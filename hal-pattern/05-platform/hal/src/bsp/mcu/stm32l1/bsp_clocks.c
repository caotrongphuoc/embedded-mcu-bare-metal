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

#if BSP_CFG_CLOCK_SOURCE != BSP_CLOCKS_SOURCE_CLOCK_PLL
#error "Only PLL system clock is supported"
#endif

#if BSP_CFG_PLL_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HSE
#define BSP_PRV_PLL_SOURCE RCC_CFGR_PLLSRC_HSE
#else
#error "Unsupported PLL clock source"
#endif

#if BSP_CFG_PLL_MUL == 3
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL3
#elif BSP_CFG_PLL_MUL == 4
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL4
#elif BSP_CFG_PLL_MUL == 6
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL6
#elif BSP_CFG_PLL_MUL == 8
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL8
#elif BSP_CFG_PLL_MUL == 12
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL12
#elif BSP_CFG_PLL_MUL == 16
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL16
#elif BSP_CFG_PLL_MUL == 24
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL24
#elif BSP_CFG_PLL_MUL == 32
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL32
#elif BSP_CFG_PLL_MUL == 48
#define BSP_PRV_PLL_MUL RCC_CFGR_PLLMUL48
#else
#error "Unsupported PLL multiplier"
#endif

#if BSP_CFG_PLL_DIV == 2
#define BSP_PRV_PLL_DIV RCC_CFGR_PLLDIV2
#elif BSP_CFG_PLL_DIV == 3
#define BSP_PRV_PLL_DIV RCC_CFGR_PLLDIV3
#elif BSP_CFG_PLL_DIV == 4
#define BSP_PRV_PLL_DIV RCC_CFGR_PLLDIV4
#else
#error "Unsupported PLL divider"
#endif

#define BSP_PRV_FLASH_ZERO_WAIT_STATE_MAX_HZ (16000000)
#define BSP_PRV_PLL_CFG                      (BSP_PRV_PLL_SOURCE | BSP_PRV_PLL_MUL | BSP_PRV_PLL_DIV)

static void bsp_clock_set_prechange(uint32_t requested_freq_hz);

/** Initializes the system clocks. */
void bsp_clock_init(void)
{
	SystemInit();
	bsp_clock_set_prechange(BSP_CFG_SYSCLK_HZ);

	RCC->CR &= ~RCC_CR_HSEBYP;
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY))
	{
	}

	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL | RCC_CFGR_PLLDIV)) | BSP_PRV_PLL_CFG;
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY))
	{
	}

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
