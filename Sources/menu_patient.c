#include <stdio.h>
#include <string.h>
#include "../Headers/patient.h"
#include "../Headers/help-functions.h"

void addPatient(HashTable ht);
void deletePatient(HashTable ht);
void searchPatients(HashTable ht);

void showPatientMenu(HashTable* hash_table){
    clearScreen();
    printf("1 - Dodaj pacijenta\n");
    printf("2 - Obrisi pacijenta\n");
    printf("3 - Pretrazi pacijente\n");
    printf("4 - Rezerviraj termin kod doktora\n");
    printf("5 - Svi pacijenti\n");
    printf("\n0 - Povratak\n");

    int option;
    scanf("%d", &option);

    while(1){
        switch (option) {
            case 1:
                addPatient(*hash_table);
                break;
            case 2:
                deletePatient(*hash_table);
                break;
            case 3:
                searchPatients(*hash_table);
                break;
            case 4:
                //reserveAppointment();
                break;
            case 5:
                ListAllPatients(hash_table);
                break;
            case 0:
                return;
            default:
                printf("Neispravan unos, pokusajte ponovo.\n");
        }
    }
}


void addPatient(HashTable ht){
    AddPatient(ht);
    return;
}

void deletePatient(HashTable ht){
    DeletePatientBySurname(&ht);
}

void searchPatients(HashTable ht){
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

            SearchPatientByID(&ht, id);
            break;
        }
        else if (option == 2) {
            char name[MAX_NAME_LENGTH];
            char surname[MAX_NAME_LENGTH];

            inputNameAndSurname(name, surname);

            SearchPatientByName(&ht, name, surname);
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