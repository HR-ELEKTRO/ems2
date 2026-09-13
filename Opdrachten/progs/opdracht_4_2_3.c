/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <stdint.h>

#define MRCC0_MRCC_GLB_CC1 (*(volatile uint32_t *)(0x40091050))
#define MRCC0_MRCC_GLB_RST1 (*(volatile uint32_t *)(0x40091010))
#define GPIO3_PDDR (*(volatile uint32_t *)(0x40105054))
#define GPIO3_PDOR (*(volatile uint32_t *)(0x40105040))

int main(void) {
    // Enable clock for PORT3 and GPIO3
    MRCC0_MRCC_GLB_CC1 |= (1 << 23) | (1 << 10);
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
