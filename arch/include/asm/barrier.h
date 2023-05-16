#ifndef   ARCH_BARRIER_H
#define   ARCH_BARRIER_H

#define  csdb()       (__asm__ volatile("csdb":::))
#define  dmb(opt)     (__asm__ volatile("dmb" #opt:::))
#define  dsb(opt)     (__asm__ volatile("dsb" #opt:::))
#define  isb(opt)     (__asm__ volatile("isb" #opt:::))
#define  pssbb()      (__asm__ volatile("pssbb":::))
#define  ssbb()       (__asm__ volatile("ssbb":::))








#endif

