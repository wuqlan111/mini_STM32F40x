
#ifndef  ASM_ARCH_REGS
#define  ASM_ARCH_REGS

#include  <stdint.h>
#include  "gcc_type.h"

// arch special  registers
#define  APSR_REG             "APSR"
#define  IPSR_REG             "IPSR"
#define  EPSR_REG             "EPSR"
#define  IAPSR_REG            "IAPSR"
#define  EAPSR_REG            "EAPSR"
#define  XPSR_REG             "XPSR"
#define  IEPSR_REG            "IEPSR"
#define  MSP_REG              "MSP"
#define  PSR_REG              "PSR"
#define  PRIMASK_REG          "PRIMASK"
#define  BASEPRI_REG          "BASEPRI"
#define  BASEPRI_MAX_REG      "BASEPRI_MAX"
#define  FAULTMASK_REG        "FAULTMASK"
#define  CONTROL_REG          "CONTROL"


//read  special  register
#define   READ_XPSR(name)    {       \
                    uint32_t val = 0;    \
                    __asm__ volatile("\tmrs\t" name ", %0":"=r"(val)::"=r"(val));       \
                    val;                \
                }
//write  special  register
#define   WRITE_XPSR(name, value)   {       \
                    uint32_t  val  = (value);       \
                    __asm__ volatile("\tmsr %0, "(name)::"=r"(val):"=r"(val));  \
                }

//update  special  register
#define   UPDATE_XPSR(name,  value, mask)  {        \
                    uint32_t  val  =  0;            \
                    __asm__ volatile("\tmrs\t"(name)", %0":"=r"(val)::"=r"(val));       \
                    val &= ~(mask);           \
                    val |=  ((mask) & (value));     \
                    __asm__ volatile("\tmsr %0, "(name)::"=r"(val):"=r"(val));  \
                }


#define  CLEAR_PRIMASK()     (__asm__ volatile("\tcpsie i":::))
#define  SET_PRIMASK()       (__asm__ volatile("\tcpsid i":::))
#define  CLEAR_FAULTMASK()   (__asm__ volatile("\tcpsie f":::))
#define  SET_FAULTMASK()     (__asm__ volatile("\tcpsid f":::))


#define  SCS_BASE_ADDR       (0xE000E000u)
#define  SYSTICK_REG_OFFSET  (0x10u)
#define  NVIC_REG_OFFSET     (0x100u)
#define  SCB_REG_OFFSET      (0xD00u)
#define  MPU_REG_OFFSET      (0xD90u)
#define  DEBUG_REG_OFFSET    (0xDF0u)
#define  SW_REG_OFFSET       (0xF00u)
#define  CACHE_REG_OFFSET    (0xF50u)
#define  MID_REG_OFFSET      (0xFD0u)



#define  ICTR_REG_ADDR            (SCS_BASE_ADDR + 0x4)
#define  ACTLR_REG_ADDR           (SCS_BASE_ADDR + 0x8)


//systick registers
#define   SYSTICK_BASE_ADDR              (SCS_BASE_ADDR +  SYSTICK_REG_OFFSET)
#define   SYSTICK_CSR_REG_ADDR           (SYSTICK_BASE_ADDR)
#define   SYSTICK_RVR_REG_ADDR           (SYSTICK_BASE_ADDR  +  0x4)
#define   SYSTICK_CVR_REG_ADDR           (SYSTICK_BASE_ADDR  +  0x8)
#define   SYSTICK_CALIB_REG_ADDR         (SYSTICK_BASE_ADDR  +  0xc)


