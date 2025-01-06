#include <stdio.h>
#include "../Headers/emergency.h"
#include "../Headers/help-functions.h"
#include "../Headers/patient.h"

void showEmergencyCaseMenu(PriorityQueue* pq, HashTable* ht){
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
                AddEmergencyCase(pq, ht);
                break;
            case 2:
                clearScreen();
                EmergencyCase topCase = peek(pq);
                if (topCase.patientId[0] != '\0') {
                    printf("Najhitniji slucaj:\n\n");
                    printf("   ---------------------------------------------------------------\n");
                    printf("     Prioritet      ID pacijenta           Opis\n");
                    printf("   ---------------------------------------------------------------\n");
                    printf("        %d              %s              %s\n", topCase.priority, topCase.patientId, topCase.description);
                    printf("   ---------------------------------------------------------------\n");
                }
                PressAnyKey();
                clearScreen();
                break;
            case 3:
                clearScreen();
                ListAllEmergencyCases(pq);
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
