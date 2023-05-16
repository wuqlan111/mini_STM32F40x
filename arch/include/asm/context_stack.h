
#ifndef  ARM_FAULT_H
#define  ARM_FAULT_H

#include  "arch_regs.h"

typedef struct {
    uint32_t  r0;
    uint32_t  r1;
    uint32_t  r2;
    uint32_t  r3;
    uint32_t  r12;
    uint32_t  r14;
    uint32_t  ret_addr;
    uint32_t  xpsr;
} __attribute__((packed)) context_no_fp_regs_t;


typedef struct {
    uint32_t  r0;
    uint32_t  r1;
    uint32_t  r2;
    uint32_t  r3;
    uint32_t  r12;
    uint32_t  r14;
    uint32_t  ret_addr;
    uint32_t  xpsr;
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
} __attribute__((packed)) context_fp_regs_t;



#endif


