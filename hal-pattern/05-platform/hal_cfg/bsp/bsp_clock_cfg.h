#ifndef __BSP_CLOCK_CFG_H__
#define __BSP_CLOCK_CFG_H__

#define BSP_CFG_XTAL_HZ         (8000000)
#define BSP_CFG_PLL_SOURCE      (BSP_CLOCKS_SOURCE_CLOCK_HSE)
#define BSP_CFG_PLL_MUL         (12)
#define BSP_CFG_PLL_DIV         (3)
#define BSP_CFG_CLOCK_SOURCE    (BSP_CLOCKS_SOURCE_CLOCK_PLL)
#define BSP_CFG_SYSCLK_HZ       (32000000)
#define BSP_CFG_HCLK_DIV        (1)
#define BSP_CFG_PCLK1_DIV       (1)
#define BSP_CFG_PCLK2_DIV       (1)

#endif // __BSP_CLOCK_CFG_H__
