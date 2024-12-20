#include <stdio.h>
#include "../Headers/doctor.h"
#include "../Headers/menus.h"
#include "../Headers/help-functions.h"

void showDoctorMenu(SpecializationNodePtr root){
    while(1){
        printf("\n---- DOKTORI ----\n\n");
        printf("1 - Dodaj doktora\n");
        printf("2 - Obrisi doktora\n");
        printf("3 - Trazi doktora\n");
        printf("4 - Dodjela pacijenta doktoru\n");
        printf("5 - Svi doktori\n");
        printf("\n0 - Povratak\n");
        printf("\n: ");

        int option;
        scanf("%d", &option);

        switch(option){
            case 1:
                break;

            case 2:
                break;
            
            case 3:
                break;

            case 4:
                break;

            case 5:
                clearScreen();
                ListAllDoctors(root);
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