//nvic  registers
#define  NVIC_BASE_ADDR                       (SCS_BASE_ADDR + NVIC_REG_OFFSET)
#define  NVIC_ISER_REG_ADDR(n)                (NVIC_BASE_ADDR + (n) * 4)
#define  NVIC_ICER_REG_ADDR(n)                (NVIC_BASE_ADDR + 0x80 + (n) * 4)
#define  NVIC_ISPR_REG_ADDR(n)                (NVIC_BASE_ADDR + 0x100 + (n) * 4)
#define  NVIC_ICPR_REG_ADDR(n)                (NVIC_BASE_ADDR + 0x180 + (n) * 4)
#define  NVIC_IABR_REG_ADDR(n)                (NVIC_BASE_ADDR + 0x200 + (n) * 4)
#define  NVIC_IPR_REG_ADDR(n)                 (NVIC_BASE_ADDR + 0x300 + (n) * 4)
#define  NVIC_ISER_PERI_INT_WIDTH             1
#define  NVIC_ICER_PERI_INT_WIDTH             1
#define  NVIC_ISPR_PERI_INT_WIDTH             1
#define  NVIC_ICPR_PERI_INT_WIDTH             1
#define  NVIC_IABR_PERI_INT_WIDTH             1
#define  NVIC_IPR_PERI_INT_WIDTH              8



//scb registers
#define  SCB_BASE_ADDR                      (SCS_BASE_ADDR + SCB_REG_OFFSET)
#define  SCB_CPUID_REG_ADDR                 (SCB_BASE_ADDR)
#define  SCB_ICSR_REG_ADDR                  (SCB_BASE_ADDR + 0x4)
#define  SCB_VTOR_REG_ADDR                  (SCB_BASE_ADDR + 0x8)
#define  SCB_AIRCR_REG_ADDR                 (SCB_BASE_ADDR + 0xC)
#define  SCB_SCR_REG_ADDR                   (SCB_BASE_ADDR + 0x10)
#define  SCB_CCR_REG_ADDR                   (SCB_BASE_ADDR + 0x14)
#define  SCB_SHPR1_REG_ADDR                 (SCB_BASE_ADDR + 0x18)
#define  SCB_SHPR2_REG_ADDR                 (SCB_BASE_ADDR + 0x1C)
#define  SCB_SHPR3_REG_ADDR                 (SCB_BASE_ADDR + 0x20)
#define  SCB_SHPRR_REG_ADDR                 (SCB_BASE_ADDR + 0x24)
#define  SCB_CFSR_REG_ADDR                  (SCB_BASE_ADDR + 0x28)
#define  SCB_HFSR_REG_ADDR                  (SCB_BASE_ADDR + 0x2C)
#define  SCB_DFSR_REG_ADDR                  (SCB_BASE_ADDR + 0x30)
#define  SCB_MMFAR_REG_ADDR                 (SCB_BASE_ADDR + 0x34)
#define  SCB_BFAR_REG_ADDR                  (SCB_BASE_ADDR + 0x38)
#define  SCB_AFSR_REG_ADDR                  (SCB_BASE_ADDR + 0x3C)
#define  ID_PFR0_REG_ADDR                   (SCB_BASE_ADDR + 0x40)
#define  ID_PFR1_REG_ADDR                   (SCB_BASE_ADDR + 0x44)
#define  ID_DFR0_REG_ADDR                   (SCB_BASE_ADDR + 0x48)
#define  ID_AFR0_REG_ADDR                   (SCB_BASE_ADDR + 0x4C)
#define  ID_MMFR0_REG_ADDR                  (SCB_BASE_ADDR + 0x50)
#define  ID_MMFR1_REG_ADDR                  (SCB_BASE_ADDR + 0x54)
#define  ID_MMFR2_REG_ADDR                  (SCB_BASE_ADDR + 0x58)
#define  ID_MMFR3_REG_ADDR                  (SCB_BASE_ADDR + 0x5C)
#define  ID_ISAR0_REG_ADDR                  (SCB_BASE_ADDR + 0x60)
#define  ID_ISAR1_REG_ADDR                  (SCB_BASE_ADDR + 0x64)
#define  ID_ISAR2_REG_ADDR                  (SCB_BASE_ADDR + 0x68)
#define  ID_ISAR3_REG_ADDR                  (SCB_BASE_ADDR + 0x6C)
#define  ID_ISAR4_REG_ADDR                  (SCB_BASE_ADDR + 0x70)
#define  ID_ISAR5_REG_ADDR                  (SCB_BASE_ADDR + 0x74)
#define  ID_CLIDR_REG_ADDR                  (SCB_BASE_ADDR + 0x78)
#define  ID_CTR_REG_ADDR                    (SCB_BASE_ADDR + 0x7C)
#define  ID_CCSIDR_REG_ADDR                 (SCB_BASE_ADDR + 0x80)
#define  ID_CSSELR_REG_ADDR                 (SCB_BASE_ADDR + 0x84)
#define  SCB_CPACR_REG_ADDR                 (SCB_BASE_ADDR + 0x88)



