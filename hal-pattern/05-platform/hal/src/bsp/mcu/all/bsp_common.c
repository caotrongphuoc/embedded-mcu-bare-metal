#include "hal_common_api.h"

extern void hal_entry(void);

__attribute__((weak)) int main(void)
{
    hal_entry();

    return 0;
}
