#ifndef  SYSTEM_RCC_H
#define  SYSTEM_RCC_H

#include  <stdint.h>

#include  "util.h"

#define  RCC_RST_MODULE(module)  RCC_RST_##module

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
    RCC_RST_MODULE(GPIOA)  = 0,
    RCC_RST_MODULE(GPIOB),
    RCC_RST_MODULE(GPIOC),
    RCC_RST_MODULE(GPIOD),
    RCC_RST_MODULE(GPIOE),
    RCC_RST_MODULE(GPIOF),
    RCC_RST_MODULE(GPIOG),
    RCC_RST_MODULE(GPIOH),
    RCC_RST_MODULE(GPIOI),
    RCC_RST_MODULE(CRC),
    RCC_RST_MODULE(DMA1),
    RCC_RST_MODULE(DMA2),
    RCC_RST_MODULE(ETHMAC),
    RCC_RST_MODULE(OTGHS),
    RCC_RST_MODULE(AHB1_MAX) = RCC_RST_MODULE(OTGHS),

    /*AHB2*/
    RCC_RST_MODULE(DCMI),
    RCC_RST_MODULE(CRYP),
    RCC_RST_MODULE(HASH),
    RCC_RST_MODULE(RNG),
    RCC_RST_MODULE(OTGFS),
    RCC_RST_MODULE(AHB2_MAX) = RCC_RST_MODULE(OTGFS),

    /*AHB3*/
    RCC_RST_MODULE(FCMS),
    RCC_RST_MODULE(AHB3_MAX) = RCC_RST_MODULE(FCMS),

    /*APB1*/
    RCC_RST_MODULE(TIM2),
    RCC_RST_MODULE(TIM3),
    RCC_RST_MODULE(TIM4),
    RCC_RST_MODULE(TIM5),
    RCC_RST_MODULE(TIM6),
    RCC_RST_MODULE(TIM7),
    RCC_RST_MODULE(TIM12),
    RCC_RST_MODULE(TIM13),
    RCC_RST_MODULE(TIM14),
    RCC_RST_MODULE(WWDG),
    RCC_RST_MODULE(SPI2),
    RCC_RST_MODULE(SPI3),
    RCC_RST_MODULE(USART2),
    RCC_RST_MODULE(USART3),
    RCC_RST_MODULE(USART4),
    RCC_RST_MODULE(USART5),
    RCC_RST_MODULE(I2C1),
    RCC_RST_MODULE(I2C2),
    RCC_RST_MODULE(I2C3),
    RCC_RST_MODULE(CAN1),
    RCC_RST_MODULE(CAN2),
    RCC_RST_MODULE(PWR),
    RCC_RST_MODULE(DAC),
    RCC_RST_MODULE(APB1_MAX) = RCC_RST_MODULE(DAC),

    /*APB2*/
    RCC_RST_MODULE(TM1),
    RCC_RST_MODULE(TM8),
    RCC_RST_MODULE(USART1),
    RCC_RST_MODULE(USART6),
    RCC_RST_MODULE(ADC),
    RCC_RST_MODULE(SDIO),
    RCC_RST_MODULE(SPI1),
    RCC_RST_MODULE(SYSCFG),
    RCC_RST_MODULE(TIM9),
    RCC_RST_MODULE(TIM10),
    RCC_RST_MODULE(TIM11),
    RCC_RST_MODULE(APB2_MAX) = RCC_RST_MODULE(TIM11),
    RCC_RST_MAX = RCC_RST_MODULE(TIM11),
} rcc_clk_rst_module_e;










#endif


