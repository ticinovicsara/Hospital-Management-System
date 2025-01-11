#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Headers/patient.h"
#include "../Headers/doctor.h"
#include "../Headers/help-functions.h"

void deletePatient(HashTable ht);
void searchPatients(HashTable ht);

void showPatientMenu(HashTable* hash_table, SpecializationNodePtr root){
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
                AddPatient(*hash_table);
                break;
            case 2:
                clearScreen();
                deletePatient(*hash_table);
                getchar();
                break;
            case 3:
                clearScreen();
                searchPatients(*hash_table);
                break;
            case 4:
                clearScreen();
                ReserveAnAppointment(*hash_table, root);
                break;
            case 5:
                clearScreen();
                ListAllPatients(hash_table);
                PressAnyKey();
                clearScreen();
                break;
            case 0:
                clearScreen();
                return;
            default:
                clearScreen();
                printf("Neispravan unos, pokusajte ponovo.\n\n");
                break;
        }
    }
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
        
        if (option == 1) {
            char id[10];
            getchar();
            getID(id);

            Patientptr p = SearchPatientByID(&ht, id);
            if(!p){
                clearScreen();
                printf("\nPacijent s ID: '%s' nije nadjen\n", p->id);
                continue;
            }
            PatientDetails(p);
            break;
        }
        else if (option == 2) {
            char surname[MAX_NAME_LENGTH];

            Input("prezime", surname, "pacijenta");

            Patientptr p = SearchPatientBySurname(&ht, surname);
            if(!p){
                clearScreen();
                printf("Pacijent s imenom '%s' nije nadjen\n\n", p->name);
                continue;
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