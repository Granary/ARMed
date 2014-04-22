#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_


#define CAT_UNCONDITIONAL   1
#define CAT_DATAPROC        2
#define CAT_LOADSTORE1      3
#define CAT_LOADSTORE2      4
#define CAT_BRANCH          5
#define CAT_SVC             6
#define CAT_UNDEFINED       7
#define CAT_NUMBER          6

#define DP_REGISTER 		1
#define DP_REGISTERSR		2
#define DP_MISC				3
#define DP_HWMMA			4
#define DP_MULTIPLYMA		5
#define DP_SP				6
#define DP_EXTRALS			7
#define DP_EXTRALSUP		8
#define DP_IMM				9
#define DP_IMMLD			10
#define DP_IMMHILD			11
#define DP_MSRIMM			12
#define DP_UNDEFINED		13
#define DP_NUMBER			14

enum {
    NULL_kind,
    IMMED_INTEGER_kind,
    IMMED_FLOAT_kind,
    PC_kind,
    REG_kind,
    BASE_DISP_kind,
    LAST_kind,
};

typedef byte opnd_size_t;

struct _opnd_t {
    byte kind;
    opnd_size_t size;
};

typedef struct _dr_instr_label_data_t {
    unsigned int data[4]; /**< Generic fields for storing user-controlled data */
} dr_instr_label_data_t;

struct _instr_t {
    /* flags contains the constants defined above */
    uint    flags;

    /* raw bits of length length are pointed to by the bytes field */
    byte    *bytes;
    uint    length;

    /* translation target for this instr */
    app_pc  translation;

    byte    cond;
    byte    instr_type;
    byte    opcode;

    /* we dynamically allocate dst and src arrays b/c x86 instrs can have
     * up to 8 of each of them, but most have <=2 dsts and <=3 srcs, and we
     * use this struct for un-decoded instrs too
     */
    byte    num_dsts;
    byte    num_srcs;

    union {
        struct {
            /* for efficiency everyone has a 1st src opnd, since we often just
             * decode jumps, which all have a single source (==target)
             * yes this is an extra 10 bytes, but the whole struct is still < 64 bytes!
             */
            opnd_t    src0;
            opnd_t    *srcs; /* this array has 2nd src and beyond */
            opnd_t    *dsts;
        };
        dr_instr_label_data_t label_data;
    };

    /* SJF Flags 2 contains flags or possible op2 depening on instruction type */
    uint    flags2;   /* contains flags contained in bits[7,4] of the instr
                         May contain opcode for coprocessor instrs */
    uint    cpsr;     /* CPSR flags */
    uint 	apsr; 		/*APSR flags*/

    /* this field is for the use of passes as an annotation.
     * it is also used to hold the offset of an instruction when encoding
     * pc-relative instructions.
     */
    void *note;

    /* fields for building instructions into instruction lists */
    instr_t   *prev;
    instr_t   *next;

    /*SJF Need the flags to be set in here as well
          so they can be corectly encoded out to the fcache */
    bool p_flag; // Post indexed?
    bool u_flag; // plus/minus offset?
    bool s_flag; // set cpsr flags?
    bool w_flag; // write back?
    bool l_flag; //load/store
    bool b_flag; //word or byte?
    bool d_flag; //???
    bool h_flag; //???
    bool m_flag; //For signed multiplies
    bool r_flag; //For stm to flag to overwrite cpsr with spsr

    int  shift_type;

}; /* instr_t */

byte *
instr_get_raw_bits(instr_t *instr);

void
instr_set_opcode(instr_t *instr, int opcode);

void
instr_set_apsr_valid(instr_t * instr, bool valid);

void
instr_set_operands_valid(instr_t *instr, bool valid);

void
instr_set_raw_bits(instr_t *instr, byte *addr, uint length);

#endif /* INSTRUCTION_H_ */
