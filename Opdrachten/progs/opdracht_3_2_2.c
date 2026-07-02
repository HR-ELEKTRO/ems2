/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
#include <stdbool.h>
#include <math.h>

void BOARD_InitHardware(void);

bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    int i;
    for (i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    BOARD_InitHardware();
    
    int number;
    PRINTF("Geef een geheel number: ");
    SCANF("%d", &number);
    PRINTF("Het number %d is ", number);
    if (isPrime(number))
    {
        PRINTF("een ");
    }
    else
    {
        PRINTF("geen ");
    }
    PRINTF("priemgetal\n");
    
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
