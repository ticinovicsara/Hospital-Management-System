#include "../Headers/patient.h"
#include "../Headers/help-functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void AddPatient(HashTable ht){
    printf("\nUnesite podatke za novog pacijenta:\n");

    Patientptr newPatient = (Patientptr)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Greska pri alokaciji memorije za pacijenta\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];

    InputName(name);
    InputSurname(surname);
    strcpy(newPatient->name, name);
    strcpy(newPatient->surname, surname);

    char birth[MAX_DATE_LENGTH];
    getBirthDate(birth);
    strcpy(newPatient->birthDate, birth);

    newPatient->history = NULL;

    InsertPatient(&ht, newPatient);

    clearScreen();
    printf("Pacijent uspjesno kreiran\n\n");
    return;
}


void DeletePatientByIDSurname(HashTable* ht){
    printf("Brisanje pacijenta po ID-u i prezimenu:\n");

    char id[10];
    char surname[MAX_NAME_LENGTH];

    getID(id);

    InputSurname(surname);

    if(!DeletePatient(ht, id, surname)){
        clearScreen();
        printf("\nPacijent sa navedenim ID-om i prezimenom ne postoji\n\n");
        return;
    }
    clearScreen();
    printf("\nPacijent sa ID %s i prezimenom %s je obrisan.\n", id, surname);
    printf("\n");
}


