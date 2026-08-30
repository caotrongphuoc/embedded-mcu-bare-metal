#ifndef __HAL_GPIO_API_H__
#define __HAL_GPIO_API_H__

#include <stdint.h>

#include "hal_common_api.h"

HAL_HEADER

/** GPIO port data type. */
typedef uint16_t hal_gpio_size_t;

/** GPIO port identifier. */
typedef uint16_t hal_gpio_port_t;

/** GPIO pin identifier. */
typedef uint16_t hal_gpio_pin_t;

/** GPIO pin level. */
typedef enum e_hal_gpio_level
{
    HAL_GPIO_LEVEL_LOW = 0,
    HAL_GPIO_LEVEL_HIGH
} hal_gpio_level_t;

/** GPIO pin direction. */
typedef enum e_hal_gpio_direction
{
    HAL_GPIO_DIRECTION_INPUT = 0,
    HAL_GPIO_DIRECTION_OUTPUT
} hal_gpio_direction_t;

HAL_FOOTER

#endif // __HAL_GPIO_API_H__
