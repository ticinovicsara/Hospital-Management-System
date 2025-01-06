#include <stdio.h>
#include "../Headers/doctor.h"
#include "../Headers/menus.h"
#include "../Headers/help-functions.h"

static void SearchDoctorBy(SpecializationNodePtr root);

void showDoctorMenu(SpecializationNodePtr root){
    while(1){
        printf("\n---- DOKTORI ----\n\n");
        printf("1 - Dodaj doktora\n");
        printf("2 - Obrisi doktora\n");
        printf("3 - Trazi doktora\n");
        printf("4 - Svi doktori\n");
        printf("\n0 - Povratak\n");
        printf("\n: ");

        int option;
        scanf("%d", &option);

        switch(option){
            case 1:
                clearScreen();
                AddDoctor(&root);
                break;

            case 2:
                clearScreen();
                DeleteDoctorByNameSurname(root);
                break;
            
            case 3:
                clearScreen();
                SearchDoctorBy(root);
                break;

            case 4:
                clearScreen();
                PrintDoctors(root);
                break;

            case 0:
                clearBuffer();
                clearScreen();
                return;

            default:
                printf("Neispravan unos, unesite ponovno\n");
                break;

        }
    }
}

static void SearchDoctorBy(SpecializationNodePtr root){
    while(1){
        printf("Trazenje doktora prema: \n");
        printf("1 - Imenu i prezimenu\n");
        printf("2 - Svi doktori odredjene specijalizacije\n");
        printf("\n0 - Povratak\n\n: ");

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

        switch(option){
            case 1:
                clearScreen();
                printf("Trazenje doktora prema imenu i prezimenu:\n\n");
                char name[MAX_NAME_LENGTH];
                char surname[MAX_NAME_LENGTH];
                Input("ime", name, "doktora");
                Input("prezime", surname, "doktora");

                DoctorPtr doctor = SearchDoctorByName(root, name, surname);
                if(!doctor){
                    clearScreen();
                    printf("Doktor '%s %s'nije prodnadjen\n", name, surname);
                    return;
                }

                printf("     --------------------------------------------------------------------------\n");
                printf("\tSPECIJALIZACIJA\t\tIME\t    PREZIME\t    DOSTUPNI TERMINI\n");
                printf("     --------------------------------------------------------------------------\n");
                printf("\t%-23s %-11s %-15s %-5d\n\n\n", root->specialization, doctor->name, doctor->surname, doctor->availableAppointments);

                PressAnyKey();
                clearScreen();
                break;

            case 2:
                clearScreen();
                char specialization[MAX_NAME_LENGTH];
                Input("specijalizaciju", specialization, "doktora");

                bool found = true;
                if(found){
                    clearScreen();
                    ListDoctorsBySpecialization(root, specialization);
                }

                PressAnyKey();
                clearScreen();
                break;
            
            case 0:
                clearBuffer();
                clearScreen();
                return;

            default:
                clearScreen();
                printf("Neispravan unos, unesite ponovno\n");
                break;
        }
    }
}
