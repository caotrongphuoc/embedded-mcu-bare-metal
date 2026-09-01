#ifndef __STM32L1_GPIO_H__
#define __STM32L1_GPIO_H__

#include "hal_gpio_api.h"
#if __has_include("stm32l1_gpio_cfg.h")
#include "stm32l1_gpio_cfg.h"
#endif

HAL_HEADER

/** STM32L1 GPIO private control block. */
typedef struct st_stm32l1_gpio_instance_ctrl
{
    uint32_t open;
    void   * p_context;
} stm32l1_gpio_instance_ctrl_t;

/** STM32L1 GPIO pin configuration options. */
typedef enum e_stm32l1_gpio_cfg_options
{
    STM32L1_GPIO_CFG_MODE_INPUT        = 0x00000000,
    STM32L1_GPIO_CFG_MODE_OUTPUT       = 0x00000001,
    STM32L1_GPIO_CFG_MODE_ALTERNATE    = 0x00000002,
    STM32L1_GPIO_CFG_MODE_ANALOG       = 0x00000003,

    STM32L1_GPIO_CFG_OUTPUT_PUSH_PULL  = 0x00000000,
    STM32L1_GPIO_CFG_OUTPUT_OPEN_DRAIN = 0x00000004,

    STM32L1_GPIO_CFG_SPEED_400_KHZ     = 0x00000000,
    STM32L1_GPIO_CFG_SPEED_2_MHZ       = 0x00000008,
    STM32L1_GPIO_CFG_SPEED_10_MHZ      = 0x00000010,
    STM32L1_GPIO_CFG_SPEED_40_MHZ      = 0x00000018,

    STM32L1_GPIO_CFG_PULL_NONE         = 0x00000000,
    STM32L1_GPIO_CFG_PULL_UP           = 0x00000020,
    STM32L1_GPIO_CFG_PULL_DOWN         = 0x00000040,

    STM32L1_GPIO_CFG_OUTPUT_LOW        = 0x00000000,
    STM32L1_GPIO_CFG_OUTPUT_HIGH       = 0x00000080,

    STM32L1_GPIO_CFG_AF_0              = 0x00000000,
    STM32L1_GPIO_CFG_AF_1              = 0x00000100,
    STM32L1_GPIO_CFG_AF_2              = 0x00000200,
    STM32L1_GPIO_CFG_AF_3              = 0x00000300,
    STM32L1_GPIO_CFG_AF_4              = 0x00000400,
    STM32L1_GPIO_CFG_AF_5              = 0x00000500,
    STM32L1_GPIO_CFG_AF_6              = 0x00000600,
    STM32L1_GPIO_CFG_AF_7              = 0x00000700,
    STM32L1_GPIO_CFG_AF_8              = 0x00000800,
    STM32L1_GPIO_CFG_AF_9              = 0x00000900,
    STM32L1_GPIO_CFG_AF_10             = 0x00000A00,
    STM32L1_GPIO_CFG_AF_11             = 0x00000B00,
    STM32L1_GPIO_CFG_AF_12             = 0x00000C00,
    STM32L1_GPIO_CFG_AF_13             = 0x00000D00,
    STM32L1_GPIO_CFG_AF_14             = 0x00000E00,
    STM32L1_GPIO_CFG_AF_15             = 0x00000F00
} stm32l1_gpio_cfg_options_t;

/** GPIO implementation for STM32L1. */
extern const hal_gpio_api_t g_gpio_on_stm32l1_gpio;

hal_err_t STM32L1_GPIO_Open(hal_gpio_ctrl_t * const p_ctrl, hal_gpio_cfg_t const * p_cfg);
hal_err_t STM32L1_GPIO_Close(hal_gpio_ctrl_t * const p_ctrl);
hal_err_t STM32L1_GPIO_PinsCfg(hal_gpio_ctrl_t * const p_ctrl, hal_gpio_cfg_t const * p_cfg);
hal_err_t STM32L1_GPIO_PinCfg(hal_gpio_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);
hal_err_t STM32L1_GPIO_PinRead(hal_gpio_ctrl_t * const p_ctrl,
                               bsp_io_port_pin_t       pin,
                               bsp_io_level_t        * p_pin_value);
hal_err_t STM32L1_GPIO_PinWrite(hal_gpio_ctrl_t * const p_ctrl,
                                bsp_io_port_pin_t       pin,
                                bsp_io_level_t          level);
hal_err_t STM32L1_GPIO_PortDirectionSet(hal_gpio_ctrl_t * const p_ctrl,
                                        bsp_io_port_t           port,
                                        hal_gpio_size_t         direction_values,
                                        hal_gpio_size_t         mask);
hal_err_t STM32L1_GPIO_PortRead(hal_gpio_ctrl_t * const p_ctrl,
                                bsp_io_port_t           port,
                                hal_gpio_size_t       * p_port_value);
hal_err_t STM32L1_GPIO_PortWrite(hal_gpio_ctrl_t * const p_ctrl,
                                 bsp_io_port_t           port,
                                 hal_gpio_size_t         value,
                                 hal_gpio_size_t         mask);

HAL_FOOTER

#endif // __STM32L1_GPIO_H__
