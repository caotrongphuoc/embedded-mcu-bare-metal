#include "bm_led_blink.h"

int main(void);

extern void _estack(void);

__attribute__((naked, noreturn)) void Reset_Handler(void)
{
	extern long _sbss, _ebss;
	extern long _sdata, _edata;
	extern long _sidata;

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

void gpio_pin_output(GPIO_TypeDef* port, uint32_t pin)
{
	const uint32_t shift = pin * 2U;
	const uint32_t mask = (3U << shift);

	port->MODER = (port->MODER & ~mask) | (1U << shift);
	port->OTYPER &= ~(1U << pin);
	port->OSPEEDR &= ~mask;
	port->PUPDR &= ~mask;
	port->BSRR = (1U << (pin + 16));
}

void gpio_write(GPIO_TypeDef* port, uint32_t pin, uint32_t state)
{
	if (state)
	{
		port->BSRR = (1U << pin);
	}
	else
	{
		port->BSRR = (1U << (pin + 16));
	}
}

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
	gpio_pin_output(LED_PORT, LED_PIN);

	for (;;)
	{
		gpio_write(LED_PORT, LED_PIN, 1);
		delay(500000);
		gpio_write(LED_PORT, LED_PIN, 0);
		delay(500000);
	}
	return 0;
}