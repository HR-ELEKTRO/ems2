/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <mcxa156.h>
#include "cycle_counter.h"

void cycle_counter_init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void cycle_counter_reset(void) {
    DWT->CYCCNT = 0;
}

uint32_t cycle_counter_get(void) {
    return DWT->CYCCNT;
}
