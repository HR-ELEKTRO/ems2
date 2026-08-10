/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
#include <math.h>
void BOARD_InitHardware(void);

typedef struct {
    int type;
    int index;
    double waarde;
} PassieveComponent;

// print_float prints a floating point number in scientific notation
// needed because the PRINTF function does not support scientific notation
// precision specifies the number of digits after the decimal point
void print_float(double value, int precision)
{
    int exponent = roundf(log10(fabs(value)));
    double mantissa = value / pow(10, exponent);
    PRINTF("%.*fE%d", precision, mantissa, exponent);
}

void printComponent(PassieveComponent c)
{
    switch (c.type)
    {
    case 1:
        PRINTF("R%d = ", c.index);
        print_float(c.waarde, 1);
        PRINTF(" ohm");
        break;
    case 2:
        PRINTF("C%d = ", c.index);
        print_float(c.waarde, 1);
        PRINTF(" farad");
        break;
    case 3:
        PRINTF("L%d = ", c.index);
        print_float(c.waarde, 1);
        PRINTF(" henry");
        break;
    }
}

int main(void)
{
    BOARD_InitHardware();
    
    PassieveComponent c[] = {
        {1, 1, 1E6}, {1, 2, 2.7E3}, {2, 1, 1E-9}, {3, 1, 1E-3}, {2, 2, 15E-6}
    };

    PRINTF("\n");
    for (size_t i = 0; i < sizeof c / sizeof c[0]; i++)
    {
        printComponent(c[i]);
        PRINTF("\n");
    }

    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
