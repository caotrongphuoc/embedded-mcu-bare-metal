#ifndef __BSP_CLOCKS_H__
#define __BSP_CLOCKS_H__

#include "hal_common_api.h"

#define BSP_CLOCKS_SOURCE_CLOCK_MSI    (0)
#define BSP_CLOCKS_SOURCE_CLOCK_HSI    (1)
#define BSP_CLOCKS_SOURCE_CLOCK_HSE    (2)
#define BSP_CLOCKS_SOURCE_CLOCK_PLL    (3)

#include "bsp_clock_cfg.h"

HAL_HEADER

void bsp_clock_init(void);

HAL_FOOTER

#endif // __BSP_CLOCKS_H__
