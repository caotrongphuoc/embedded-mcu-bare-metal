#include "hal_common_api.h"

extern void hal_entry(void);

__attribute__((weak)) int main(void)
{
	hal_entry();

	return 0;
}

__attribute__((weak)) void hal_error_log(hal_err_t err, const char * file, int line)
{
	HAL_PARAMETER_NOT_USED(err);
	HAL_PARAMETER_NOT_USED(file);
	HAL_PARAMETER_NOT_USED(line);
}
