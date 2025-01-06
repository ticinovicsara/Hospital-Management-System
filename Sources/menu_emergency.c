#include <stdio.h>
#include "../Headers/emergency.h"
#include "../Headers/help-functions.h"

void showEmergencyCaseMenu(PriorityQueue* pq){
    while(true){
        printf("\n---- HITNI SLUCAJEVI ----\n\n");
        printf("1 - Dodaj hitni slucaj\n");
        printf("2 - Pogledaj najhitniji slucaj\n");
        printf("3 - Svi hitni slucajevi\n");
        printf("\n0 - Povratak\n");
        printf("\n: ");

        char input[100];
        int option;

        if (!fgets(input, sizeof(input), stdin)) {
            printf("Greska pri citanju unosa, pokusajte ponovo.\n");
            continue;
        }
        if (sscanf(input, "%d", &option) != 1) {
            clearScreen();
            printf("Neispravan unos, pokusajte ponovo.\n\n");
            continue;
        }


        if (sscanf(input, "%d", &option) != 1) {
            clearScreen();
            printf("\nNeispravan unos, unesite broj.\n\n");
            continue;
        }

        switch (option) {
            case 1:
                clearScreen();
                EmergencyCase newCase;
                getID(newCase.id);
                printf("Unesite opis hitnog slucaja: ");
                getchar();
                fgets(newCase.description, sizeof(newCase.description), stdin);
                printf("Unesite prioritet hitnog slucaja (manji broj = veci prioritet): ");
                scanf("%d", &newCase.priority);
                    
                enqueue(pq, newCase);
                printf("Hitni slucaj dodan\n");
                clearBuffer();
                break;
            case 2:
                clearScreen();
                EmergencyCase topCase = peek(pq);
                if (topCase.id[0] != '\0') {
                    printf("Najhitniji slucaj: ID: %s, Opis: %s, Prioritet: %d\n", topCase.id, topCase.description, topCase.priority);
                }
                clearBuffer();
                break;
            case 3:
                clearScreen();
                ListAllEmergencyCases(pq);
                clearBuffer();
                break;
            case 0:
                clearBuffer();
                clearScreen();
                return;
            default:
                clearScreen();
                printf("Neispravan unos, pokusajte ponovo.\n");
                break;
        }
    }
}