#include "bm_led_blink.h"

int main(void);

extern void _estack(void);

__attribute__((naked, noreturn)) void Reset_Handler(void)
{
	extern long _sbss, _ebss;
	extern long _sdata, _edata;
	extern long _sidata;

	SCB->VTOR = APP_START_ADDR;

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
		(void)0;
	}
}

__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[16 + 45])(void) = {
    _estack,
    Reset_Handler,
};

static void delay(volatile uint32_t count)
{
	while (count--)
	{
		__asm__("nop");
	}
}

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	LED_PORT->MODER |= (1U << (LED_PIN * 2));

	for (;;)
	{
		LED_PORT->BSRR = (1U << LED_PIN);
		delay(500000);
		LED_PORT->BSRR = (1U << (LED_PIN + 16));
		delay(500000);
	}
	return 0;
}