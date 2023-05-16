
#ifndef   ASM_ARCH_ATOMIC_H
#define   ASM_ARCH_ATOMIC_H

#include  "irqflags.h"


static inline uint32_t atomic_read32(uint32_t * ptr)
{
    uint32_t  val, flag;
    val = flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("ldr %0, %1":"=r"(val):"r"(ptr):);
    restore_and_enable_irq(flag);
    return  val;
}

static inline uint16_t atomic_read16(uint16_t * ptr)
{
    uint32_t  val, flag;
    val = flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("ldrh %0, %1":"=r"(val):"r"(ptr):);
    restore_and_enable_irq(flag);
    return  (val & 0xffff);
}

static inline uint8_t atomic_read8(uint8_t * ptr)
{
    uint32_t  val, flag;
    val = flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("ldrb %0, %1":"=r"(val):"r"(ptr):);
    restore_and_enable_irq(flag);
    return  (val & 0xff);
}


static inline uint32_t atomic_write32(uint32_t * ptr, uint32_t val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("str %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);
    return  val;
}

static inline void atomic_write16(uint16_t * ptr,  uint16_t  val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("strh %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);
}

static inline void atomic_write8(uint8_t * ptr, uint8_t val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("strb %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);

}




static inline uint32_t atomic_add32(uint32_t * ptr, uint32_t val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("str %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);
    return  val;
}

static inline uint16_t atomic_add16(uint16_t * ptr,  uint16_t  val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("strh %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);
}

static inline uint16_t atomic_add8(uint8_t * ptr, uint8_t val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("strb %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);

}


static inline uint32_t atomic_sub32(uint32_t * ptr, uint32_t val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("str %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);
    return  val;
}

static inline uint16_t atomic_sub16(uint16_t * ptr,  uint16_t  val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("strh %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);
}

static inline uint16_t atomic_sub8(uint8_t * ptr, uint8_t val)
{
    uint32_t  flag;
    flag  = 0;
    flag = save_and_disable_irq();
    __asm__ volatile("strb %0, %1"::"r"(val),"r"(ptr):);
    restore_and_enable_irq(flag);

}





#endif


