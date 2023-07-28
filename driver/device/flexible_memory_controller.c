
#include  <stdlib.h>

#include  "flexible_memory_controller.h"




#define   PSRAM_BASE_ADDR             (0x60000000u)
#define   NAND_FLASH_BASE_ADDR        (0x70000000u)
#define   PC_CARD_BASE_ADDR           (0x90000000u)

#define  FSMC_REGS_BASE_ADDR                   (0xA0000000u)
#define  FSMC_BCRX_REG_ADDR(n)                 (FSMC_REGS_BASE_ADDR + (n) * 0x8)
#define  FSMC_BTRX_REG_ADDR(n)                 (FSMC_REGS_BASE_ADDR + (n) * 0x8 + 0x4)
#define  FSMC_BWTRX_REG_ADDR(n)                (FSMC_REGS_BASE_ADDR + (n) * 0x8 + 0x104)
#define  FSMC_PCRX_REG_ADDR(n)                 (FSMC_REGS_BASE_ADDR + (n) * 0x20 + 0x60)
#define  FSMC_SRX_REG_ADDR(n)                  (FSMC_REGS_BASE_ADDR + (n) * 0x20 + 0x64)
#define  FSMC_PMEMX_REG_ADDR(n)                (FSMC_REGS_BASE_ADDR + (n) * 0x20 + 0x68)
#define  FSMC_PATTX_REG_ADDR(n)                (FSMC_REGS_BASE_ADDR + (n) * 0x20 + 0x6c)
#define  FSMC_PIO4_REG_ADDR                    (FSMC_REGS_BASE_ADDR + 0xb0)
#define  FSMC_ECCRX_REG_ADDR(n)                (FSMC_REGS_BASE_ADDR + (n) * 0x20 + 0x74)



#define   FSMC_BCRX_CBURSTRW               (1<<19u)
#define   FSMC_BCRX_CPSIZE                 (0x7<<16u)
#define   FSMC_BCRX_ASYNCWAIT              (1<<15u)
#define   FSMC_BCRX_EXTMOD                 (1<<14u)
#define   FSMC_BCRX_WAITEN                 (1<<13u)
#define   FSMC_BCRX_WREN                   (1<<12u)
#define   FSMC_BCRX_WAITCFG                (1<<11u)
#define   FSMC_BCRX_WRAPMOD                (1<<10u)
#define   FSMC_BCRX_WAITPOL                (1<<9u)
#define   FSMC_BCRX_BURSTEN                (1<<8u)
#define   FSMC_BCRX_FACCEN                 (1<<6u)
#define   FSMC_BCRX_MWID                   (0x3<<4u)
#define   FSMC_BCRX_MTYP                   (0x3<<2u)
#define   FSMC_BCRX_MUXEN                  (0x2u)
#define   FSMC_BCRX_MBKEN                  (0x1u)



#define   FSMC_BTRX_ACCMOD                 (0x3<<28u)
#define   FSMC_BTRX_DATLAT                 (0xf<<24u)
#define   FSMC_BTRX_CLKDIV                 (0xf<<20u)
#define   FSMC_BTRX_BUSTURN                (0xf<<16u)
#define   FSMC_BTRX_DATAST                 (0xff<<8u)
#define   FSMC_BTRX_ADDHLD                 (0xf<<4u)
#define   FSMC_BTRX_ADDSET                 (0xf<u)


#define  FSMC_BWTRX_ACCMOD                 (0x3<<28u)
#define  FSMC_BWTRX_BUSTURN                (0xf<<16u)
#define  FSMC_BWTRX_DATAST                 (0xff<<8u)
#define  FSMC_BWTRX_ADDHLD                 (0xf<<4u)
#define  FSMC_BWTRX_ADDSET                 (0xfu)


#define  FSMC_PCRX_ECCPS            (0x7<<17u)
#define  FSMC_PCRX_TAR              (0x7<<13u)
#define  FSMC_PCRX_TCLR             (0x7<<9u)
#define  FSMC_PCRX_ECCEN            (1<<6u)
#define  FSMC_PCRX_PWID             (0x3<<4u)
#define  FSMC_PCRX_PTYP             (1<<3u) 
#define  FSMC_PCRX_PBKEN            (1<<2u)
#define  FSMC_PCRX_PWAITEN          (0x2u)



#define  FSMC_SRX_FEMPT              (1<<6u)
#define  FSMC_SRX_IFEN               (1<<5u)
#define  FSMC_SRX_ILEN               (1<<4u)
#define  FSMC_SRX_IREN               (1<<3u)
#define  FSMC_SRX_IFS                (1<<2u)
#define  FSMC_SRX_ILS                (0x2u)
#define  FSMC_SRX_IRS                (0x1u)



#define   FSMC_PMEMX_MEMHIZX            (0xff<<24u)
#define   FSMC_PMEMX_MEMHOLDX           (0xff<<16u)
#define   FSMC_PMEMX_MEMWAITX           (0xff<<8u)
#define   FSMC_PMEMX_MEMSETX            (0xffu)



#define   FSMC_PATT_ATTHIZ              (0xff<<24u)
#define   FSMC_PATT_ATTHOLD             (0xff<<16u)
#define   FSMC_PATT_ATTWAIT             (0xff<<8u)
#define   FSMC_PATT_ATTSET              (0xffu)



#define  FSMC_PIO4_IOHIZ                (0xff<<24u)
#define  FSMC_PIO4_IOHOLD               (0xff<<16u)
#define  FSMC_PIO4_IOWAIT               (0xff<<8u)
#define  FSMC_PIO4_IOSET                (0xffu)

















