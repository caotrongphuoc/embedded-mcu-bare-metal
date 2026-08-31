#include "stm32l1_gpio.h"

#define STM32L1_GPIO_PRV_PORT_OFFSET    (8U)
#define STM32L1_GPIO_PRV_PORT_BITS      (0xFF00U)
#define STM32L1_GPIO_PRV_PIN_BITS       (0x00FFU)

const hal_gpio_api_t g_gpio_on_stm32l1_gpio =
{
    .open             = STM32L1_GPIO_Open,
    .close            = STM32L1_GPIO_Close,
    .pinsCfg          = STM32L1_GPIO_PinsCfg,
    .pinCfg           = STM32L1_GPIO_PinCfg,
    .pinRead          = STM32L1_GPIO_PinRead,
    .pinWrite         = STM32L1_GPIO_PinWrite,
    .portDirectionSet = STM32L1_GPIO_PortDirectionSet,
    .portRead         = STM32L1_GPIO_PortRead,
    .portWrite        = STM32L1_GPIO_PortWrite
};
