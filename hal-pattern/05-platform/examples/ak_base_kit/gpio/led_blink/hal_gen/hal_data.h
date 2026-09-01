#ifndef __HAL_DATA_H__
#define __HAL_DATA_H__

#include "pin_data.h"
#include "stm32l1_gpio.h"

HAL_HEADER

extern stm32l1_gpio_instance_ctrl_t g_gpio_ctrl;
extern const hal_gpio_instance_t g_gpio;

void hal_entry(void);

HAL_FOOTER

#endif // __HAL_DATA_H__
