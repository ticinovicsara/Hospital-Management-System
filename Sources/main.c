#include "../Headers/read_files.h"
#include "../Headers/patient.h"
#include "../Headers/help-functions.h"
#include "../Headers/emergency.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addpatient(HashTable* ht);
void deletePatient(HashTable* ht);
void searchPatients(HashTable* ht);
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
        printf("1 - Dodaj pacijenta\n");
        printf("2 - Obrisi pacijenta\n");
        printf("3 - Pretrazi pacijente\n");
        printf("4 - Rezerviraj termin kod doktora\n");
        printf("5 - Upravljanje hitnim slucajevima\n");
        printf("6 - Svi pacijenti\n");
        printf("7 - Svi doktori\n");
        printf("8 - Svi hitni slucajevi\n");
        printf("0 - Izlaz\n");
        printf("\n: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addpatient(hash_table);
                break;
            case 2:
                deletePatient(hash_table);
                break;
            case 3:
                searchPatients(hash_table);
                break;
            case 4:
                //reserveAppointment();
                break;
            case 5:
                manageEmergencyCases(pq);
                break;
            case 6:
                manageEmergencyCases(pq);
                break;
            case 7:
                manageEmergencyCases(pq);
            case 6:
                manageEmergencyCases(pq);
                break;
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

void addpatient(HashTable* ht){
    AddPatient(ht);
}

void deletePatient(HashTable* ht){
    DeletePatientBySurname(ht);
}

void searchPatients(HashTable* ht){
    while(1){
        clearScreen();
        printf("Pretrazi pacijenta po: \n");
        printf("1 - ID-u\n");
        printf("2 - Prezimenu\n");
        printf("\n0 - Povratak\n");

        int option;
        scanf("%d", &option);
        
        if (option == 1) {
            char id[10];
            do {
                printf("\nUnesite ID pacijenta: ");
                scanf("%s", id);

                if (strlen(id) == 0) {
                    printf("ID ne smije biti prazan.\n");
                }
            } while (strlen(id) == 0);

            SearchPatientByID(ht, id);
            break;
        }
        else if (option == 2) {
            char name[MAX_NAME_LENGTH];
            char surname[MAX_NAME_LENGTH];

            inputNameAndSurname(name, surname);

            SearchPatientByName(ht, name, surname);
            break;
        }
        else if(option == 0){
            return;
        }
        else {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    }
}


void manageEmergencyCases(PriorityQueue* pq){
    manageEmergencyCase(pq);
}