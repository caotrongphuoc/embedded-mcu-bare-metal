#ifndef __STM32L1_GPIO_H__
#define __STM32L1_GPIO_H__

#include "hal_gpio_api.h"

HAL_HEADER

/** STM32L1 GPIO private control block. */
typedef struct st_stm32l1_gpio_instance_ctrl
{
    uint32_t open;
    void   * p_context;
} stm32l1_gpio_instance_ctrl_t;

HAL_FOOTER

#endif // __STM32L1_GPIO_H__
