
#include  <stdlib.h>
#include  <memory.h>

#include  "../include/system_rcc.h"
#include  "../include/driver_util.h"
#include  "util.h"


#define  RCC_CR_PLLI2SRDY             (1<<27u)
#define  RCC_CR_PLLI2SON              (1<<26u)
#define  RCC_CR_PLLRDY                (1<<25u)
#define  RCC_CR_PLLON                 (1<<24u)
#define  RCC_CR_CSSON                 (1<<19u)
#define  RCC_CR_HSEBYP                (1<<18u)
#define  RCC_CR_HSERDY                (1<<17u)
#define  RCC_CR_HSEON                 (1<<16u)
#define  RCC_CR_HSICAL                (0xff00u)
#define  RCC_CR_HSITRIM               (0xf8u)
#define  RCC_CR_HSIRDY                (0x2u)
#define  RCC_CR_HSION                 (0x1u)

#define  RCC_PLLCR_PLLQ               (0xf<<24u)
#define  RCC_PLLCR_PLLSRC             (1<<22u)
#define  RCC_PLLCR_PLLP               (0x3<<16u)
#define  RCC_PLLCR_PLLN               (0x1ff<<6u)
#define  RCC_PLLCR_PLLM               (0x3fu)



#define  RCC_CFGR_MCO2               (0x3<<30u)
#define  RCC_CFGR_MCO2PRE            (0x7<<27u)
#define  RCC_CFGR_MCO1PRE            (0x7<<24u)
#define  RCC_CFGR_I2SSRC             (1<<23u)
#define  RCC_CFGR_MCO1               (0x3<<21u)
#define  RCC_CFGR_RTCPRE             (0x1f<<16u)
#define  RCC_CFGR_PPRE2              (0x7<<13u)
#define  RCC_CFGR_PPRE1              (0x7<<10u)
#define  RCC_CFGR_HPRE               (0xf0u)
#define  RCC_CFGR_SWS                (0xcu)
#define  RCC_CFGR_SW                 (0x3u)





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




static  int32_t  set_ahb2_module_op(rcc_module_e  module,  rcc_module_op_e  op)
{
    uint32_t  flag,   mask, shift;
    flag  =  mask   =  shift  =  0;

    if (module <= RCC_MODULE_AHB1_MAX) {
        return  -1;
    }

    CHECK_PARAM_VALUE(module, RCC_MODULE_AHB2_MAX );
    CHECK_PARAM_VALUE(op,   RCC_MODULE_MAX_OP);


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_CLK_ENABLE:
        case  RCC_CLK_ENABLE_LOWER_POWER:
            flag  =   1;
        case  RCC_UNRESET_OP:
        case  RCC_CLK_DISABLE:
        case  RCC_CLK_DISABLE_LOWER_POWER:
            mask  =   1;

            if (module  < RCC_MODULE_CRYP) {
                shift  =  module - RCC_MODULE_CRYP;
            } else {
                shift  =  module - RCC_MODULE_CRYP + 4;
            }

            flag  <<= shift;
            mask  <<= shift;
    }


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_UNRESET_OP:
            REG32_UPDATE(RCC_AHBXRSTR_REG_ADDR(RCC_AHB2_CLK), flag,  mask);
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_DISABLE:
            REG32_UPDATE(RCC_AHBXENR_REG_ADDR(RCC_AHB2_CLK), flag,  mask);
            break;
        
        default:
            REG32_UPDATE(RCC_AHBXLPENR_REG_ADDR(RCC_AHB2_CLK), flag,  mask);
            
    }

    return   0;

}


static  int32_t  set_ahb3_module_op(rcc_module_e  module,  rcc_module_op_e  op)
{
    uint32_t  flag,   mask, shift;
    flag  =  mask   =  shift  =  0;

    if (module <= RCC_MODULE_AHB2_MAX) {
        return  -1;
    }

    CHECK_PARAM_VALUE(module, RCC_MODULE_AHB3_MAX );
    CHECK_PARAM_VALUE(op,   RCC_MODULE_MAX_OP);


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_CLK_ENABLE:
        case  RCC_CLK_ENABLE_LOWER_POWER:
            flag  =   1;
        case  RCC_UNRESET_OP:
        case  RCC_CLK_DISABLE:
        case  RCC_CLK_DISABLE_LOWER_POWER:
            mask  =   1;
            shift  =   0;

            flag  <<= shift;
            mask  <<= shift;
    }


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_UNRESET_OP:
            REG32_UPDATE(RCC_AHBXRSTR_REG_ADDR(RCC_AHB3_CLK), flag,  mask);
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_DISABLE:
            REG32_UPDATE(RCC_AHBXENR_REG_ADDR(RCC_AHB3_CLK), flag,  mask);
            break;
        
        default:
            REG32_UPDATE(RCC_AHBXLPENR_REG_ADDR(RCC_AHB3_CLK), flag,  mask);
            
    }

    return   0;

}




