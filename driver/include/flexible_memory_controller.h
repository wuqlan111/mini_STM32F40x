

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


typedef  union {
    struct {
        uint32_t   write_burst:1;
        uint32_t   cram_page_size:3;
        uint32_t   async_wait:1;
        uint32_t   ext_mode:1;
        uint32_t   wait_enable:1;
        uint32_t   write_enable:1;
        uint32_t   write_burst:1;
        uint32_t   wait_active_high:1;
        uint32_t   burst_enable:1;
        uint32_t   memory_width:2;
        uint32_t   memory_type:2;
        uint32_t   addr_multiplex:1;
    } sram_cfg;

    struct {
        uint32_t   ecc_page_size:3;
        uint32_t   ale_re_delay:4;
        uint32_t   cle_re_delay:4;
        uint32_t   ecc_enable:1;
        uint32_t   pbus_width:2;
        uint32_t   nand_flash:1;
        uint32_t   wait_enable:1;
    } nand_flash_cfg;
} fsmc_bank_control_t;




typedef  union {
    struct  {
        uint32_t  access_mode:2;
        uint32_t  bus_turn_phase:4;
        uint32_t  data_phase:8;
        uint32_t  addr_hold_phase:4;
        uint32_t  addr_setup_phase:4;
    } sram_time;

    struct  {
        uint32_t  memory_hiz_time:2;
        uint32_t  memory_hold_time:4;
        uint32_t  memory_wait_time:8;
        uint32_t  memory_setup_time:4;
    } sram_time;
} fsmc_transfer_time_t;
















#endif

