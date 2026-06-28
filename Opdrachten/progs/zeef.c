/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
#include <stdbool.h>
#include <math.h>
void BOARD_InitHardware(void);

void zeef(bool b[], size_t n)
{
    b[0] = false;
    b[1] = false;
    //for (size_t i = 2; i < n; i++)
    // Versnelling 3:
    for (size_t i = 2; i <= sqrt(n); i++)
    {
        // Versnelling 1:
        if (b[i] == true)
        {
            //for (int streep = 2 * i; streep < n; streep = streep + i)
            // Versnelling 2:
            for (size_t streep = 2 * i; streep < n; streep = streep + i)
            {
                b[streep] = false;
            }
        }
    }
}

void initBoolArray(bool a[], size_t n, bool init)
{
    for (size_t i = 0; i < n; i++)
    {
        a[i] = init;
    }
}

void printBoolArrayTrueIndexes(bool a[], size_t n)
{
    int teller = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (a[i] == true)
        {
            PRINTF("%d ", i);
            teller++;
            if (teller == 10)
            {
                PRINTF("\n");
                teller = 0;
            }
        }
    }
}

int main(void)
{
    BOARD_InitHardware();
    
    bool isPriem[1000];
    size_t n = sizeof isPriem / sizeof isPriem[0];
    initBoolArray(isPriem, n, true);
    zeef(isPriem, n);
    PRINTF("Alle priemgetallen < %d:\n", n);
    printBoolArrayTrueIndexes(isPriem, n);
    PRINTF("\n");
    
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
