
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

#define  RCC_PLLCFGR_PLLQ               (0xf<<24u)
#define  RCC_PLLCFGR_PLLSRC             (1<<22u)
#define  RCC_PLLCFGR_PLLP               (0x3<<16u)
#define  RCC_PLLCFGR_PLLN               (0x1ff<<6u)
#define  RCC_PLLCFGR_PLLM               (0x3fu)



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

#define  RCC_BDCR_BDRST               (1<<16u)
#define  RCC_BDCR_RTCEN               (1<<15u)
#define  RCC_BDCR_RTCSEL              (0x3<<8u)
#define  RCC_BDCR_LSEBYP              (0x4u)
#define  RCC_BDCR_LSERDY              (0x2u)
#define  RCC_BDCR_LSEON               (0x1u)



#define  RCC_CSR_LPWRRSTF             (1<<31u)
#define  RCC_CSR_WWDGRSTF             (1<<30u)
#define  RCC_CSR_IWDGRSTF             (1<<29u)
#define  RCC_CSR_SFTRSTF              (1<<28u)
#define  RCC_CSR_PORRSTF              (1<<27u)
#define  RCC_CSR_PINRSTF              (1<<26u)
#define  RCC_CSR_BORRSTF              (1<<25u)
#define  RCC_CSR_RMVF                 (1<<24u)
#define  RCC_CSR_LSIRDY               (0x2u)
#define  RCC_CSR_LSION                (0x1u)




#define  RCC_REGISTER_BASE_ADDR              (0x40023800u)
#define  RCC_CR_REG_ADDR                (RCC_REGISTER_BASE_ADDR)
#define  RCC_PLLCFGR_REG_ADDR             (RCC_REGISTER_BASE_ADDR + 0x4)
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


#define   RCC_HSI_CLK_FREQUENCY            16         // 16MHz     
#define   RCC_HSE_CLK_FREQUENCY            8          // 8MHz
#define   RCC_USB_OTG_FREQUENCY            48         // 48MHz
#define   RCC_VCO_MAX_INPUT_FREQUENCY                 2         // 2MHz
#define   RCC_VCO_MIN_INPUT_FREQUENCY                 1         // 2MHz
#define   RCC_VCO_MAX_OUTPUT_FREQUENCY                432         // 432MHz
#define   RCC_VCO_MIN_OUTPUT_FREQUENCY                100         // 100MHz
#define   RCC_PLL_MAX_FREQUENCY                    168         // 168MHz
#define   RCC_PLLCFGR_MIN_PLLQ                      2
#define   RCC_PLLCFGR_MAX_PLLQ                      15
#define   RCC_PLLCFGR_MIN_PLLN                      50
#define   RCC_PLLCFGR_MAX_PLLN                      432
#define   RCC_PLLCFGR_MIN_PLLM                      2
#define   RCC_PLLCFGR_MAX_PLLM                      63




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



int32_t  rcc_set_clk_state(rcc_system_clk_e clk_type, uint32_t  enable)
{
    uint32_t  shift, reg;
    shift  =  reg  =  0;

    CHECK_PARAM_VALUE(clk_type,  RCC_MAX_CLK);


    switch (clk_type) {
        case  RCC_HSI_CLK:
            shift  =  0;
            break;
        case  RCC_HSE_CLK:
            shift  =  16;
            break;
        case  RCC_PLL_CLK:
            shift  =  24;
            break;
        case  RCC_PLLI2S_CLK:
            shift  =  26;
            break;
        case  RCC_LSE_CLK:
        case  RCC_LSI_CLK:
            shift  =  0;
    }

    uint32_t  flag  =  enable? 1<<shift: 0;
    uint32_t  mask  =  1 << shift;

    if (clk_type  <= RCC_PLLI2S_CLK) {
        reg  =  RCC_CFGR_REG_ADDR;
    } else if (clk_type  ==  RCC_LSE_CLK) {
        reg  =  RCC_BDCR_REG_ADDR;
    } else {
        reg  =  RCC_CSR_REG_ADDR;
    }

    REG32_UPDATE(reg,  flag,  mask);

    REG32_WAIT(reg,  flag << 1,  mask << 1);

    return  0;

}

