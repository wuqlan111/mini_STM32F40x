

#ifndef  STM32_FLEXIBLE_MEMORY_CONTROLLER_H
#define  STM32_FLEXIBLE_MEMORY_CONTROLLER_H

#include  <stdint.h>
#include  "util.h"




typedef enum {
    FSMC_CRAM_PAGE_128  =  1,
    FSMC_CRAM_PAGE_256,
    FSMC_CRAM_PAGE_512,
    FSMC_CRAM_PAGE_1024,
    FSMC_CRAM_MAX_PAGE  =  FSMC_CRAM_PAGE_1024,
} fsmc_cram_page_size_e;


typedef enum {
    FSMC_MEMORY_WIDTH_8  =  0,
    FSMC_MEMORY_WIDTH_16,
    FSMC_MEMORY_MAX_WIDTH  =  FSMC_MEMORY_WIDTH_16,
} fsmc_memory_width_e;



typedef enum {
    FSMC_MEMORY_SRAM  =  0,
    FSMC_MEMORY_PSRAM,
    FSMC_MEMORY_NOR_FLASH,
    FSMC_MEMORY_MAX_TYPE  =  FSMC_MEMORY_NOR_FLASH,
} fsmc_memory_type_e;


typedef enum {
    FSMC_ACCESS_MODE_A  =  0,
    FSMC_ACCESS_MODE_B,
    FSMC_ACCESS_MODE_C,
    FSMC_ACCESS_MODE_D,
    FSMC_ACCESS_MAX_MODE  =  FSMC_ACCESS_MODE_D,
} fsmc_access_mode_e;









#endif

