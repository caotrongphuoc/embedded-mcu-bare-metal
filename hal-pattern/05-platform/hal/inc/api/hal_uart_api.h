#ifndef __HAL_UART_API_H__
#define __HAL_UART_API_H__

#include <stdint.h>

#include "hal_common_api.h"

HAL_HEADER

/** UART data bit length. */
typedef enum e_hal_uart_data_bits
{
	HAL_UART_DATA_BITS_9 = 9,
	HAL_UART_DATA_BITS_8 = 8,
	HAL_UART_DATA_BITS_7 = 7
} hal_uart_data_bits_t;

/** UART parity mode. */
typedef enum e_hal_uart_parity
{
	HAL_UART_PARITY_OFF = 0,
	HAL_UART_PARITY_EVEN,
	HAL_UART_PARITY_ODD
} hal_uart_parity_t;

/** UART stop bit length. */
typedef enum e_hal_uart_stop_bits
{
	HAL_UART_STOP_BITS_1 = 0,
	HAL_UART_STOP_BITS_2
} hal_uart_stop_bits_t;

/** UART event delivered to the user callback. */
typedef enum e_hal_uart_event
{
	HAL_UART_EVENT_RX_COMPLETE = 0,
	HAL_UART_EVENT_TX_COMPLETE,
	HAL_UART_EVENT_RX_CHAR,
	HAL_UART_EVENT_ERR_PARITY,
	HAL_UART_EVENT_ERR_FRAMING,
	HAL_UART_EVENT_ERR_OVERFLOW
} hal_uart_event_t;

/** Arguments passed to the UART callback. */
typedef struct st_hal_uart_callback_args
{
	uint8_t          channel;
	hal_uart_event_t event;
	uint32_t         data;         /* received byte for HAL_UART_EVENT_RX_CHAR */
	void           * p_context;    /* user context set via hal_uart_cfg_t or callbackSet */
} hal_uart_callback_args_t;

/** UART configuration data. */
typedef struct st_hal_uart_cfg
{
	uint8_t              channel;
	hal_uart_data_bits_t data_bits;
	hal_uart_parity_t    parity;
	hal_uart_stop_bits_t stop_bits;
	void              (* p_callback)(hal_uart_callback_args_t * p_args);
	void               * p_context;
	void const         * p_extend;
} hal_uart_cfg_t;

/** UART control block. */
typedef void hal_uart_ctrl_t;

/** UART functions implemented at the HAL layer. */
typedef struct st_hal_uart_api
{
	/** Open the UART driver. */
	hal_err_t (* open)(hal_uart_ctrl_t * const p_ctrl, hal_uart_cfg_t const * const p_cfg);

	/** Read bytes from the UART driver. */
	hal_err_t (* read)(hal_uart_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);

	/** Write bytes to the UART driver. */
	hal_err_t (* write)(hal_uart_ctrl_t * const p_ctrl, uint8_t const * const p_src, uint32_t const bytes);

	/** Close the UART driver. */
	hal_err_t (* close)(hal_uart_ctrl_t * const p_ctrl);

	/** Register a callback and context. Replaces the values from open(). */
	hal_err_t (* callbackSet)(hal_uart_ctrl_t * const p_ctrl,
	                          void                 (* p_callback)(hal_uart_callback_args_t *),
	                          void * const            p_context);
} hal_uart_api_t;

/** UART instance. */
typedef struct st_hal_uart_instance
{
	hal_uart_ctrl_t      * p_ctrl;
	hal_uart_cfg_t const * p_cfg;
	hal_uart_api_t const * p_api;
} hal_uart_instance_t;

HAL_FOOTER

#endif // __HAL_UART_API_H__
