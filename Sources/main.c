#include "../Headers/read_files.h"
#include "../Headers/patient.h"
#include "../Headers/help-functions.h"
#include "../Headers/emergency.h"
#include "../Headers/menus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void manageEmergencyCases(PriorityQueue* pq);

int main(){
    HashTable* hash_table = CreateHashTable(11);
    ReadPatients(hash_table);

    SpecializationNodePtr root = NULL;
    ReadDoctors(&root);

    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        printf("nemoguce alocirati memoriju\n");
        exit(1);
    }
    initializeQueue(pq);
    ReadEmergencyCases(pq);

    char input[100];
    int option;

    clearScreen();

    while (1) {
        printf("\n===== Hospital Management System =====\n\n");
        printf("Dobrodosli! Za nastavak odaberite radnju:\n");
        printf("1 - Pacijenti\n");
        printf("2 - Doktori\n");
        printf("3 - Hitni slucajevi\n");
        printf("0 - Izlaz\n");
        printf("\n: ");
        
        if (!fgets(input, sizeof(input), stdin)) {
            clearScreen();
            printf("Greska pri citanju unosa, pokusajte ponovo.\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "%d", &option) != 1) {
            clearScreen();
            printf("Neispravan unos, unesite broj.\n");
            continue;
        }

        switch (option) {
            case 1:
                showPatientMenu(hash_table);
                break;
            case 2:
                showDoctorMenu(root);
                break;
            case 3:
                manageEmergencyCase(pq);
                break;
            case 0:
                printf("Izlaz iz programa...\n");
                exit(0);
                break;
            default:
                clearScreen();
                printf("Neispravan unos, pokusajte ponovo.\n");
                printf("Pritisnite bilo sto za nastavak...\n");
                getchar();
                break;
        }
    }

    free(pq);
    free(root);
    return 0;
}

void manageEmergencyCases(PriorityQueue* pq){
    if (pq == NULL || pq->size == 0) {
        printf("Red je prazan ili nije inicijalizovan.\n");
        return;
    }
    manageEmergencyCase(pq);
}