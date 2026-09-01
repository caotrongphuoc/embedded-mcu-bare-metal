#ifndef __BSP_COMPILER_SUPPORT_H__
#define __BSP_COMPILER_SUPPORT_H__

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define BSP_ATTRIBUTE_STACKLESS    __attribute__((naked))
#elif defined(__ICCARM__)
#define BSP_ATTRIBUTE_STACKLESS    __stackless
#else
#define BSP_ATTRIBUTE_STACKLESS
#endif

#endif // __BSP_COMPILER_SUPPORT_H__
