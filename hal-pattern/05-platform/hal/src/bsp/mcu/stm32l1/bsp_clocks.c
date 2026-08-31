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

#define BSP_PRV_FLASH_ZERO_WAIT_STATE_MAX_HZ (16000000)

static void bsp_clock_set_prechange(uint32_t requested_freq_hz);

/** Initializes the system clocks. */
void bsp_clock_init(void)
{
	SystemInit();
	bsp_clock_set_prechange(BSP_CFG_SYSCLK_HZ);
	SystemCoreClockUpdate();
}

/** Prepares power and flash settings before the system clock is changed. */
static void bsp_clock_set_prechange(uint32_t requested_freq_hz)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	(void)RCC->APB1ENR;

	PWR->CR = (PWR->CR & ~PWR_CR_VOS) | PWR_CR_VOS_0;
	while (PWR->CSR & PWR_CSR_VOSF)
	{
	}

	FLASH->ACR |= FLASH_ACR_ACC64 | FLASH_ACR_PRFTEN;

	if (requested_freq_hz > BSP_PRV_FLASH_ZERO_WAIT_STATE_MAX_HZ)
	{
		FLASH->ACR |= FLASH_ACR_LATENCY;
	}
	else
	{
		FLASH->ACR &= ~FLASH_ACR_LATENCY;
	}
}
