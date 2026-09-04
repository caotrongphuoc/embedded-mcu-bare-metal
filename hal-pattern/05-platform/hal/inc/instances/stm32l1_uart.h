#ifndef __STM32L1_UART_H__
#define __STM32L1_UART_H__

#include "hal_uart_api.h"
#if __has_include("stm32l1_uart_cfg.h")
#include "stm32l1_uart_cfg.h"
#endif

#include "stm32l1xx.h"

HAL_HEADER

/** STM32L1 UART private control block. */
typedef struct st_stm32l1_uart_instance_ctrl
{
	uint32_t         open;
	USART_TypeDef  * p_reg;
	uint8_t          channel;
	void          (* p_callback)(hal_uart_callback_args_t * p_args);
	void           * p_context;
} stm32l1_uart_instance_ctrl_t;

/** STM32L1 UART extended configuration. Assign to hal_uart_cfg_t::p_extend. */
typedef struct st_stm32l1_uart_extended_cfg
{
	uint32_t baud;   /* baud rate in bits per second, e.g. 115200 */
} stm32l1_uart_extended_cfg_t;

/** STM32L1 USART channel selector for hal_uart_cfg_t::channel. */
typedef enum e_stm32l1_uart_channel
{
	STM32L1_UART_CHANNEL_USART1 = 0,
	STM32L1_UART_CHANNEL_USART2 = 1,
	STM32L1_UART_CHANNEL_USART3 = 2
} stm32l1_uart_channel_t;

/** UART implementation for STM32L1. */
extern const hal_uart_api_t g_uart_on_stm32l1_uart;

hal_err_t STM32L1_UART_Open(hal_uart_ctrl_t * const p_ctrl, hal_uart_cfg_t const * const p_cfg);
hal_err_t STM32L1_UART_Close(hal_uart_ctrl_t * const p_ctrl);
hal_err_t STM32L1_UART_Read(hal_uart_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);
hal_err_t STM32L1_UART_Write(hal_uart_ctrl_t * const p_ctrl, uint8_t const * const p_src, uint32_t const bytes);
hal_err_t STM32L1_UART_CallbackSet(hal_uart_ctrl_t * const p_ctrl,
                                   void                 (* p_callback)(hal_uart_callback_args_t *),
                                   void * const            p_context);

HAL_FOOTER

#endif // __STM32L1_UART_H__
