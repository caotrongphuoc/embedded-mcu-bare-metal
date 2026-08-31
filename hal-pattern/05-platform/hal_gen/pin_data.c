#include "pin_data.h"
#include "stm32l1_gpio.h"

const hal_gpio_pin_cfg_t g_bsp_pin_cfg_data[] =
{
    {
        .pin_cfg = STM32L1_GPIO_CFG_MODE_OUTPUT |
                   STM32L1_GPIO_CFG_OUTPUT_PUSH_PULL |
                   STM32L1_GPIO_CFG_SPEED_2_MHZ |
                   STM32L1_GPIO_CFG_PULL_NONE |
                   STM32L1_GPIO_CFG_OUTPUT_LOW,
        .pin = AK_BASE_KIT_LED_PIN
    }
};

const hal_gpio_cfg_t g_bsp_pin_cfg =
{
    .number_of_pins = 1U,
    .p_pin_cfg_data = g_bsp_pin_cfg_data,
    .p_extend       = NULL
};
