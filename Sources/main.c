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

    PriorityQueue* pq = NULL;
    initializeQueue(&pq);
    ReadEmergencyCases(pq);

    int option;

    while (1) {
        printf("\n===== Hospital Management System =====\n");
        printf("Dobrodosli! Za nastavak odaberite radnju:\n");
        printf("1 - Pacijenti\n");
        printf("2 - Doktori\n");
        printf("3 - Upravljanje hitnim slucajevima\n");
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

    return 0;
}

void manageEmergencyCases(PriorityQueue* pq){
    manageEmergencyCase(pq);
}