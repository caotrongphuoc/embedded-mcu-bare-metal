#include "board.h"
#include "bsp_clocks.h"

#if defined(BOARD_AK_BASE_KIT)

/** Performs initialization specific to the AK Base Kit. */
void bsp_init(void * p_args)
{
	HAL_PARAMETER_NOT_USED(p_args);

	bsp_clock_init();
}

#endif
