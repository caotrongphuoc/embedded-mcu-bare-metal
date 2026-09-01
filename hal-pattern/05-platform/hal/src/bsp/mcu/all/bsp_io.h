#ifndef __BSP_IO_H__
#define __BSP_IO_H__

#include <stdint.h>

#include "hal_common_api.h"

HAL_HEADER

/** IO port identifier. */
typedef uint16_t bsp_io_port_t;

/** IO pin identifier. Encoded as (port << 8) | pin_number. */
typedef uint16_t bsp_io_port_pin_t;

/** Digital IO pin level. */
typedef enum e_bsp_io_level
{
    BSP_IO_LEVEL_LOW = 0,
    BSP_IO_LEVEL_HIGH
} bsp_io_level_t;

/** Digital IO pin direction. */
typedef enum e_bsp_io_direction
{
    BSP_IO_DIRECTION_INPUT = 0,
    BSP_IO_DIRECTION_OUTPUT
} bsp_io_direction_t;

HAL_FOOTER

#endif // __BSP_IO_H__
