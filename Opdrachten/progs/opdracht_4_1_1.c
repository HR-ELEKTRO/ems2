/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
void BOARD_InitHardware(void);

typedef struct {
    int teller;
    int noemer;
} Breuk;

int ggd(int n, int m)
{
    if (m == 0)
    {
        return n;
    }
    else
    {
        return ggd(m, n % m);
    }
}

Breuk normaliseer(Breuk b)
{
    int d = ggd(b.teller, b.noemer);
    b.teller /= d;
    b.noemer /= d;
    if (b.noemer < 0)
    {
        b.noemer = -b.noemer;
        b.teller = -b.teller;
    }
    return b;
}

Breuk product(Breuk b1, Breuk b2)
{
    Breuk p;
    p.teller = b1.teller * b2.teller;
    p.noemer = b1.noemer * b2.noemer;
    return normaliseer(p);
}

int main(void)
{
    BOARD_InitHardware();
    
    Breuk a = {-7, 14}, b = {2, -3};

    Breuk c = som(a, b);
    PRINTF("c = %d/%d\n", c.teller, c.noemer);

    Breuk d = product(a, b);
    PRINTF("d = %d/%d\n", d.teller, d.noemer);
    
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
