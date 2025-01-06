#include <stdio.h>
#include "../Headers/emergency.h"
#include "../Headers/help-functions.h"


void manageEmergencyCase(PriorityQueue* pq){
    while(true){
        clearScreen();
        printf("\nUpravljanje hitnim slucajevima:\n");
        printf("1 - Dodaj hitni slucaj\n");
        printf("2 - Pogledaj najhitniji slucaj\n");
        printf("\n0 - Povratak\n");
        printf(": ");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                    EmergencyCase newCase;
                    printf("Unesite ID hitnog slucaja: ");
                    scanf("%s", newCase.id);
                    printf("Unesite opis hitnog slucaja: ");
                    getchar();
                    fgets(newCase.description, sizeof(newCase.description), stdin);
                    printf("Unesite prioritet hitnog slucaja (manji broj = veci prioritet): ");
                    scanf("%d", &newCase.priority);
                    
                    enqueue(pq, newCase);
                    printf("Hitni slucaj dodan\n");
                    break;
            case 2:
                    EmergencyCase topCase = peek(pq);
                    if (topCase.id != 0) {
                        printf("Najhitniji slucaj: ID: %s, Opis: %s, Prioritet: %d\n", topCase.id, topCase.description, topCase.priority);
                    }
                    break;
                    break;
            case 0:
                return;
            default:
                printf("Neispravan unos, pokusajte ponovo.\n");
                break;
        }
    }
}