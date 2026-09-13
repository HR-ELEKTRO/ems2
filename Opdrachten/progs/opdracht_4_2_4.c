/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <MCXA156.h>

int main(void) {
    // Enable clock for PORT3 and GPIO3
    MRCC0->MRCC_GLB_CC1 |= MRCC_MRCC_GLB_CC1_PORT3_MASK | MRCC_MRCC_GLB_CC1_GPIO3_MASK;
    // Release PORT3 and GPIO3 from reset
    // PLACE YOUR CODE HERE
    // Set GPIO3 pin for blue led as output
    // PLACE YOUR CODE HERE
    while (1) {
        // Toggle GPIO3 pin for blue led
        // PLACE YOUR CODE HERE
        // Simple delay loop
        volatile uint32_t i = 0;
        while (i < 500000) {
            i++;
        }
    }
}
