#ifndef __BSP_DELAY_H__
#define __BSP_DELAY_H__

#include <stdint.h>

#include "hal_common_api.h"

HAL_HEADER

typedef enum e_bsp_delay_units
{
    BSP_DELAY_UNITS_SECONDS      = 1000000,
    BSP_DELAY_UNITS_MILLISECONDS = 1000,
    BSP_DELAY_UNITS_MICROSECONDS = 1
} bsp_delay_units_t;

void BSP_SoftwareDelay(uint32_t delay, bsp_delay_units_t units);

HAL_FOOTER

#endif // __BSP_DELAY_H__
