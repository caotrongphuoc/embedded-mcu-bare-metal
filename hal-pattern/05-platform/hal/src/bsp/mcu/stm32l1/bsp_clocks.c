#include "bsp_clocks.h"
#include "stm32l1xx.h"

/** Initializes the system clocks. */
void bsp_clock_init(void)
{
    SystemInit();
    SystemCoreClockUpdate();
}
