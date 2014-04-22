/*
 * main.c
 *
 *  Created on: 2014-03-05
 *      Author: akshayk
 */

#include <stdio.h>
#include "global.h"
#include "instruction.h"
#include "decode.h"

unsigned char theProgram [] = {
        0x00, 0x92, 0x40, 0x03, // ADDS R4, R2, R3
        0x00, 0xC2, 0x34, 0x91,  // SMULL R2, R3 , R4, R1
        0x01, 0xA0, 0x71, 0x83, // LSL R7, R3, #3
        0x01, 0x12, 0x00, 0x01, // TST R2, R1
        0x02, 0xF3, 0x40, 0x05, // RSC R4, R3, #5
        0x0A, 0x00, 0x00, 0xFF, // B #255
        0x0B, 0x00, 0x00, 0x0A, // BL #10
        0x04, 0x19, 0x30, 0x0C, // LDR R3, R9, #12
        0x06, 0x02, 0x10, 0x05, // STR R1, R2, R5
        0x0F, 0x00, 0x00, 0xC0,
        0xe1, 0x54, 0x00, 0x05,
        0x21, 0xa0, 0xf0, 0x0e,
        0xe8, 0xb4, 0x00, 0x41, //        ldm     r4!, {r0, r6}
        0xe7, 0x80, 0x60, 0x03, //        str     r6, [r0, r3]
        0xea, 0xff, 0xff, 0xfa,
}; // SVC #192

#define INSTR_NUMBER    15

int main()
{
    unsigned int PC, i;
    instr_t instr;
    unsigned char * currentPC = theProgram;

    for(i = 0; i < INSTR_NUMBER; i++)
    {
        PC = *currentPC;
        PC = PC << 8 | *(currentPC+1);
        PC = PC << 8 | *(currentPC+2);
        PC = PC << 8 | *(currentPC+3);
        printf("Instruction %d is: %.8x \n",i, PC);
        currentPC = decode(currentPC, &instr);
    }
    return 0;
}


