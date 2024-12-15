#include <stdio.h>
#include "emergency.h"
#include "../Headers/help-functions.h"


void manageEmergencyCase(){
    static PriorityQueue pq;
    initializeQueue(&pq);

    while(true){
        clearScreen();
        printf("\nUpravljanje hitnim slucajevima:\n");
        printf("1 - Dodaj hitni slucaj\n");
        printf("2 - Obradi hitni slucaj\n");
        printf("3 - Pogledaj najhitniji slucaj\n");
        printf("\n0 - Povratak\n");
        printf(": ");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                    EmergencyCase newCase;
                    printf("Unesite ID hitnog slucaja: ");
                    scanf("%d", &newCase.id);
                    printf("Unesite opis hitnog slucaja: ");
                    getchar();
                    fgets(newCase.description, sizeof(newCase.description), stdin);
                    printf("Unesite prioritet hitnog slucaja (manji broj = veci prioritet): ");
                    scanf("%d", &newCase.priority);
                    
                    enqueue(&pq, newCase);
                    printf("Hitni slucaj dodan.\n");
                    break;
            case 2:
                    EmergencyCase processedCase = dequeue(&pq);
                    if (processedCase.id != 0) {
                        printf("Obradjen hitni slucaj ID: %d, Opis: %s\n", processedCase.id, processedCase.description);
                    }
                    break;
            case 3:
                    EmergencyCase topCase = peek(&pq);
                    if (topCase.id != 0) {
                        printf("Najhitniji slucaj: ID: %d, Opis: %s, Prioritet: %d\n", topCase.id, topCase.description, topCase.priority);
                    }
                    break;
            case 0:
                return;
            default:
                printf("Neispravan unos. Pokusajte ponovo.\n");
                break;
        }
    }
}