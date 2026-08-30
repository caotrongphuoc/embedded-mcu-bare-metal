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

/** GPIO pin identifier and configuration value. */
typedef struct st_hal_gpio_pin_cfg
{
    uint32_t       pin_cfg;            ///< Pin options, for example output mode with pull-up
    hal_gpio_pin_t pin;                ///< Pin identifier, for example port B pin 8 is 0x0108
} hal_gpio_pin_cfg_t;

/** GPIO configuration data. */
typedef struct st_hal_gpio_cfg
{
    uint16_t                   number_of_pins; ///< Number of configured pins, for example 1 for one LED
    hal_gpio_pin_cfg_t const * p_pin_cfg_data; ///< Pin configuration array
    void const               * p_extend;       ///< MCU-specific configuration, or NULL when unused
} hal_gpio_cfg_t;

/** GPIO control block. */
typedef void hal_gpio_ctrl_t;

HAL_FOOTER

#endif // __HAL_GPIO_API_H__
