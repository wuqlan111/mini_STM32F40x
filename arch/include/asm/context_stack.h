
#ifndef  ARM_FAULT_H
#define  ARM_FAULT_H

#include  "arch_regs.h"
#include  "gcc_type.h"


typedef struct {
    uint32_t  faultmask;
    uint32_t  basepri;
    uint32_t  primask;
    uint32_t  control;
    uint32_t  r4;
    uint32_t  r5;
    uint32_t  r6;
    uint32_t  r7;
    uint32_t  r8;
    uint32_t  r9;
    uint32_t  r10;
    uint32_t  r11;
    uint32_t  lr;
} ATTRIBUTE_PACK context_user_regs_t;


typedef struct {
    uint32_t  r0;
    uint32_t  r1;
    uint32_t  r2;
    uint32_t  r3;
    uint32_t  r12;
    uint32_t  r14;
    uint32_t  ret_addr;
    uint32_t  xpsr;
} ATTRIBUTE_PACK context_system_regs_t;


typedef struct {
    uint32_t  s0;
    uint32_t  s1;
    uint32_t  s2;
    uint32_t  s3;
    uint32_t  s4;
    uint32_t  s5;
    uint32_t  s6;
    uint32_t  s7;
    uint32_t  s8;
    uint32_t  s9;
    uint32_t  s10;
    uint32_t  s11;
    uint32_t  s12;
    uint32_t  s13;
    uint32_t  s14;
    uint32_t  s15;
    uint32_t  fpscr;
} ATTRIBUTE_PACK context_fp_regs_t;


typedef struct {
    context_user_regs_t  user_regs;    
    context_system_regs_t  common_regs;
} ATTRIBUTE_PACK  context_exception_no_fp_regs_t;

typedef struct {
    context_exception_no_fp_regs_t   no_fp_context;
    context_fp_regs_t    fp_regs;
} ATTRIBUTE_PACK  context_exception_fp_regs_t;



#endif


