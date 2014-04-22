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

typedef byte opnd_size_t;

struct _opnd_t {
    byte kind;
    opnd_size_t size;
};


#endif /* INSTRUCTION_H_ */
