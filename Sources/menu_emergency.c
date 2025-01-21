#include <stdio.h>
#include <string.h>
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
                    printf("        %-17d%-18s%s\n", topCase.priority, topCase.patientId, topCase.description);
                    printf("   ---------------------------------------------------------------\n");
                }

                char input[5];
                do{
                    printf("\n\nRijesi ovaj slucaj? (y/n): ");
                    scanf(" %s", input);

                    if(strcmp(input, "y") == 0){
                        dequeue(pq);
                        printf("\n\nSlucaj rijesen.\n");
                        break;
                    }
                    else if(strcmp(input, "n") == 0) { break; }
                    else{
                        printf("\nUnesite 'y' ili 'n'\n");
                    }
                }while(stringIsValid(input));

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
                getchar();
                printf("Neispravan unos, pokusajte ponovo.\n");
                break;
        }
    }
}