int32_t  rcc_set_clk_bypass_oscillator(rcc_system_clk_e clk_type, uint32_t  bypass)
{
    uint32_t  reg, shift;
    reg = shift  =  0;

    if ( (clk_type !=  RCC_HSE_CLK) && (clk_type != RCC_LSE_CLK)) {
        return  -1;
    }

    if (clk_type == RCC_HSE_CLK) {
        reg  =  RCC_CFGR_REG_ADDR;
        shift  = 18;
    } else {
        reg  =  RCC_BDCR_REG_ADDR;
        shift  =  2;
    }

    uint32_t  flag  =  bypass? 1 << shift:  0;
    uint32_t  mask  =  1 << shift;

    REG32_UPDATE(reg,  flag,  mask); 

    return   0;

}




int32_t  rcc_switch_system_clk_source(rcc_system_clk_select_e  clk_type)
{
    uint32_t  flag,  mask;
    flag  =  mask  =  0;
    CHECK_PARAM_VALUE(clk_type,  RCC_SYSTEM_CLK_MAX);

    switch (clk_type) {
        case RCC_SYSTEM_CLK_HSE:
            flag  =  1;
            break;
        case RCC_SYSTEM_CLK_PLL:
            flag  =  2;
    }

    mask  =  0x3;

    REG32_UPDATE(RCC_CFGR_REG_ADDR,  flag,  mask);

    flag  <<=  2;
    mask  <<=  2;

    REG32_WAIT(RCC_CFGR_REG_ADDR,  flag,  mask);

    return   0;

}



int32_t  rcc_set_pll_clk_frequency(uint32_t  freq)
{
    uint32_t  flag,  mask;
    flag = mask  =  0;

    CHECK_PARAM_VALUE(freq,  RCC_PLL_MAX_FREQUENCY);

    flag  = REG32_READ(RCC_CFGR_REG_ADDR);

    uint32_t  pll_input_clk  =   0;
    if (flag | RCC_PLLCFGR_PLLSRC) {
        pll_input_clk  =  RCC_HSE_CLK_FREQUENCY;
    } else {
        pll_input_clk  =  RCC_HSI_CLK_FREQUENCY;
    }

    uint32_t  pllm  = pll_input_clk / RCC_VCO_MAX_INPUT_FREQUENCY;

    CHECK_PARAM_VALUE(pllm,  RCC_PLLCFGR_MAX_PLLM);
    if (pllm < RCC_PLLCFGR_MIN_PLLM) {
        return  -1;
    }

    uint32_t  plln  =  (flag & RCC_PLLCFGR_PLLN) >> 6;
    if (plln < RCC_PLLCFGR_MIN_PLLN) {
        return  -1;
    }

    CHECK_PARAM_VALUE(plln,  RCC_PLLCFGR_MAX_PLLN);

    uint32_t vco_out_clk =  RCC_VCO_MAX_INPUT_FREQUENCY * plln;

    if (vco_out_clk < RCC_VCO_MIN_OUTPUT_FREQUENCY) {
        return  -1;
    }

    CHECK_PARAM_VALUE(vco_out_clk,  RCC_VCO_MAX_OUTPUT_FREQUENCY);

    uint32_t  factor  =   vco_out_clk / freq;

    CHECK_PARAM_VALUE(factor, 8);
    if ( (factor  <  2) || (factor & 0x1) ) {
        return  -1;
    }

    uint32_t  pllp    =   (factor >> 1) - 1;

    flag   =  pllp << 16;

    REG32_UPDATE(RCC_PLLCFGR_REG_ADDR,  flag,  RCC_PLLCFGR_PLLP); 

    return   0;

}












