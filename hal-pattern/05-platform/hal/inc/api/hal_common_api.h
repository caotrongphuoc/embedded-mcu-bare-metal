#ifndef __HAL_COMMON_API_H__
#define __HAL_COMMON_API_H__

#ifdef __cplusplus
#define HAL_HEADER    extern "C" {
#define HAL_FOOTER    }
#else
#define HAL_HEADER
#define HAL_FOOTER
#endif

#define HAL_PARAMETER_NOT_USED(p)    ((void) (p))

HAL_HEADER

/** Return values shared by HAL modules. */
typedef enum e_hal_err
{
    HAL_SUCCESS = 0,
    HAL_ERR_ASSERTION,
    HAL_ERR_INVALID_POINTER,
    HAL_ERR_INVALID_ARGUMENT,
    HAL_ERR_INVALID_SIZE,
    HAL_ERR_INVALID_CHANNEL,
    HAL_ERR_INVALID_MODE,
    HAL_ERR_UNSUPPORTED,
    HAL_ERR_NOT_OPEN,
    HAL_ERR_NOT_ENABLED,
    HAL_ERR_IN_USE,
    HAL_ERR_HW_LOCKED,
    HAL_ERR_ALREADY_OPEN,
    HAL_ERR_TIMEOUT,
    HAL_ERR_INVALID_STATE
} hal_err_t;

HAL_FOOTER

#endif // __HAL_COMMON_API_H__
