/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
void BOARD_InitHardware(void);

int main(void)
{
    BOARD_InitHardware();
    
    int i = 51966;
    char c = '?';
    double d = 3.141592653;
    char s[] = "Dit is een string!";
    
    // Vul hier je code in
    
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
