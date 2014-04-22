
#include "global.h"
#include "instruction.h"
#include "decode.h"

static bool
decode_operand(decode_info_t *di, byte optype, opnd_size_t opsize, opnd_t *opnd)
{
	switch (optype) {
	case TYPE_NONE:
		opnd->kind = NULL_kind;
		return TRUE;
	case Reg:
		opnd->kind = REG_kind;
		return TRUE;
	}
}

int
decodeDataProcessing(unsigned int instruction)
{
	int i = 0;
	for(i = 0; i < DP_NUMBER; i++){
		if((instruction & DataProcCats[i].maskedBits) == DataProcCats[i].concernedBits)
			return DataProcCats[i].catergoryNumber;
	}
	return DP_UNDEFINED;
}

int get_instr_type(unsigned int instruction)
{
	unsigned int i = 0;
	for(i = 0; i < CAT_NUMBER; i++)
	{
		if((instruction & Catergories[i].concernedBits) == Catergories[i].maskedBits)
			return Catergories[i].catergoryNumber;
	}
	return CAT_UNDEFINED;
}

// Read the operands of the instruction
void
read_operands(unsigned char * PC, decode_info_t *di, const instr_info_t  *info)
{
	unsigned int instruction = *PC;
	int bitShifter = 0;
	int temp;
	int i = 0;
	instruction = instruction << 8 | *(PC+1);
	instruction = instruction << 8 | *(PC+2);
	instruction = instruction << 8 | *(PC+3);

	LOG("Instruction %.8x\n", instruction);

	if (info->dst1_type != TYPE_NONE){
		di->regDst1 = (instruction) & (info->dst1_mask);
		temp = info->dst1_mask;
		for(i = 0 ; i < 32; i++)
			if((temp & 0x1) == 1)
				break;
			else{
				temp = temp >> 1;
				bitShifter ++;
			}
		di->regDst1 = di->regDst1 >> bitShifter;
		bitShifter = 0;
	}

	if (info->dst2_type != TYPE_NONE){
		di->regDst2 = instruction & info->dst2_mask;
		temp = info->dst2_mask;
		for(i = 0 ; i < 32; i++)
			if((temp & 0x1) == 1)
				break;
			else{
				temp = temp >> 1;
				bitShifter ++;
			}
		di->regDst2 = di->regDst2 >> bitShifter;
		bitShifter = 0;
	}

	if (info->src1_type != TYPE_NONE){
		if(info->src1_type != Reg){
			di->immed = instruction & info->src1_mask;
			temp = info->src1_mask;
			for(i = 0 ; i < 32; i++)
				if((temp & 0x1) == 1)
					break;
				else{
					temp = temp >> 1;
					bitShifter ++;
				}
			di->immed = di->immed >> bitShifter;
			bitShifter = 0;

		} else{
			di->regSrc1 = instruction & info->src1_mask;
			temp = info->src1_mask;
			for(i = 0 ; i < 32; i++)
				if((temp & 0x1) == 1)
					break;
				else
				{
					temp = temp >> 1;
					bitShifter ++;
				}

			di->regSrc1 = di->regSrc1 >> bitShifter;
			bitShifter = 0;
		}
	}

	if (info->src2_type != TYPE_NONE){
		if(info->src2_type != Reg)
		{
			di->immed = instruction & info->src2_mask;
			temp = info->src2_mask;
			for(i = 0 ; i < 32; i++)
				if((temp & 0x1) == 1)
					break;
				else
				{
					temp = temp >> 1;
					bitShifter ++;
				}

			di->immed = di->immed >> bitShifter;
			bitShifter = 0;
		}
		else
		{
			di->regSrc2 = instruction & info->src2_mask;
			//           printf("Src2 Hex %x\n", di->regSrc2);
			temp = info->src2_mask;
			for(i = 0 ; i < 32; i++)
				if((temp & 0x1) == 1)
					break;
				else
				{
					temp = temp >> 1;
					bitShifter ++;
				}
			di->regSrc2 = di->regSrc2 >> bitShifter;
		}
	}

	if (info->src3_type != TYPE_NONE){
		if(info->src3_type != Reg)
		{
			di->immed = instruction & info->src3_mask;
			temp = info->src3_mask;
			for(i = 0 ; i < 32; i++)
				if((temp & 0x1) == 1)
					break;
				else
				{
					temp = temp >> 1;
					bitShifter ++;
				}
			di->immed = di->immed >> bitShifter;
			bitShifter = 0;
		}
		else
		{
			di->regSrc3 = instruction & info->src3_mask;
			temp = info->src3_mask;
			for(i = 0 ; i < 32; i++)
				if((temp & 0x1) == 1)
					break;
				else
				{
					temp = temp >> 1;
					bitShifter ++;
				}
			di->regSrc3 = di->regSrc3 >> bitShifter;
		}
	}
	return;
}

