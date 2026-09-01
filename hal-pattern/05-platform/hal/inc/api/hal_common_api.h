#ifndef __HAL_COMMON_API_H__
#define __HAL_COMMON_API_H__

#include <stddef.h>

#if __has_include("bsp_cfg.h")
#include "bsp_cfg.h"
#endif

/** Assert / logging behaviour (BSP-level):
 *  1 = HAL_ASSERT returns HAL_ERR_ASSERTION + calls hal_error_log (default)
 *  2 = HAL_ASSERT calls C assert() (aborts, useful under debugger)
 *  3 = HAL_ASSERT compiles out; no runtime overhead
 *  Override via bsp_cfg.h or the compiler command line. */
#ifndef BSP_CFG_ASSERT
#define BSP_CFG_ASSERT    (1)
#endif

#if (2 == BSP_CFG_ASSERT)
#include <assert.h>
#endif

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

/** Weak error-log hook. Override to route errors to UART, RTT, breakpoint, etc. */
extern void hal_error_log(hal_err_t err, const char * file, int line);

HAL_FOOTER

#if (1 == BSP_CFG_ASSERT)
#ifndef HAL_ERROR_LOG
#define HAL_ERROR_LOG(err)    hal_error_log((err), __FILE__, __LINE__)
#endif
#else
#define HAL_ERROR_LOG(err)
#endif

#define HAL_ERROR_RETURN(a, err)                        \
    {                                                   \
        if ((a))                                        \
        {                                               \
            (void) 0;                                   \
        }                                               \
        else                                            \
        {                                               \
            HAL_ERROR_LOG(err);                         \
            return err;                                 \
        }                                               \
    }

#ifndef HAL_RETURN
#define HAL_RETURN(err)                                 \
    {                                                   \
        HAL_ERROR_LOG(err);                             \
        return err;                                     \
    }
#endif

#if (3 == BSP_CFG_ASSERT)
#define HAL_ASSERT(a)
#elif (2 == BSP_CFG_ASSERT)
#define HAL_ASSERT(a)    { assert(a); }
#else
#define HAL_ASSERT(a)    HAL_ERROR_RETURN((a), HAL_ERR_ASSERTION)
#endif

#endif // __HAL_COMMON_API_H__
