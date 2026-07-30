/*
 * Copyright (C) 2026, Hogeschool Rotterdam
 * All rights reserved.
 */

#include <fsl_debug_console.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void BOARD_InitHardware(void);

#define AANTAL_SPELERS_IN_LIJST 3
#define MAX_AANTAL_KARAKTERS_IN_NAAM 15

typedef struct {
    char naam[MAX_AANTAL_KARAKTERS_IN_NAAM + 1];
    unsigned int punten;
} Speler;

void maakLijstLeeg(Speler lijst[], size_t aantalInLijst)
{
    for (size_t i = 0; i < aantalInLijst; i++)
    {
        size_t ci;
        for (ci = 0; ci < MAX_AANTAL_KARAKTERS_IN_NAAM; ci++)
        {
            lijst[i].naam[ci] = '-';
        }
        lijst[i].naam[ci] = '\0';
        lijst[i].punten = 0;
    }
}

void printLijst(Speler lijst[], size_t aantalInLijst)
{
    for (size_t i = 0; i < aantalInLijst; i++)
    {
        PRINTF("%-*s %5d\n", MAX_AANTAL_KARAKTERS_IN_NAAM, lijst[i].naam, lijst[i].punten);
    }
}

void zetBovenaanInLijst(Speler s, Speler lijst[], size_t aantalInLijst)
{
    // Alle voorgaande spelers een plaatsje opschuiven:
    for (size_t i = aantalInLijst - 1; i > 0; i--)
    {
        lijst[i] = lijst[i - 1];
    }
    // De laatste speler komt bovenaan de lijst:
    lijst[0] = s;
}

int speelSpel(void)
{
    // Hier komt  de code die het spel bestuurt.
    // Het aantal behaalde punten wordt als returnwaarde teruggegeven.
    return rand() & 0xFFFF; // 16-bits random waarde
}

void leesNaam(char s[])
{
    char karakter;
    size_t i = 0;
    do
    {
        karakter = GETCHAR();
        if (isprint(karakter) && i != MAX_AANTAL_KARAKTERS_IN_NAAM)
        {
            s[i] = karakter;
            i++;
        }
    }
    while (karakter != '\r' && karakter != '\n');
    s[i] = '\0';
}

int main(void)
{
    BOARD_InitHardware();
    
    int getal;
    PRINTF("Type een willekeurig getal in: ");
    SCANF("%d", &getal);
    srand(getal);

    Speler laatsteSpelers[AANTAL_SPELERS_IN_LIJST];
    maakLijstLeeg(laatsteSpelers, AANTAL_SPELERS_IN_LIJST);

    while (1)
    {
        Speler s;
        s.punten = speelSpel();
        PRINTF("Je hebt %d punten behaald, type nu je naam in: ", s.punten);
        leesNaam(s.naam);
        zetBovenaanInLijst(s, laatsteSpelers, AANTAL_SPELERS_IN_LIJST);
        PRINTF("Laatste %d spelers:\n", AANTAL_SPELERS_IN_LIJST);
        printLijst(laatsteSpelers, AANTAL_SPELERS_IN_LIJST);
    }
    
    // Wacht tot debugger afgesloten wordt
    while (1);
    return 0;
}
