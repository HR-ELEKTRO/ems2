/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
#include <string.h>
#include "cycle_counter.h"

void BOARD_InitHardware(void);

size_t strlen_met_index(const char s[])
{
    size_t i = 0;

    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

size_t strlen_met_pointer(const char *s)
{
    const char *p = s;

    while (*p != '\0')
    {
        p++;
    }
    return p - s;
}

int main(void)
{
    BOARD_InitHardware();
    cycle_counter_init();
    
    const char* test = "Hoe lang is deze string?";
    cycle_counter_reset();
    size_t len1 = strlen_met_index(test);
    uint32_t cycles1 = cycle_counter_get();

    cycle_counter_reset();
    size_t len2 = strlen_met_pointer(test);
    uint32_t cycles2 = cycle_counter_get();

    cycle_counter_reset();
    size_t len3 = strlen(test);
    uint32_t cycles3 = cycle_counter_get();

    if (len1 != len3)
    {
        PRINTF("str_len_met_index() werkt niet goed!\n");
    }
    else
    {
        PRINTF("str_len_met_index() werkt naar verwachting\n");
    }
    PRINTF("str_len_met_index() heeft %d cycles geduurd\n", cycles1);
    if (len2 != len3)
    {
        PRINTF("str_len_met_pointer() werkt niet goed!\n");
    }
    else
    {
        PRINTF("str_len_met_pointer() werkt naar verwachting\n");
    }
    PRINTF("str_len_met_pointer() heeft %d cycles geduurd\n", cycles2);
    PRINTF("strlen() heeft %d cycles geduurd\n", cycles3);
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
