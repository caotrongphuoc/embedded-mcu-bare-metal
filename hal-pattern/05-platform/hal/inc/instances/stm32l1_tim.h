#ifndef __STM32L1_TIM_H__
#define __STM32L1_TIM_H__

#include "hal_timer_api.h"
#if __has_include("stm32l1_tim_cfg.h")
#include "stm32l1_tim_cfg.h"
#endif

#include "stm32l1xx.h"

HAL_HEADER

/** STM32L1 TIM private control block. */
typedef struct st_stm32l1_tim_instance_ctrl
{
	uint32_t          open;
	TIM_TypeDef     * p_reg;
	uint8_t           channel;
	hal_timer_mode_t  mode;
	void           (* p_callback)(hal_timer_callback_args_t * p_args);
	void            * p_context;
} stm32l1_tim_instance_ctrl_t;

/** STM32L1 TIM extended configuration. Assign to hal_timer_cfg_t::p_extend. Empty placeholder for now. */
typedef struct st_stm32l1_tim_extended_cfg
{
	uint32_t reserved;
} stm32l1_tim_extended_cfg_t;

/** STM32L1 TIM channel selector for hal_timer_cfg_t::channel. */
typedef enum e_stm32l1_tim_channel
{
	STM32L1_TIM_CHANNEL_TIM2 = 0,
	STM32L1_TIM_CHANNEL_TIM3 = 1,
	STM32L1_TIM_CHANNEL_TIM4 = 2
} stm32l1_tim_channel_t;

/** Timer implementation for STM32L1. */
extern const hal_timer_api_t g_timer_on_stm32l1_tim;

hal_err_t STM32L1_TIM_Open(hal_timer_ctrl_t * const p_ctrl, hal_timer_cfg_t const * const p_cfg);
hal_err_t STM32L1_TIM_Close(hal_timer_ctrl_t * const p_ctrl);
hal_err_t STM32L1_TIM_Start(hal_timer_ctrl_t * const p_ctrl);
hal_err_t STM32L1_TIM_Stop(hal_timer_ctrl_t * const p_ctrl);
hal_err_t STM32L1_TIM_PeriodSet(hal_timer_ctrl_t * const p_ctrl, uint32_t const period_us);
hal_err_t STM32L1_TIM_CallbackSet(hal_timer_ctrl_t * const p_ctrl,
                                  void                 (* p_callback)(hal_timer_callback_args_t *),
                                  void * const            p_context);

HAL_FOOTER

#endif // __STM32L1_TIM_H__
