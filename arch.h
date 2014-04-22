/*
 * arch.h
 *
 *  Created on: 2014-04-07
 *      Author: akshayk
 */

#ifndef ARCH_H_
#define ARCH_H_

#define R0_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r0)))
#define R1_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r1)))
#define R2_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r2)))
#define R3_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r3)))
#define R4_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r4)))
#define R5_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r5)))
#define R6_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r6)))
#define R7_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r7)))
#define R8_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r8)))
#define R9_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r9)))
#define R10_OFFSET       //((MC_OFFS) + (offsetof(priv_mcontext_t, r10)))
#define R11_OFFSET       //((MC_OFFS) + (offsetof(priv_mcontext_t, r11)))
#define R12_OFFSET       //((MC_OFFS) + (offsetof(priv_mcontext_t, r12)))
#define R13_OFFSET       //((MC_OFFS) + (offsetof(priv_mcontext_t, r13)))
#define R14_OFFSET       //((MC_OFFS) + (offsetof(priv_mcontext_t, r14)))

  /* Define both pc and r15 even though the same */
#define R15_OFFSET       //((MC_OFFS) + (offsetof(priv_mcontext_t, r15)))
#define PC_OFFSET        //((MC_OFFS) + (offsetof(priv_mcontext_t, r15))) /* Define both pc and r15 even though the same */

#if 0
  #define CPSR_OFFSET      ((MC_OFFS) + (offsetof(priv_mcontext_t, cpsr)))

  #define ERRNO_OFFSET      (offsetof(unprotected_context_t, errno))
  #define AT_SYSCALL_OFFSET (offsetof(unprotected_context_t, at_syscall))

  #define NEXT_TAG_OFFSET        (offsetof(dcontext_t, next_tag))
  #define LAST_EXIT_OFFSET       (offsetof(dcontext_t, last_exit))
  #define DSTACK_OFFSET          (offsetof(dcontext_t, dstack))
#endif

#endif /* ARCH_H_ */
