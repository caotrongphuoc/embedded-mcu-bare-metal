#ifndef __STM32L1_GPIO_CFG_H__
#define __STM32L1_GPIO_CFG_H__

#if __has_include("bsp_cfg.h")
#include "bsp_cfg.h"
#endif

#ifndef STM32L1_GPIO_CFG_PARAM_CHECKING_ENABLE
#define STM32L1_GPIO_CFG_PARAM_CHECKING_ENABLE    (BSP_CFG_PARAM_CHECKING_ENABLE)
#endif

#endif // __STM32L1_GPIO_CFG_H__
