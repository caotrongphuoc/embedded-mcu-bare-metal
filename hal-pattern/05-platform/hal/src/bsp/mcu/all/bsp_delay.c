#include "bsp_delay.h"

#define BSP_DELAY_US_PER_SECOND (1000000)
#define BSP_DELAY_LOOP_CYCLES   (4)

extern uint32_t SystemCoreClock;

static void bsp_prv_software_delay_loop(uint32_t loop_count) __attribute__((naked, noinline));

void bsp_software_delay(uint32_t delay, bsp_delay_units_t units)
{
	uint32_t cycles_per_us = (SystemCoreClock + BSP_DELAY_US_PER_SECOND - 1) / BSP_DELAY_US_PER_SECOND;
	uint64_t total_us      = (uint64_t)delay * (uint32_t)units;
	uint64_t loop_count    = (total_us * cycles_per_us) / BSP_DELAY_LOOP_CYCLES;

	if (loop_count > UINT32_MAX)
	{
		loop_count = UINT32_MAX;
	}

	if (0 != loop_count)
	{
		bsp_prv_software_delay_loop((uint32_t)loop_count);
	}
}

static void bsp_prv_software_delay_loop(__attribute__((unused)) uint32_t loop_count)
{
	__asm volatile(
	    "1:                         \n"
	    "    sub r0, r0, #1         \n"
	    "    cmp r0, #0             \n"
	    "    bne.n 1b               \n"
	    "    bx lr                  \n");
}
