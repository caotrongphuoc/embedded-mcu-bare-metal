#include "hal_data.h"

stm32l1_gpio_instance_ctrl_t g_gpio_ctrl;

const hal_gpio_instance_t g_gpio =
{
    .p_ctrl = &g_gpio_ctrl,
    .p_cfg  = &g_bsp_pin_cfg,
    .p_api  = &g_gpio_on_stm32l1_gpio
};
