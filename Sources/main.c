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

    int option;

    while (1) {
        clearScreen();
        printf("\n===== Hospital Management System =====\n\n");
        printf("Dobrodosli! Za nastavak odaberite radnju:\n");
        printf("1 - Pacijenti\n");
        printf("2 - Doktori\n");
        printf("3 - Hitni slucajevi\n");
        printf("0 - Izlaz\n");
        printf("\n: ");
        scanf("%d", &option);

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
            default:
                printf("Neispravan unos, pokusajte ponovo.\n");
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