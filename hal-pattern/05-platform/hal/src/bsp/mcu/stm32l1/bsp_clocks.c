#include "bsp_clocks.h"
#include "stm32l1xx.h"

#if BSP_CFG_XTAL_HZ == 0
 #error "BSP_CFG_XTAL_HZ must be greater than zero"
#endif

#if BSP_CFG_PLL_MUL == 0
 #error "BSP_CFG_PLL_MUL must be greater than zero"
#endif

#if BSP_CFG_PLL_DIV == 0
 #error "BSP_CFG_PLL_DIV must be greater than zero"
#endif

#if BSP_CFG_SYSCLK_HZ != ((BSP_CFG_XTAL_HZ * BSP_CFG_PLL_MUL) / BSP_CFG_PLL_DIV)
 #error "BSP_CFG_SYSCLK_HZ does not match PLL configuration"
#endif

#if BSP_CFG_SYSCLK_HZ > 32000000
 #error "STM32L151 system clock exceeds 32 MHz"
#endif

/** Initializes the system clocks. */
void bsp_clock_init(void)
{
    SystemInit();
    SystemCoreClockUpdate();
}
