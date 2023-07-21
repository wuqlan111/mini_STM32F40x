#ifndef  SYSTEM_RCC_H
#define  SYSTEM_RCC_H

#include  <stdint.h>

#include  "util.h"

#define  RCC_MODULE(module)  RCC_MODULE_##module

typedef  enum {
    RCC_AHB1_CLK = 0,
    RCC_AHB2_CLK,
    RCC_AHB3_CLK,
    RCC_APB1_CLK,
    RCC_APB2_CLK,
    RCC_MAX_CLK  =   RCC_APB2_CLK
} rcc_clk_type_e;




typedef  enum {

    /*AHB1*/
    RCC_MODULE(GPIOA)  = 0,
    RCC_MODULE(GPIOB),
    RCC_MODULE(GPIOC),
    RCC_MODULE(GPIOD),
    RCC_MODULE(GPIOE),
    RCC_MODULE(GPIOF),
    RCC_MODULE(GPIOG),
    RCC_MODULE(GPIOH),
    RCC_MODULE(GPIOI),
    RCC_MODULE(CRC),
    RCC_MODULE(DMA1),
    RCC_MODULE(DMA2),
    RCC_MODULE(ETHMAC),
    RCC_MODULE(OTGHS),
    RCC_MODULE(AHB1_MAX) = RCC_MODULE(OTGHS),

    /*AHB2*/
    RCC_MODULE(DCMI),
    RCC_MODULE(CRYP),
    RCC_MODULE(HASH),
    RCC_MODULE(RNG),
    RCC_MODULE(OTGFS),
    RCC_MODULE(AHB2_MAX) = RCC_MODULE(OTGFS),

    /*AHB3*/
    RCC_MODULE(FCMS),
    RCC_MODULE(AHB3_MAX) = RCC_MODULE(FCMS),

    /*APB1*/
    RCC_MODULE(TIM2),
    RCC_MODULE(TIM3),
    RCC_MODULE(TIM4),
    RCC_MODULE(TIM5),
    RCC_MODULE(TIM6),
    RCC_MODULE(TIM7),
    RCC_MODULE(TIM12),
    RCC_MODULE(TIM13),
    RCC_MODULE(TIM14),
    RCC_MODULE(WWDG),
    RCC_MODULE(SPI2),
    RCC_MODULE(SPI3),
    RCC_MODULE(USART2),
    RCC_MODULE(USART3),
    RCC_MODULE(USART4),
    RCC_MODULE(USART5),
    RCC_MODULE(I2C1),
    RCC_MODULE(I2C2),
    RCC_MODULE(I2C3),
    RCC_MODULE(CAN1),
    RCC_MODULE(CAN2),
    RCC_MODULE(PWR),
    RCC_MODULE(DAC),
    RCC_MODULE(APB1_MAX) = RCC_MODULE(DAC),

    /*APB2*/
    RCC_MODULE(TIM1),
    RCC_MODULE(TIM8),
    RCC_MODULE(USART1),
    RCC_MODULE(USART6),
    RCC_MODULE(ADC),
    RCC_MODULE(SDIO),
    RCC_MODULE(SPI1),
    RCC_MODULE(SYSCFG),
    RCC_MODULE(TIM9),
    RCC_MODULE(TIM10),
    RCC_MODULE(TIM11),
    RCC_MODULE(APB2_MAX) = RCC_MODULE(TIM11),
    RCC_MODULE_MAX = RCC_MODULE(TIM11),
} rcc_module_e;


typedef  enum {
    RCC_RESET_OP =  0,
    RCC_UNRESET_OP,
    RCC_CLK_ENABLE,
    RCC_CLK_DISABLE,
    RCC_CLK_ENABLE_LOWER_POWER,
    RCC_CLK_DISABLE_LOWER_POWER,
    RCC_MODULE_MAX_OP  =  RCC_CLK_DISABLE_LOWER_POWER,
} rcc_module_op_e;



typedef enum {
    RCC_SYSTEM_CLK_HSI  =  0,
    RCC_SYSTEM_CLK_HSE,
    RCC_SYSTEM_CLK_PLL,
    RCC_SYSTEM_CLK_MAX   =  RCC_SYSTEM_CLK_PLL,
} rcc_system_clk_select_e;


typedef enum {
    RCC_HSI_CLK   =   0,
    RCC_HSE_CLK,
    RCC_PLL_CLK,
    RCC_PLLI2S_CLK,
    RCC_LSE_CLK,
    RCC_LSI_CLK,
    RCC_MAX_CLK =  RCC_LSI_CLK,
} rcc_system_clk_e;





int32_t  rcc_module_set_op(rcc_module_e  module,  rcc_module_op_e  op);


int32_t  rcc_set_clk_state(rcc_system_clk_e clk_type,  uint32_t  enable);

int32_t  rcc_set_clk_bypass_oscillator(rcc_system_clk_e clk_type, uint32_t  bypass);



int32_t  rcc_switch_system_clk_source(rcc_system_clk_select_e  clk_type);









#endif


