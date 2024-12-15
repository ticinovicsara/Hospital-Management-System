#include "../Headers/patient.h"
#include "../Headers/help-functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void AddPatient(HashTable ht){
    clearScreen();
    printf("\nUnesite podatke za novog pacijenta:\n");

    Patientptr newPatient = (Patientptr)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Greska pri alokaciji memorije za pacijenta\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];

    inputNameAndSurname(name, surname);
    strcpy(newPatient->name, name);
    strcpy(newPatient->surname, surname);

    do {
        printf("\nUnesite datum rodjenja pacijenta u formatu (DD.MM.YYYY): ");
        scanf("%s", newPatient->birthDate);

        if (!isValidDate(newPatient->birthDate)) {
            printf("Datum nije valjan, pokusajte ponovo.\n");
        }
    } while (!isValidDate(newPatient->birthDate));

    newPatient->history = NULL;

    InsertPatient(&ht, newPatient);

    printf("Pacijent uspjesno kreiran.\n");
}

void inputNameAndSurname(char* name, char* surname) {
    do {
        printf("\nUnesite ime pacijenta: ");
        scanf("%s", name);

        if (!stringIsValid(name)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(name));

    do {
        printf("\nUnesite prezime pacijenta: ");
        scanf("%s", surname);

        if (!stringIsValid(surname)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(surname));
}


void DeletePatientBySurname(HashTable* ht){
    clearScreen();
    printf("Brisanje pacijenta po ID-u i prezimenu:\n");

    char id[10];
    char surname[MAX_NAME_LENGTH];

    do {
        printf("Unesite ID pacijenta: ");
        scanf("%s", id);

        if (strlen(id) == 0) {
            printf("ID ne moze biti prazan, pokusajte ponovo.\n");
        }
    } while (strlen(id) == 0);

    do {
        printf("Unesite prezime pacijenta: ");
        scanf("%s", surname);

        if (!stringIsValid(surname)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(surname));


    DeletePatient(ht, id, surname);
    printf("\n");
}