static byte *
read_instruction(byte *pc, byte *orig_pc,
		const instr_info_t *ret_info, decode_info_t *di,
		bool just_opcode)
{
	unsigned int instruction = *pc;
	const instr_info_t *decodedInstruction = NULL;
	di->start_pc = pc;
	di->size_immed = OPSZ_NA;
	di->regDst1 = TYPE_NONE;
	di->regDst2 = TYPE_NONE;
	di->regSrc1 = TYPE_NONE;
	di->regSrc2 = TYPE_NONE;
	di->regSrc3 = TYPE_NONE;
	di->immed = 0;
	di->len = 4;

	/* get instruction as a whole*/
	instruction = instruction << 8 | *(pc+1);
	instruction = instruction << 8 | *(pc+2);
	instruction = instruction << 8 | *(pc+3);

	int instrCat = get_instr_type(instruction);

	switch (instrCat){

	case CAT_UNCONDITIONAL:
		printf("Instruction is an Unconditional Instruction\n");
		decodedInstruction = NullInstruction;
		break;

	case CAT_DATAPROC:
		printf("Instruction is a Data Processing Instruction\n");
		instrCat = decodeDataProcessing(instruction);

		switch (instrCat){

		case DP_REGISTER:
			printf("Instruction is a Register Processing Instruction\n");
			decodedInstruction = DataProcessingInstructionsR;
			break;

		case DP_REGISTERSR:
			printf("Instruction is a Register Shifted Register Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_MISC:
			printf("Instruction is a Misc Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_HWMMA:
			printf("Instruction is a Halfword Multiply Accumumlate Instructions\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_MULTIPLYMA:
			printf("Instruction is a Multiply and Accumulate Instruction\n");
			decodedInstruction = MultipyAndMultiplyAcc;
			break;

		case DP_SP:
			printf("Instruction is a Synchronization Primitive\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_EXTRALS:
			printf("Instruction is an Extra Load/ Store Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_EXTRALSUP:
			printf("Instruction is an Extra Load Store Unprivlaged Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_IMM:
			printf("Instruction is a Data Processing IMM Instruction\n");
			decodedInstruction = DataProcessingInstructionsIMM;
			break;

		case DP_IMMLD:
			printf("Instruction is a 16 Bit Immediate load Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_IMMHILD:
			printf("Instruction is a High Halfword Immediate Load Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_MSRIMM:
			printf("Instruction is a MSR Immedate Instruction\n");
			decodedInstruction = NullInstruction;
			break;

		case DP_UNDEFINED:
			printf("Instruction is Undefined\n");
			decodedInstruction = NullInstruction;
			break;
		}
		break;

		case CAT_LOADSTORE1:
			printf("Instruction is a Load Store Type 1 Instruction\n");
			decodedInstruction = loadStore;
			break;

		case CAT_LOADSTORE2:
			printf("Instruction is a Load Store Type 2 Instruction\n");
			decodedInstruction = loadStore;
			break;

		case CAT_BRANCH:
			printf("Instruction is a Branch Insturction\n");
			decodedInstruction = BranchInstructions;
			break;

		case CAT_SVC:
			printf("Instruction is a Service Call Instruction\n");
			decodedInstruction = serviceCalls;
			break;

		case CAT_UNDEFINED:
			printf("Instruction is Undefined\n");
			decodedInstruction = NullInstruction;
			break;
	}


	while (decodedInstruction->type != OP_NULL){
		if((instruction & decodedInstruction->maskedBits) == decodedInstruction->concernedBits)
			break;
		decodedInstruction++;
	}

	LOG("Final Instruction Opcode is: %s\n", decodedInstruction->name);

	if (just_opcode) {
		ret_info = decodedInstruction;
		return NULL;
	}

	read_operands(pc,di, decodedInstruction);
	printf("Destination Operand 1 is: %d\n", di->regDst1);
	printf("Destination Operand 2 is: %d\n", di->regDst2);
	printf("Source Operand 1 is: %d\n", di->regSrc1);
	printf("Source Operand 2 is: %d\n", di->regSrc2);
	printf("Source Operand 3 is: %d\n", di->regSrc3);
	printf("Immediate Operand is: %d\n", di->immed);
	/* return values */
	ret_info = decodedInstruction;
	return pc+4;
}


byte *
decode_opcode(byte *pc, instr_t *instr)
{
	instr_info_t instr_info;
	decode_info_t di;
	int sz = 0;

	read_instruction(pc, pc, &instr_info, &di, TRUE /* just opcode */);

	instr_set_opcode(instr, instr_info.type);

	instr->apsr = instr_info.APSR;
	instr_set_apsr_valid(instr, TRUE);

	/* operands are NOT set */
	instr_set_operands_valid(instr, FALSE);
	instr_set_raw_bits(instr, pc, sz);
	//    /* must set rip_rel_pos after setting raw bits */
	return pc + 4;
}




static byte *
decode_common(byte *pc, byte *orig_pc, instr_t *instr)
{
	const instr_info_t instr_info;
	decode_info_t di;
	byte *next_pc;
	int instr_num_dsts = 0, instr_num_srcs = 0;
	opnd_t dsts[8];
	opnd_t srcs[8];

	LOG("Starting decode_common\n");

	next_pc = read_instruction(pc, orig_pc, &instr_info, &di, FALSE );
	instr_set_opcode(instr, instr_info.type);

	if (next_pc == NULL) {
		LOG("decode: invalid instr\n");
		return NULL;
	}

	// set instruction apsr
	instr->apsr = instr_info.APSR;
	instr_set_apsr_valid(instr, TRUE);

	instr_set_operands_valid(instr, TRUE);

	di.len = (int) (next_pc - pc);

	//TODO: decode operand
	if (instr_info.dst1_type != TYPE_NONE) {
		if (!decode_operand(&di, instr_info.dst1_type, di.regDst1,
				&(dsts[instr_num_dsts++])))
			goto decode_invalid;
	}

	if (instr_info.dst2_type != TYPE_NONE) {
		if (!decode_operand(&di, instr_info.dst2_type, di.regDst2,
				&(dsts[instr_num_dsts++])))
			goto decode_invalid;
	}

	if (instr_info.src1_type != TYPE_NONE) {
		if(instr_info.src1_type != Immediate){
			if (!decode_operand(&di, instr_info.src1_type, di.regSrc1,
					&(srcs[instr_num_srcs++])))
				goto decode_invalid;

		} else{
			if (!decode_operand(&di, instr_info.src1_type, di.immed,
					&(srcs[instr_num_srcs++])))
				goto decode_invalid;
		}
	}

	if (instr_info.src2_type != TYPE_NONE) {
		if(instr_info.src2_type != Immediate){
			if (!decode_operand(&di, instr_info.src2_type, di.regSrc2,
					&(srcs[instr_num_srcs++])))
				goto decode_invalid;

		} else{
			if (!decode_operand(&di, instr_info.src2_type, di.immed,
					&(srcs[instr_num_srcs++])))
				goto decode_invalid;
		}
	}

	if (instr_info.src3_type != TYPE_NONE) {
		if(instr_info.src3_type != Immediate){
			if (!decode_operand(&di, instr_info.src3_type, di.regSrc1,
					&(srcs[instr_num_srcs++])))
				goto decode_invalid;

		} else{
			if (!decode_operand(&di, instr_info.src3_type, di.immed,
					&(srcs[instr_num_srcs++])))
				goto decode_invalid;
		}
	}

	return next_pc;

decode_invalid:
	return NULL;
}



byte *
decode(byte *pc, instr_t *instr)
{
	return decode_common(pc, pc, instr);
}
