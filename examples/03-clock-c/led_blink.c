#include "led_blink.h"

int main(void);
extern void _estack(void);

volatile uint32_t g_tick;

__attribute__((naked, noreturn)) void Reset_Handler(void)
{
	extern long _sbss, _ebss, _sdata, _edata, _sidata;

	for (long* dst = &_sbss; dst < &_ebss; dst++)
	{
		*dst = 0;
	}

	for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
	{
		*dst++ = *src++;
	}

	main();
	for (;;)
	{
	}
}

void SysTick_Handler(void)
{
	g_tick++;
}

__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[16])(void) = {
    _estack,
    Reset_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SysTick_Handler,
};

static void delay_ms(uint32_t ms)
{
	uint32_t start = g_tick;
	while ((g_tick - start) < ms)
	{
	}
}

// HSI 16 MHz × 4 / 2 = 32 MHz (max SYSCLK for STM32L1). RM0038 §6.3.
static void clock_init(void)
{
	RCC->APB1ENR |= (1U << 28);                              // PWR clock on

	PWR->CR = (PWR->CR & ~(0x3U << 11)) | (0x1U << 11);      // VOS = range 1
	while (PWR->CSR & (1U << 4))
	{
	}

	FLASH->ACR |= (1U << 2);                                 // ACC64
	while (!(FLASH->ACR & (1U << 2)))
	{
	}
	FLASH->ACR |= (1U << 1) | (1U << 0);                     // PRFTEN + LATENCY=1

	RCC->CR |= (1U << 0);                                    // HSI on
	while (!(RCC->CR & (1U << 1)))
	{
	}

	uint32_t cfgr = RCC->CFGR;
	cfgr &= ~((0xFU << 18) | (0x3U << 22) | (1U << 16));
	cfgr |= (0x1U << 18) | (0x1U << 22);                     // PLLMUL=×4, PLLDIV=/2, PLLSRC=HSI
	RCC->CFGR = cfgr;

	RCC->CR |= (1U << 24);                                   // PLL on
	while (!(RCC->CR & (1U << 25)))
	{
	}

	RCC->CFGR = (RCC->CFGR & ~0x3U) | 0x3U;                  // SW = PLL
	while ((RCC->CFGR & 0xCU) != 0xCU)
	{
	}
}

int main(void)
{
	clock_init();

	RCC->AHBENR |= (1U << 1);
	GPIOB->MODER |= (1U << (LED_PIN * 2));

	SysTick->LOAD = (SYSCLK_HZ / TICK_HZ) - 1U;
	SysTick->VAL = 0U;
	SysTick->CTRL = (1U << 0) | (1U << 1) | (1U << 2);

	for (;;)
	{
		GPIOB->BSRR = (1U << LED_PIN);
		delay_ms(100);
		GPIOB->BSRR = (1U << (LED_PIN + 16));
		delay_ms(100);
	}
	return 0;
}
