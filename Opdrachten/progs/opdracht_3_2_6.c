/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
#include <stdint.h>
#include "cycle_counter.h"

void BOARD_InitHardware(void);

void keerom_met_indexen(char *s)
{
    size_t eerste = 0;
    size_t laatste = strlen(s) - 1;

    while (laatste > eerste)
    {
        char hulp = s[eerste];
        s[eerste] = s[laatste];
        s[laatste] = hulp;
        eerste++;
        laatste--;
    }
}

void keerom_met_pointers(char *s)
{
    char *p_eerste = s;
    char *p_laatste = s + strlen(s) - 1;

    // vul hier je code in
}

int main(void)
{
    BOARD_InitHardware();
    cycle_counter_init();
    
    char test1[] = "Keer dit eens om";
    PRINTF("\"%s\" omgekeerd is ", test1);
    cycle_counter_reset();
    keerom_met_indexen(test1);
    uint32_t cycles1 = cycle_counter_get();
    PRINTF("\"%s\"\n", test1);

    char test2[] = "Keer dit eens om";
    PRINTF("\"%s\" omgekeerd is ", test2);
    cycle_counter_reset();
    keerom_met_pointers(test2);
    uint32_t cycles2 = cycle_counter_get();
    PRINTF("\"%s\"\n", test1);

    PRINTF("keerom_met_indexen() heeft %d cycles geduurd\n", cycles1);
    PRINTF("keerom_met_pointers() heeft %d cycles geduurd\n", cycles2);
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
