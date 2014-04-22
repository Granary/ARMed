
#include "global.h"
#include "instruction.h"
#include "decode.h"

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
	return next_pc;
}



byte *
decode(byte *pc, instr_t *instr)
{
	return decode_common(pc, pc, instr);
}
