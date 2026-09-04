#ifndef __PIN_DATA_H__
#define __PIN_DATA_H__

#include "hal_gpio_api.h"

HAL_HEADER

#define AK_BASE_KIT_USART1_TX_PIN    ((bsp_io_port_pin_t) 0x0009)   /* PA9  */
#define AK_BASE_KIT_USART1_RX_PIN    ((bsp_io_port_pin_t) 0x000A)   /* PA10 */

extern const hal_gpio_cfg_t g_bsp_pin_cfg;

HAL_FOOTER

#endif // __PIN_DATA_H__
