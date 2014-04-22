

#include <string.h>
#include "global.h"
#include "instruction.h"
#include "decode.h"

bool opnd_is_pc(opnd_t opnd) {
    return opnd.kind == PC_kind;
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
