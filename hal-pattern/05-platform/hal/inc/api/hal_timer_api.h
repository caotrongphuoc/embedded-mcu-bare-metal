#ifndef __HAL_TIMER_API_H__
#define __HAL_TIMER_API_H__

#include <stdint.h>

#include "hal_common_api.h"

HAL_HEADER

/** Timer counting mode. */
typedef enum e_hal_timer_mode
{
	HAL_TIMER_MODE_PERIODIC = 0,
	HAL_TIMER_MODE_ONE_SHOT
} hal_timer_mode_t;

/** Timer event delivered to the user callback. */
typedef enum e_hal_timer_event
{
	HAL_TIMER_EVENT_CYCLE_END = 0
} hal_timer_event_t;

/** Arguments passed to the timer callback. */
typedef struct st_hal_timer_callback_args
{
	uint8_t           channel;
	hal_timer_event_t event;
	void            * p_context;
} hal_timer_callback_args_t;

/** Timer configuration data. */
typedef struct st_hal_timer_cfg
{
	uint8_t           channel;
	hal_timer_mode_t  mode;
	uint32_t          period_us;
	void           (* p_callback)(hal_timer_callback_args_t * p_args);
	void            * p_context;
	void const      * p_extend;
} hal_timer_cfg_t;

/** Timer control block. */
typedef void hal_timer_ctrl_t;

/** Timer functions implemented at the HAL layer. */
typedef struct st_hal_timer_api
{
	/** Open the timer driver and apply the initial configuration. */
	hal_err_t (* open)(hal_timer_ctrl_t * const p_ctrl, hal_timer_cfg_t const * const p_cfg);

	/** Close the timer driver. */
	hal_err_t (* close)(hal_timer_ctrl_t * const p_ctrl);

	/** Start the timer counting. */
	hal_err_t (* start)(hal_timer_ctrl_t * const p_ctrl);

	/** Stop the timer without closing the driver. */
	hal_err_t (* stop)(hal_timer_ctrl_t * const p_ctrl);

	/** Change the period in microseconds. */
	hal_err_t (* periodSet)(hal_timer_ctrl_t * const p_ctrl, uint32_t const period_us);

	/** Register a callback and context. Replaces the values from open(). */
	hal_err_t (* callbackSet)(hal_timer_ctrl_t * const p_ctrl,
	                          void                 (* p_callback)(hal_timer_callback_args_t *),
	                          void * const            p_context);
} hal_timer_api_t;

/** Timer instance. */
typedef struct st_hal_timer_instance
{
	hal_timer_ctrl_t      * p_ctrl;
	hal_timer_cfg_t const * p_cfg;
	hal_timer_api_t const * p_api;
} hal_timer_instance_t;

HAL_FOOTER

#endif // __HAL_TIMER_API_H__
