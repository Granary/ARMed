#include "global.h"
#include "instr.h"

typedef unsigned char byte;

#define SIZE_SZ     4

int
decode_sizeof(byte *start_pc)
{
    return SIZE_SZ;
}

byte *
decode_cti(byte *pc, instr_t *instr)
{
    /*TODO : check decoding of CTI instructions*/
    return 0;
}


/* Returns a pointer to the pc of the next instruction
 * Returns NULL on decoding an invalid instruction.
 */
byte *
decode_next_pc(byte *pc)
{
    int sz = decode_sizeof(pc);
    if (sz == 0)
        return NULL;
    else
        return pc + sz;
}


byte *
decode_raw(byte *pc, instr_t *instr)
{
    int sz = decode_sizeof(pc);
    return (byte*)(pc + sz);
}



