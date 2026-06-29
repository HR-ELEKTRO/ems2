/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
void BOARD_InitHardware(void);

void sorteer(int a, int b)
{
    if (a > b)
    {
        int hulpje = a;
        a = b;
        b = hulpje;
    }
}

int main(void)
{
    BOARD_InitHardware();
    
    int x1 = 7, x2 = 8;
    sorteer(x1, x2);
    if (x1 == 7 && x2 == 8)
    {
        PRINTF("Test 1 geslaagd!\n");
    }
    else
    {
        PRINTF("Test 1 NIET geslaagd!\n");
    }
    int x3 = 8, x4 = 7;
    sorteer(x3, x4);
    if (x3 == 7 && x4 == 8)
    {
        PRINTF("Test 2 geslaagd!\n");
    }
    else
    {
        PRINTF("Test 2 NIET geslaagd!\n");
    }
    
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
