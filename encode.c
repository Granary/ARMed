#include "global.h"
#include "instruction.h"
#include "decode.h"

const char * const type_names[] = {
    "TYPE_NONE",
    "TYPE_A", /* immediate that is absolute address */
    "TYPE_I", /* immediate */
    "TYPE_J", /* immediate that is relative offset of EIP */
    "TYPE_M", /* modrm select mem addr */
    "TYPE_O", /* immediate that is memory offset */
    "TYPE_P",
    "TYPE_1",
    "TYPE_FLOATCONST",
    "TYPE_FLOATMEM",
    "TYPE_REG",
    "TYPE_CO_REG",
    "TYPE_INDIR_E",
    "TYPE_INDIR_REG",
};

const char * const reg_names[] = {
    "<NULL>",
    "r0",   "r1",   "r2",   "r3",   "r4",   "r5",   "r6",   "r7"
    "r8",   "r9",   "r10",  "r11",  "r12",  "r13",  "r14",  "r15"
    "q0",   "q1",   "q2",   "q3",   "q4",   "q5",   "q6",   "q7"
    "q8",   "q9",   "q10",  "q11",  "q12",  "q13",  "q14",  "q15"
    "d0",   "d1",   "d2",   "d3",   "d4",   "d5",   "d6",   "d7"
    "d8",   "d9",   "d10",  "d11",  "d12",  "d13",  "d14",  "d15"
    "d16",  "d17",  "d18",  "d19",  "d20",  "d21",  "d22",  "d23"
    "d24",  "d25",  "d26",  "d27",  "d28",  "d29",  "d30",  "d31"
    "s0",   "s1",   "s2",   "s3",   "s4",   "s5",   "s6",   "s7"
    "s8",   "s9",   "s10",  "s11",  "s12",  "s13",  "s14",  "s15"
    "s16",  "s17",  "s18",  "s19",  "s20",  "s21",  "s22",  "s23"
    "s24",  "s25",  "s26",  "s27",  "s28",  "s29",  "s30",  "s31"
    "<invalid>",
    "es",   "cs",   "ss",   "ds",   "fs",   "gs",

    "debug1","debug2", "control1", "control2", "cpsr"
    /* XXX: when you update here, update dr_reg_fixer[] in instr.c too */
};

byte*
write_word_to_fcache( byte* pc, byte* word )
{
	//Word should now be an instruction. MSB encoding
	*((byte *)pc) = word[3];
	pc++;
	*((byte *)pc) = word[2];
	pc++;
	*((byte *)pc) = word[1];
	pc++;
	*((byte *)pc) = word[0];
	pc++;

	return pc;
}


byte*
encode_coproc_mrc(decode_info_t* di, instr_t* instr, byte* pc)
{
	byte word[4] = {0};  //Instr encoding in byte array
	uint        opc;
	byte        b;

	opc = instr_get_opcode(instr);

	/*
       Instruction encoded as 31-0
       |cond|1010|imm24|
	 */

	/*********** Encode condition code. TODO Move to decode_info_t *********/

	if(instr_is_unconditional(instr)){
		//Encode unconditional(not a proper cond code '1111')
		b = 0xf0;
		word[0] |= b;
	} else{
		b = instr->cond;
		word[0] |= (b << 4);
	}

	pc = write_word_to_fcache(pc, word );

	// Have a separate function for branch instrs to calc correct address
	// Branch instrs are pretty simple anyway
	return pc;
}

byte*
encode_coproc_mcr(decode_info_t* di, instr_t* instr, byte* pc)
{
	byte word[4] = {0};  //Instr encoding in byte array
	uint        opc;
	byte        b;

	opc = instr_get_opcode(instr);

	/*
       Instruction encoded as 31-0
       |cond|1010|imm24|
	 */

	/*********** Encode condition code. TODO Move to decode_info_t *********/

	if(instr_is_unconditional(instr)){
		b = 0xf0;
		word[0] |= b;

	} else{
		b = instr->cond;
		word[0] |= (b << 4);
	}

	pc = write_word_to_fcache(pc, word );

	// Have a separate function for branch instrs to calc correct address
	// Branch instrs are pretty simple anyway
	return pc;
}


