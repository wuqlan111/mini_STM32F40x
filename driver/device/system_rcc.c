
#include  <stdlib.h>
#include  <memory.h>

#include  "../include/system_rcc.h"
#include  "../include/driver_util.h"
#include  "util.h"



#define  RCC_REGISTER_BASE_ADDR              (0x40023800u)
#define  RCC_CR_REG_ADDR                (RCC_REGISTER_BASE_ADDR)
#define  RCC_PLLCR_REG_ADDR             (RCC_REGISTER_BASE_ADDR + 0x4)
#define  RCC_CFGR_REG_ADDR              (RCC_REGISTER_BASE_ADDR + 0x8)
#define  RCC_CIR_REG_ADDR               (RCC_REGISTER_BASE_ADDR + 0xc)
#define  RCC_AHBXRSTR_REG_ADDR(ahb)     (RCC_REGISTER_BASE_ADDR + 0x10 + ((ahb) - RCC_AHB1_CLK) * 4)
#define  RCC_APBXRSTR_REG_ADDR(apb)     (RCC_REGISTER_BASE_ADDR + 0x20 + ((apb) - RCC_APB1_CLK) * 4)
#define  RCC_AHBXENR_REG_ADDR(ahb)      (RCC_REGISTER_BASE_ADDR + 0x30 + ((ahb) - RCC_AHB1_CLK) * 4)
#define  RCC_APBXENR_REG_ADDR(apb)      (RCC_REGISTER_BASE_ADDR + 0x40 + ((apb) - RCC_APB1_CLK) * 4)
#define  RCC_AHBXLPENR_REG_ADDR(ahb)    (RCC_REGISTER_BASE_ADDR + 0x50 + ((ahb) - RCC_AHB1_CLK) * 4)
#define  RCC_APBXLPENR_REG_ADDR(apb)    (RCC_REGISTER_BASE_ADDR + 0x60 + ((apb) - RCC_APB1_CLK) * 4)
#define  RCC_BDCR_REG_ADDR              (RCC_REGISTER_BASE_ADDR + 0x70)
#define  RCC_CSR_REG_ADDR               (RCC_REGISTER_BASE_ADDR + 0x74)
#define  RCC_SSCGR_REG_ADDR             (RCC_REGISTER_BASE_ADDR + 0x80)
#define  RCC_PLLI2SCFGR_REG_ADDR        (RCC_REGISTER_BASE_ADDR + 0x84)


static  int32_t  set_ahb1_module_op(rcc_module_e  module,  rcc_module_op_e  op)
{
    uint32_t  flag,   mask, shift;
    flag  =  mask   =  shift  =  0;

    CHECK_PARAM_VALUE(module, RCC_MODULE_AHB1_MAX );
    CHECK_PARAM_VALUE(op,   RCC_MODULE_MAX_OP);

    switch (op) {
        case  RCC_RESET_OP:
            flag  =   1;
        case  RCC_UNRESET_OP:
            mask  =   1;

            if (module  < RCC_MODULE_CRC) {
                shift  =  module - RCC_MODULE_GPIOA;
            } else if (module < RCC_MODULE_DMA1) {
                shift  =  module - RCC_MODULE_CRC + 12;
            } else if (module < RCC_MODULE_ETHMAC) {
                shift  =  module - RCC_MODULE_DMA1 + 21;
            } else if (module < RCC_MODULE_OTGFS) {
                shift  =  module - RCC_MODULE_ETHMAC + 25;
            } else {
                shift  =  module - RCC_MODULE_OTGHS + 29;
            }

            flag  <<= shift;
            mask  <<= shift;
            
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_ENABLE_LOWER_POWER:
            if (module == RCC_MODULE_ETHMAC) {
                flag  =  0xf;
            } else if (module ==  RCC_MODULE_OTGHS) {
                flag  =  0x3;
            } else {
                flag  =  1;
            }

        case  RCC_CLK_DISABLE:
        case  RCC_CLK_DISABLE_LOWER_POWER:

            if (module == RCC_MODULE_ETHMAC) {
                mask  =  0xf;
            } else if (module ==  RCC_MODULE_OTGHS) {
                mask  =  0x3;
            } else {
                mask  =  1;
            }

            if (module  < RCC_MODULE_CRC) {
                shift  =  module - RCC_MODULE_GPIOA;
            } else if (module < RCC_MODULE_DMA1) {
                shift  =  module - RCC_MODULE_CRC + 12;
            } else if (module < RCC_MODULE_ETHMAC) {
                shift  =  module - RCC_MODULE_DMA1 + 21;
            } else if (module < RCC_MODULE_OTGFS) {
                shift  =  module - RCC_MODULE_ETHMAC + 25;
            } else {
                shift  =  module - RCC_MODULE_OTGHS + 29;
            }
            flag  <<= shift;
            mask  <<= shift;
    }


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_UNRESET_OP:
            REG32_UPDATE(RCC_AHBXRSTR_REG_ADDR(RCC_AHB1_CLK), flag,  mask);
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_DISABLE:
            REG32_UPDATE(RCC_AHBXENR_REG_ADDR(RCC_AHB1_CLK), flag,  mask);
            break;
        
        default:
            REG32_UPDATE(RCC_AHBXLPENR_REG_ADDR(RCC_AHB1_CLK), flag,  mask);
            
    }

    return   0;

}



















int32_t  rcc_module_set_op(rcc_module_e  module,  rcc_module_op_e  op)
{

    CHECK_PARAM_VALUE(module,  RCC_MODULE_MAX);
    CHECK_PARAM_VALUE(op,      RCC_MODULE_MAX_OP);







    return  0;
}











