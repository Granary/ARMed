#ifndef DECODE_H_
#define DECODE_H_

#define PREFIX_DATA           0x0008
#define PREFIX_ADDR           0x0010
#define PREFIX_REX_W          0x0020
#define PREFIX_REX_R          0x0040
#define PREFIX_REX_X          0x0080
#define PREFIX_REX_B          0x0100


typedef struct {
    unsigned int regDst1;
    unsigned int regDst2;
    unsigned int regSrc1;
    unsigned int regSrc2;
    unsigned int regSrc3;
    /* immed info */
    opnd_size_t size_immed;
    short immed;
    unsigned char *start_pc;
    uint len;
} decode_info_t;

enum {
    /* register enum values are used for TYPE_*REG */
    OPSZ_NA, /**< Sentinel value: not a valid size. */ /* = 139 */
};

typedef struct  {
  int type;
  unsigned int concernedBits;
  unsigned int maskedBits;
  char *name;
  unsigned char dst1_type; unsigned int dst1_mask;
  unsigned char dst2_type; unsigned int dst2_mask;
  unsigned char src1_type; unsigned int src1_mask;
  unsigned char src2_type; unsigned int src2_mask;
  unsigned char src3_type; unsigned int src3_mask;
  unsigned int APSR;
} instr_info_t;

typedef struct
{
  int catergoryNumber;
  unsigned int concernedBits;
    unsigned int maskedBits;
} InstructionCatergory;

extern const instr_info_t DataProcessingInstructionsR[];
extern const instr_info_t MultipyAndMultiplyAcc[];
extern const instr_info_t DataProcessingInstructionsIMM[];
extern const instr_info_t BranchInstructions[];
extern const instr_info_t loadStore[];
extern const InstructionCatergory Catergories[];
extern const InstructionCatergory DataProcCats[];
extern const instr_info_t NullInstruction[];
extern const instr_info_t serviceCalls[];

byte *
decode_opcode(byte *pc, instr_t *instr);

byte *
decode(byte *pc, instr_t *instr);

#define UNKNOWN_APSR    0


enum {
    TYPE_NONE,
    Reg,
    Immediate,
};


enum{
/* 0 */ OP_AND,
/* 1 */ OP_EOR,
/* 2 */ OP_SUB,
/* 3 */ OP_RSB,
/* 4 */ OP_ADD,
/* 5 */ OP_ADC,
/* 6 */ OP_SBC,
/* 7 */ OP_RSC,
/* 8 */ OP_TST,
/* 9 */ OP_TEQ,
/* 10 */ OP_CMP,
/* 11 */ OP_CMN,
/* 12 */ OP_ORR,
/* 13 */ OP_MOV,
/* 14 */ OP_LSL,
/* 15 */ OP_LSR,
/* 16 */ OP_ASR,
/* 17 */ OP_RRX,
/* 18 */ OP_ROR,
/* 19 */ OP_BIC,
/* 20 */ OP_MVN,
/* 21 */ OP_ADR,
/* 22 */ OP_MUL,
/* 23 */ OP_MLA,
/* 24 */ OP_UMAAL,
/* 25 */ OP_MLS,
/* 26 */ OP_UMULL,
/* 27 */ OP_UMLAL,
/* 28 */ OP_SMULL,
/* 29 */ OP_SMLAL,
/* 30 */ OP_B,
/* 31 */ OP_BL,
/* 32 */ OP_STRT,
/* 33 */ OP_STRB,
/* 34 */ OP_STRBT,
/* 35 */ OP_LDRT,
/* 36 */ OP_LDRB,
/* 37 */ OP_LDRBT,
/* 38 */ OP_LDR,
/* 39 */ OP_STR,
/* 40 */ OP_SVC,
        OP_NULL,
};



extern const InstructionCatergory Catergories[];
extern const InstructionCatergory DataProcCats[];


typedef unsigned char opnd_size_t;

enum{
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15,
  RUNKNOWN,
};


#endif /* DECODE_H_ */
