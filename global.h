#ifndef GLOBAL_H_
#define GLOBAL_H_


#include <stdio.h>
#include <stdlib.h>

#define CLIENT_ASSERT(...)
#define ASSERT(...)
#define LOG 	printf

#define TRUE 	1
#define FALSE	0

typedef int bool;

typedef unsigned int uint;
typedef unsigned short ushort;

typedef unsigned char byte;
typedef signed char sbyte;

typedef byte * app_pc;

typedef void (*generic_func_t) ();

typedef unsigned long long int uint64;
typedef uint64 reg_t;
typedef long long int int64;
typedef int ptr_int_t;


struct _opnd_t;
typedef struct _opnd_t opnd_t;
struct _instr_t;
typedef struct _instr_t instr_t;
struct _instr_list_t;
struct _fragment_t;
typedef struct _fragment_t fragment_t;
struct _future_fragment_t;
typedef struct _future_fragment_t future_fragment_t;
struct _trace_t;
typedef struct _trace_t trace_t;
struct _linkstub_t;
typedef struct _linkstub_t linkstub_t;
struct _dcontext_t;
typedef struct _dcontext_t dcontext_t;
struct vm_area_vector_t;
typedef struct vm_area_vector_t vm_area_vector_t;
struct _coarse_info_t;
typedef struct _coarse_info_t coarse_info_t;
struct _coarse_freeze_info_t;
typedef struct _coarse_freeze_info_t coarse_freeze_info_t;
struct _module_data_t;
typedef struct _module_data_t module_data_t;
typedef struct _instr_list_t instrlist_t;
typedef struct _module_data_t module_data_t;




#endif /* GLOBAL_H_ */
