
#include  <stdlib.h>

#include  "flexible_memory_controller.h"
#include  "../include/driver_util.h"
#include  "../../subsys/include/console.h"



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



static  int32_t  fsmc_psram_init_control(fsmc_memory_bank_e fsmc_bank,  fsmc_bank_control_t  * cfg)
{
    uint32_t  flag, mask,offset;
    flag   =  mask  =  offset  =  0;
    CHECK_PARAM_NULL(cfg);
    CHECK_PARAM_VALUE(fsmc_bank,   FSMC_PSRAM_BANK4);

    CHECK_PARAM_VALUE(cfg->sram_cfg.cram_page_size,  FSMC_CRAM_PAGE_1024);
    CHECK_PARAM_VALUE(cfg->sram_cfg.memory_width,  FSMC_MEMORY_MAX_WIDTH);
    CHECK_PARAM_VALUE(cfg->sram_cfg.memory_type,  FSMC_MEMORY_MAX_TYPE);

    flag    =   cfg->sram_cfg.cram_page_size  << 16;
    flag   |=   cfg->sram_cfg.memory_width    << 4;
    flag   |=   cfg->sram_cfg.memory_type     << 2;

    if (cfg->sram_cfg.write_burst) {
        flag  |=   1 << 19;
    }

    if (cfg->sram_cfg.async_wait) {
        flag  |=  1 << 15;
    }

    if (cfg->sram_cfg.ext_mode) {
        flag  |=  1 <<  14;
    }

    if (cfg->sram_cfg.wait_enable) {
        flag  |=  1 << 13;
    }

    if (cfg->sram_cfg.write_enable) {
        flag  |=  1 << 12;
    }

    if (cfg->sram_cfg.wait_active_high) {
        flag  |=  1  << 9;
    }

    if (cfg->sram_cfg.burst_enable) {
        flag  |=  1  << 8;
    }


    mask   =   0x7f33c;

    offset   =   fsmc_bank  - FSMC_PSRAM_BANK1;
    REG32_UPDATE(FSMC_BCRX_REG_ADDR(offset),  flag,  mask);

    return   0;

}



static  int32_t  fsmc_nand_flash_init_control(fsmc_memory_bank_e fsmc_bank,  fsmc_bank_control_t  * cfg)
{
    uint32_t  flag, mask,offset;
    flag   =  mask  =  offset  =  0;
    CHECK_PARAM_NULL(cfg);
    CHECK_PARAM_VALUE(fsmc_bank,   FSMC_MEMORY_MAX_BANK);

    if (fsmc_bank < FSMC_NAND_FLASH_BANK2) {
        return  -1;
    }

    CHECK_PARAM_VALUE(cfg->nand_flash_cfg.ecc_page_size,  FSMC_ECC_MAX_PAGE);
    CHECK_PARAM_VALUE(cfg->nand_flash_cfg.pbus_width,  FSMC_MEMORY_MAX_WIDTH);

    flag    =   cfg->nand_flash_cfg.ecc_page_size  <<  17;
    flag   |=   cfg->nand_flash_cfg.ale_re_delay   <<  13;
    flag   |=   cfg->nand_flash_cfg.cle_re_delay   <<  9;
    flag   |=   cfg->nand_flash_cfg.pbus_width   << 4;

    if (cfg->nand_flash_cfg.ecc_enable) {
        flag  |=  1 << 6;
    }

    if (cfg->nand_flash_cfg.nand_flash) {
        flag  |=  1 << 3;
    }

    if (cfg->nand_flash_cfg.wait_enable) {
        flag  |=  0x2;
    }


    mask   =   0xff77a;

    offset   =   fsmc_bank  - FSMC_NAND_FLASH_BANK2;
    REG32_UPDATE(FSMC_PCRX_REG_ADDR(offset),  flag,  mask);

    return   0;

}





int32_t  fsmc_memory_init_control(fsmc_memory_bank_e fsmc_bank,  fsmc_bank_control_t  * cfg)
{
    int32_t   ret  =  0;
    CHECK_PARAM_NULL(cfg);
    CHECK_PARAM_VALUE(fsmc_bank,  FSMC_MEMORY_MAX_BANK);

    if (fsmc_bank < FSMC_NAND_FLASH_BANK2) {
        ret  =   fsmc_psram_init_control(fsmc_bank,  cfg);
    } else {
        ret  =   fsmc_nand_flash_init_control(fsmc_bank,  cfg);
    }
    
    return   ret;

}





int32_t   fsmc_memory_bank_enable_or_disable(fsmc_memory_bank_e fsmc_bank, uint32_t enable)
{

    uint32_t  flag,  mask,  offset;
    flag  =  mask   = offset   =  0;
    CHECK_PARAM_VALUE(fsmc_bank,  FSMC_MEMORY_MAX_BANK);


    if (fsmc_bank  <  FSMC_NAND_FLASH_BANK2) {
        flag   =  enable?  0x1:  0;
        mask   =  0x1;
        offset   =   fsmc_bank  -  FSMC_PSRAM_BANK1;

        REG32_UPDATE(FSMC_BCRX_REG_ADDR(offset),   flag,  mask);
    } else {
        flag  =  enable? 0x2:  0;
        mask  =  0x2;
        offset   =   fsmc_bank  -  FSMC_NAND_FLASH_BANK2;

        REG32_UPDATE(FSMC_PCRX_REG_ADDR(offset),   flag,  mask);
    }

    return   0;

}






int32_t  fsmc_set_psram_time(fsmc_memory_bank_e fsmc_bank, uint32_t  read_time, fsmc_transfer_time_t * cfg)
{
    uint32_t  flag, offset;
    flag =  offset  =  0;
    int32_t  ret  =   0;

    CHECK_PARAM_NULL(cfg);
    CHECK_PARAM_VALUE(fsmc_bank,  FSMC_PSRAM_BANK4);

    offset  =   fsmc_bank  -  FSMC_PSRAM_BANK1;

    uint32_t  psram_cfg  =  REG32_READ(FSMC_BCRX_REG_ADDR(offset));
    uint32_t  memory_type  =  (psram_cfg & FSMC_PCRX_PTYP) >> 3;


    if (cfg->sram_time.data_latency && (memory_type == FSMC_MEMORY_PSRAM)) {
        DEBUG_PRINTF_ERROR("data latency for psram must set 0!");
        return  -1;
    }

    flag    =   cfg->sram_time.access_mode  << 28;
    flag   |=   cfg->sram_time.bus_turn_phase   <<  16;
    flag   |=   cfg->sram_time.data_phase   <<   8;
    flag   |=   cfg->sram_time.addr_hold_phase    <<  4;
    flag   |=   cfg->sram_time.addr_setup_phase;

    if (read_time) {
        flag   |=   cfg->sram_time.data_latency   <<  24;
        flag   |=   cfg->sram_time.clkdiv   <<  20;
    }


    if (read_time) {
        REG32_WRITE(FSMC_BTRX_REG_ADDR(offset),  flag);
    } else {
        REG32_WRITE(FSMC_BWTRX_REG_ADDR(offset),  flag);
    }

    return   0;

}



int32_t  fsmc_set_nand_flash_time(fsmc_memory_bank_e fsmc_bank,  fsmc_transfer_time_t * cfg);








int32_t  fsmc_set_pio_time(fsmc_memory_bank_e fsmc_bank,  fsmc_transfer_time_t * cfg);



















