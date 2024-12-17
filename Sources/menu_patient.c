#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Headers/patient.h"
#include "../Headers/help-functions.h"

void addPatient(HashTable ht);
void deletePatient(HashTable ht);
void searchPatients(HashTable ht);

void showPatientMenu(HashTable* hash_table){
    while(1){
        printf("\n---- PACIJENTI ----\n\n");
        printf("1 - Dodaj pacijenta\n");
        printf("2 - Obrisi pacijenta\n");
        printf("3 - Pretrazi pacijente\n");
        printf("4 - Rezerviraj termin kod doktora\n");
        printf("5 - Svi pacijenti\n");
        printf("\n0 - Povratak\n\n");
        printf(": ");

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
                addPatient(*hash_table);
                clearBuffer();
                break;
            case 2:
                clearScreen();
                deletePatient(*hash_table);
                clearBuffer();
                break;
            case 3:
                clearScreen();
                searchPatients(*hash_table);
                clearBuffer();
                break;
            case 4:
                clearScreen();
                //reserveAppointment();
                clearBuffer();
                break;
            case 5:
                clearScreen();
                ListAllPatients(hash_table);
                clearBuffer();
                break;
            case 0:
                clearBuffer();
                clearScreen();
                return;
            default:
                clearScreen();
                printf("Neispravan unos, pokusajte ponovo.\n\n");
                break;
        }
    }
}

void addPatient(HashTable ht){
    AddPatient(ht);
    return;
}

void deletePatient(HashTable ht){
    ListAllPatients(&ht);
    DeletePatientByIDSurname(&ht);
}

void searchPatients(HashTable ht){
    while(1){
        printf("Pretrazi pacijenta po: \n");
        printf("1 - ID-u\n");
        printf("2 - Prezimenu\n");
        printf("\n0 - Povratak\n\n");
        printf(": ");

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
        
        if (option == 1) {
            char id[10];
            getID(id);

            Patientptr p = SearchPatientByID(&ht, id);
            if(!p){
                clearScreen();
                printf("\nPacijent s navedenim ID-om nije nadjen\n", p->id);
                break;
            }
            PatientDetails(p);
            break;
        }
        else if (option == 2) {
            char name[MAX_NAME_LENGTH];
            char surname[MAX_NAME_LENGTH];

            InputSurname(surname, "pacijenta");

            Patientptr p = SearchPatientBySurname(&ht, surname);
            if(!p){
                clearScreen();
                printf("Pacijent s navedenim imenom nije nadjen\n\n", p->id);
                break;
            }

            PatientDetails(p);
            break;
        }
        else if(option == 0){
            clearScreen();
            return;
        }
        else {
            clearScreen();
            printf("Neispravan unos, pokusajte ponovo.\n\n");
            continue;
        }
    }
}