//mmu registers
#define  MPU_BASE_ADDR                     (SCS_BASE_ADDR + MPU_REG_OFFSET)
#define  MPU_TYPE_REG_ADDR                 (MPU_BASE_ADDR)
#define  MPU_CTRL_REG_ADDR                 (MPU_BASE_ADDR + 0x4)
#define  MPU_RNR_REG_ADDR                  (MPU_BASE_ADDR + 0x8)
#define  MPU_RBAR_REG_ADDR                 (MPU_BASE_ADDR + 0xC)
#define  MPU_RASR_REG_ADDR                 (MPU_BASE_ADDR + 0x10)
#define  MPU_RBAR_A_REG_ADDR(n)            (MPU_BASE_ADDR + 0x14 + 0x8 * (n))
#define  MPU_RASR_A_REG_ADDR(n)            (MPU_BASE_ADDR + 0x18 + 0x8 * (n))



#define  SCS_STIR_REG_ADDR                 (SCS_BASE_ADDR  + SW_REG_OFFSET)


//fp registers
#define  SCS_FP_BASE_ADDR                  (SCS_STIR_REG_ADDR  +  0x34)
#define  SCS_FPCCR_REG_ADDR                (SCS_FP_BASE_ADDR)
#define  SCS_FPCAR_REG_ADDR                (SCS_FP_BASE_ADDR  +  0x4)
#define  SCS_FPDSCR_REG_ADDR               (SCS_FP_BASE_ADDR  +  0x8)
#define  SCS_FPMVFR_REG_ADDR(n)            (SCS_FP_BASE_ADDR  +  0xC + (n) * 4)



//cache registers
#define  CACHE_BASE_ADDR                    (SCS_BASE_ADDR  +  CACHE_REG_OFFSET)
#define  CAHCE_ICIALLU_REG_ADDR             (CACHE_BASE_ADDR)
#define  CAHCE_ICIMVAU_REG_ADDR             (CACHE_BASE_ADDR  +  0x8)
#define  CAHCE_DCIMVAC_REG_ADDR             (CACHE_BASE_ADDR  +  0xC)
#define  CAHCE_DCISW_REG_ADDR               (CACHE_BASE_ADDR  +  0x10)
#define  CAHCE_DCCMVAU_REG_ADDR             (CACHE_BASE_ADDR  +  0x14)
#define  CAHCE_DCCMVAC_REG_ADDR             (CACHE_BASE_ADDR  +  0x18)
#define  CAHCE_DCCSW_REG_ADDR               (CACHE_BASE_ADDR  +  0x1C)
#define  CAHCE_DCCIMVAC_REG_ADDR            (CACHE_BASE_ADDR  +  0x20)
#define  CAHCE_DCCISW_REG_ADDR              (CACHE_BASE_ADDR  +  0x24)
#define  CAHCE_BPIALL_REG_ADDR              (CACHE_BASE_ADDR  +  0x28)



#define  REG32_READ(addr)       (*((volatile uint32_t *)(addr)))
#define  REG32_WRITE(addr, val)      (*((volatile uint32_t *)(addr)) = (val))
#define  REG32_UPDATE(addr, val,  mask)  {          \
                                uint32_t  tmp  =  REG32_READ((addr));   \
                                tmp   &=  (~(mask));              \
                                tmp   |=  ((val) & (mask));       \
                                REG32_WRITE(addr,  tmp);          \
                                }




#endif



