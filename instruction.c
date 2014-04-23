

#include <string.h>
#include "global.h"
#include "instruction.h"
#include "decode.h"

bool opnd_is_pc(opnd_t opnd) {
    return opnd.kind == PC_kind;
}

bool
instr_opcode_valid(instr_t *instr)
{
    return (instr->opcode != OP_INVALID && instr->opcode != OP_UNDECODED);
}

byte *
instr_get_raw_bits(instr_t *instr)
{
    return instr->bytes;
}


void
instr_set_opcode(instr_t *instr, int opcode)
{
    instr->opcode = opcode;
}

void
instr_set_apsr_valid(instr_t * instr, bool valid)
{

}

void
instr_set_operands_valid(instr_t *instr, bool valid)
{

}

void
instr_set_raw_bits(instr_t *instr, byte *addr, uint length)
{
    instr->bytes = addr;
    instr->length = length;
}

void
instr_decode_opcode(instr_t *instr)
{
    if (!instr_opcode_valid(instr)) {
        byte *next_pc;
        next_pc = decode_opcode(instr->bytes, instr);
    }
}


int
instr_get_opcode(instr_t *instr)
{
	if (instr->opcode == OP_UNDECODED)
		instr_decode_opcode(instr);
	return instr->opcode;
}
