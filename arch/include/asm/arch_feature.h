#ifndef   ARCH_FEATURE_H
#define   ARCH_FEATURE_H

#include  <stdint.h>

#include  "arch_regs.h"

#define  ID_PFR0_THUMB_FLAG     (0xF0U)
#define  ID_PFR0_THUMB2_SUPPORT   (0x30U)


static inline  uint32_t can_support_thumb2(void)
{
    return  (REG32_READ(ID_PFR0_REG_ADDR) & ID_PFR0_THUMB_FLAG) == ID_PFR0_THUMB2_SUPPORT;

}


#define  ID_DFR0_DEBUG_FLAG    (0xF00000U)
#define  ID_DFR0_DEBUG_MEMORY_MAPPED   (0x100000U)

static inline  uint32_t can_support_memory_mapped_debug(void)
{
    return  (REG32_READ(ID_DFR0_REG_ADDR) & ID_DFR0_DEBUG_FLAG) == ID_DFR0_DEBUG_MEMORY_MAPPED;
}


#define  ID_MMFR0_PMSA_FLAG     (0xF0U)
#define  ID_MMFR0_PMSA_7        (0x30U)
static inline uint32_t can_support_psmav7(void)
{
    return  (REG32_READ(ID_MMFR0_REG_ADDR) & ID_MMFR0_PMSA_FLAG) == ID_MMFR0_PMSA_7;
}


#define  ID_MMFR2_WFI_FLAG     (0xF000000U)
#define  ID_MMFR2_WFI_STALLING        (0x1000000U)
static inline uint32_t can_support_WFI_stalling(void)
{
    return  (REG32_READ(ID_MMFR2_REG_ADDR) & ID_MMFR2_WFI_FLAG) == ID_MMFR2_WFI_STALLING;
}


#define  ID_MVFR0_ROUND_MODE_FLAG          (0xF0000000U)
#define  ID_MVFR0_SHORT_VECTOR_FLAG        (0x0F000000U)
#define  ID_MVFR0_SQUARE_ROOT_FLAG         (0x00F00000U)
#define  ID_MVFR0_DIVIDE_FLAG              (0x000F0000U)
#define  ID_MVFR0_FP_EXCEPTION_FLAG        (0x0000F000U)
#define  ID_MVFR0_DOUBLE_PRECISION_FLAG    (0x00000F00U)
#define  ID_MVFR0_SINGLE_PRECISION_FLAG    (0x000000F0U)
#define  ID_MVFR0_SIMD_FLAG                (0x0000000FU)

#define  FP_MVFR0_SUPPORT_ALL_ROUND          (0x10000000U)
#define  FP_MVFR0_SUPPORT_SQUARE_ROOT        (0x00100000U)
#define  FP_MVFR0_SUPPORT_DIVIDE             (0x00010000U)
#define  FP_MVFR0_SUPPORT_DOUBLE             (0x00000200U)
#define  FP_MVFR0_SUPPORT_SINGLE             (0x00000020U)

static inline uint32_t  fp_support_all_round_mode(void)
{
    return  (REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_ROUND_MODE_FLAG) == ID_MMFR2_WFI_STALLING; 
}

static inline uint32_t  fp_support_short_vector(void)
{
    return  REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_SHORT_VECTOR_FLAG; 
}

static inline uint32_t  fp_support_square_root(void)
{
    return  (REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_SQUARE_ROOT_FLAG) == 
                FP_MVFR0_SUPPORT_SQUARE_ROOT; 
}

static inline  uint32_t fp_support_divide(void)
{
        return  (REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_DIVIDE_FLAG) == 
                FP_MVFR0_SUPPORT_DIVIDE; 
}

static inline  uint32_t fp_support_exception_trap(void)
{
        return  REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_FP_EXCEPTION_FLAG; 
}

static inline  uint32_t fp_support_double(void)
{
        return  REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_DOUBLE_PRECISION_FLAG == 
                    FP_MVFR0_SUPPORT_DOUBLE; 
}


static inline  uint32_t fp_support_single(void)
{
        return  REG32_READ(SCS_FPMVFR_REG_ADDR(0)) & ID_MVFR0_SINGLE_PRECISION_FLAG == 
                    FP_MVFR0_SUPPORT_SINGLE; 
}




#endif