byte*
encode_advanced_coprocessor_and_syscall(decode_info_t* di, instr_t* instr, byte* pc)
{
	uint opc;
	byte* nxt_pc = pc;

	opc = instr_get_opcode(instr);

	switch( opc ){
	case OP_cdp:
	case OP_cdp2:
		break;

	case OP_mcr:
	case OP_mcr2:
		nxt_pc = encode_coproc_mcr(di, instr, pc);
		break;

	case OP_mrc:
	case OP_mrc2:
		nxt_pc = encode_coproc_mrc(di, instr, pc);
		break;

	default:
		break;
	}

	return nxt_pc;
}

static bool
encoding_possible_pass(decode_info_t *di, instr_t *in, const instr_info_t * ii)
{

    /* for efficiency we separately test 2 dsts, 3 srcs */
    //TEST_OPND(di, ii->dst1_type, ii->dst1_size, 1, in->num_dsts, instr_get_dst(in, 0));
    //TEST_OPND(di, ii->dst2_type, ii->dst2_size, 2, in->num_dsts, instr_get_dst(in, 1));
    //TEST_OPND(di, ii->src1_type, ii->src1_size, 1, in->num_srcs, instr_get_src(in, 0));
    //TEST_OPND(di, ii->src2_type, ii->src2_size, 2, in->num_srcs, instr_get_src(in, 1));
    //TEST_OPND(di, ii->src3_type, ii->src3_size, 3, in->num_srcs, instr_get_src(in, 2));

    return TRUE;
}

/* Does not check operands beyond 2 dsts and 3 srcs!
 * Modifies in's prefixes to reflect whether operand or data size
 * prefixes are required.
 * Assumes caller has set di->x86_mode (i.e., ignores in's mode).
 */
static bool
encoding_possible(decode_info_t *di, instr_t *in, const instr_info_t * ii)
{
    if (ii == NULL || in == NULL)
        return FALSE;

    if (!encoding_possible_pass(di, in, ii))
        return FALSE;

    return TRUE;
}


static byte *
instr_encode_common(instr_t *instr, byte *copy_pc, byte *final_pc,
                    bool check_reachable, bool *has_instr_opnds/*OUT OPTIONAL*/)
{
	instr_info_t instr_info;
	decode_info_t di;
	int sz=0;

	byte *cache_pc = copy_pc;
	byte *field_ptr = cache_pc;
	uint instr_type;

	if (has_instr_opnds != NULL)
		*has_instr_opnds = FALSE;

	/* first handle the already-encoded instructions */
	if (instr_raw_bits_valid(instr)) {
		/* copy raw bits, possibly re-relativizing */
		return copy_and_re_relativize_raw_instr(instr, cache_pc, final_pc);
	}

	/* fill out the other fields of di */
	di.start_pc = cache_pc;
	di.size_immed = OPSZ_NA;

    if (!encoding_possible(&di, instr, &instr_info))
       return FALSE;

    switch( instr_type ){

    case INSTR_TYPE_UNDECODED:
    	//Check for label here
    	break;

    case INSTR_TYPE_DATA_PROCESSING_AND_ELS:
    	field_ptr = encode_data_processing_and_els(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_DATA_PROCESSING_IMM:
    	field_ptr = encode_data_processing_imm_and_misc(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_LOAD_STORE1:
    	field_ptr = encode_load_store_1_and_misc(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_LOAD_STORE2_AND_MEDIA:
    	field_ptr = encode_load_store_2_and_media(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_LOAD_STORE_MULTIPLE:
    	field_ptr = (byte*)encode_load_store_multiple(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_BRANCH:
    	field_ptr = encode_branch(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_COPROCESSOR_DATA_MOVEMENT:
    	field_ptr = encode_coprocessor_data_movement(&di, instr, field_ptr);
    	break;

    case INSTR_TYPE_ADVANCED_COPROCESSOR_AND_SYSCALL:
    	field_ptr = encode_advanced_coprocessor_and_syscall(&di, instr, field_ptr);
    	break;

    default:
    	return 0;
    }

    /* instr_t* operand support */
    //    di.cur_note = (ptr_int_t) instr->note;

    //SJF Should be 4
    sz = decode_sizeof(di.start_pc);

    if (has_instr_opnds != NULL)
    	*has_instr_opnds = 1;
    return field_ptr;
}

byte *
instr_encode_to_copy(instr_t *instr, byte *copy_pc, byte *final_pc)
{
	return instr_encode_common(instr, copy_pc, final_pc, TRUE, NULL);
}

byte *
instr_encode(instr_t *instr, byte *pc)
{
	return instr_encode_to_copy(instr, pc, pc);
}
