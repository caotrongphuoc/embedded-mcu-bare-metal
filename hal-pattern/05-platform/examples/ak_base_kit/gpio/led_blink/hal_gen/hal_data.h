#ifndef __HAL_DATA_H__
#define __HAL_DATA_H__

#include "pin_data.h"
#include "stm32l1_gpio.h"

HAL_HEADER

extern const hal_gpio_instance_t g_gpio;

void hal_entry(void);

HAL_FOOTER

#endif // __HAL_DATA_H__