static  int32_t  set_apb1_module_op(rcc_module_e  module,  rcc_module_op_e  op)
{
    uint32_t  flag,   mask, shift;
    flag  =  mask   =  shift  =  0;

    if (module <= RCC_MODULE_AHB3_MAX) {
        return  -1;
    }

    CHECK_PARAM_VALUE(module, RCC_MODULE_APB1_MAX );
    CHECK_PARAM_VALUE(op,   RCC_MODULE_MAX_OP);


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_CLK_ENABLE:
        case  RCC_CLK_ENABLE_LOWER_POWER:
            flag  =   1;
        case  RCC_UNRESET_OP:
        case  RCC_CLK_DISABLE:
        case  RCC_CLK_DISABLE_LOWER_POWER:
            mask  =   1;

            if (module  < RCC_MODULE_WWDG) {
                shift  =  module - RCC_MODULE_TIM2;
            } else if (module  < RCC_MODULE_SPI2) {
                shift  =  module - RCC_MODULE_WWDG + 11;
            } else if (module  < RCC_MODULE_USART2) {
                shift  =  module - RCC_MODULE_SPI2 + 14;
            } else if (module  < RCC_MODULE_CAN1) {
                shift  =  module - RCC_MODULE_USART2 + 17;
            } else if (module  < RCC_MODULE_PWR) {
                shift  =  module - RCC_MODULE_CAN1 + 25;
            } else {
                shift  =  module - RCC_MODULE_PWR + 28;
            }

            flag  <<= shift;
            mask  <<= shift;
    }


    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_UNRESET_OP:
            REG32_UPDATE(RCC_APBXRSTR_REG_ADDR(RCC_APB1_CLK), flag,  mask);
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_DISABLE:
            REG32_UPDATE(RCC_APBXENR_REG_ADDR(RCC_APB1_CLK), flag,  mask);
            break;
        
        default:
            REG32_UPDATE(RCC_APBXLPENR_REG_ADDR(RCC_APB1_CLK), flag,  mask);
            
    }

    return   0;

}


static  int32_t  set_apb2_module_op(rcc_module_e  module,  rcc_module_op_e  op)
{
    uint32_t  flag,   mask, shift;
    flag  =  mask   =  shift  =  0;

    if (module <= RCC_MODULE_APB1_MAX) {
        return  -1;
    }

    CHECK_PARAM_VALUE(module, RCC_MODULE_APB1_MAX );
    CHECK_PARAM_VALUE(op,   RCC_MODULE_MAX_OP);

    switch (op) {
        case  RCC_RESET_OP:
            flag  =   1;
        case  RCC_UNRESET_OP:
            mask  =   1;
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_ENABLE_LOWER_POWER:
            if (module == RCC_MODULE_ADC) {
                flag  =  0x7;
            } else {
                flag  =  1;
            }

        case  RCC_CLK_DISABLE:
        case  RCC_CLK_DISABLE_LOWER_POWER:

            if (module == RCC_MODULE_ADC) {
                mask  =  0x7;
            } else {
                mask  =  1;
            }
    }

    if (module  < RCC_MODULE_USART1) {
        shift  =  module - RCC_MODULE_TIM1;
    } else if (module < RCC_MODULE_ADC) {
        shift  =  module - RCC_MODULE_USART1 + 4;
    } else if (module < RCC_MODULE_SDIO) {
        shift  =  module - RCC_MODULE_ADC + 8;
    } else if (module < RCC_MODULE_SYSCFG) {
        shift  =  module - RCC_MODULE_SDIO + 11;
    } else if (module < RCC_MODULE_TIM9) {
        shift  =  module - RCC_MODULE_SYSCFG + 14;
    } else {
        shift  =  module - RCC_MODULE_TIM9 + 16;
    }

    flag  <<=   shift;
    mask  <<=   shift;

    switch (op) {
        case  RCC_RESET_OP:
        case  RCC_UNRESET_OP:
            REG32_UPDATE(RCC_APBXRSTR_REG_ADDR(RCC_APB2_CLK), flag,  mask);
            break;

        case  RCC_CLK_ENABLE:
        case  RCC_CLK_DISABLE:
            REG32_UPDATE(RCC_APBXENR_REG_ADDR(RCC_APB2_CLK), flag,  mask);
            break;
        
        default:
            REG32_UPDATE(RCC_APBXLPENR_REG_ADDR(RCC_APB2_CLK), flag,  mask);
            
    }

    return   0;

}




int32_t  rcc_module_set_op(rcc_module_e  module,  rcc_module_op_e  op)
{
    int32_t  ret  =  0;
    CHECK_PARAM_VALUE(module,  RCC_MODULE_MAX);
    CHECK_PARAM_VALUE(op,      RCC_MODULE_MAX_OP);

    if (module <= RCC_MODULE_AHB1_MAX) {
        ret  =  set_ahb1_module_op(module, op);
    } else if (module <=  RCC_MODULE_AHB2_MAX) {
        ret  =  set_ahb2_module_op(module, op);
    } else if (module <=  RCC_MODULE_AHB3_MAX) {
        ret  =  set_ahb3_module_op(module, op);
    } else if (module <=  RCC_MODULE_APB1_MAX) {
        ret  =  set_apb1_module_op(module, op);
    } else {
        ret  =  set_apb2_module_op(module, op);
    }

    return  ret;
}











