#ifndef __HAL_GPIO_API_H__
#define __HAL_GPIO_API_H__

#include <stdint.h>

#include "bsp_io.h"
#include "hal_common_api.h"

HAL_HEADER

/** GPIO port data type. */
typedef uint16_t hal_gpio_size_t;

/** GPIO pin identifier and configuration value. */
typedef struct st_hal_gpio_pin_cfg
{
    uint32_t          pin_cfg;
    bsp_io_port_pin_t pin;
} hal_gpio_pin_cfg_t;

/** GPIO configuration data. */
typedef struct st_hal_gpio_cfg
{
    uint16_t                   number_of_pins;
    hal_gpio_pin_cfg_t const * p_pin_cfg_data;
    void const               * p_extend;
} hal_gpio_cfg_t;

/** GPIO control block. */
typedef void hal_gpio_ctrl_t;

/** GPIO functions implemented at the HAL layer. */
typedef struct st_hal_gpio_api
{
    /** Open the GPIO driver and apply the initial pin configuration. */
    hal_err_t (* open)(hal_gpio_ctrl_t * const p_ctrl, hal_gpio_cfg_t const * p_cfg);

    /** Close the GPIO driver. */
    hal_err_t (* close)(hal_gpio_ctrl_t * const p_ctrl);

    /** Configure multiple pins. */
    hal_err_t (* pinsCfg)(hal_gpio_ctrl_t * const p_ctrl, hal_gpio_cfg_t const * p_cfg);

    /** Configure one pin. */
    hal_err_t (* pinCfg)(hal_gpio_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);

    /** Read one pin. */
    hal_err_t (* pinRead)(hal_gpio_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);

    /** Write one pin. */
    hal_err_t (* pinWrite)(hal_gpio_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);

    /** Set the direction of selected pins on a port. */
    hal_err_t (* portDirectionSet)(hal_gpio_ctrl_t * const p_ctrl,
                                   bsp_io_port_t           port,
                                   hal_gpio_size_t         direction_values,
                                   hal_gpio_size_t         mask);

    /** Read a port. */
    hal_err_t (* portRead)(hal_gpio_ctrl_t * const p_ctrl,
                           bsp_io_port_t           port,
                           hal_gpio_size_t       * p_port_value);

    /** Write selected pins on a port. */
    hal_err_t (* portWrite)(hal_gpio_ctrl_t * const p_ctrl,
                            bsp_io_port_t           port,
                            hal_gpio_size_t         value,
                            hal_gpio_size_t         mask);
} hal_gpio_api_t;

/** GPIO instance. */
typedef struct st_hal_gpio_instance
{
    hal_gpio_ctrl_t      * p_ctrl;
    hal_gpio_cfg_t const * p_cfg;
    hal_gpio_api_t const * p_api;
} hal_gpio_instance_t;

HAL_FOOTER

#endif // __HAL_GPIO_API_H__
