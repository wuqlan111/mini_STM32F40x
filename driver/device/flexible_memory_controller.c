
#include  <stdlib.h>

#include  "flexible_memory_controller.h"



#define  FSMC_REGS_BASE_ADDR                   (0xA0000000u)
#define  FSMC_BCRX_REG_ADDR(n)                 (FSMC_REGS_BASE_ADDR + (n) * 0x8)
#define  FSMC_BTRX_REG_ADDR(n)                 (FSMC_REGS_BASE_ADDR + (n) * 0x8 + 0x4)
#define  FSMC_BWTRX_REG_ADDR(n)                (FSMC_REGS_BASE_ADDR + (n) * 0x8 + 0x104)


















