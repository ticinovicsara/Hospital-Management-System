#include "../Headers/doctor.h"
#include "../Headers/help-functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void AddDoctor(SpecializationNodePtr* root){
    printf("\nUnesite podatke za novog doktora:\n");

    DoctorPtr newDoctor = (DoctorPtr)malloc(sizeof(Doctor));
    if (!newDoctor) {
        printf("Greska pri alokaciji memorije za doktora\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char specialization[MAX_NAME_LENGTH];

    Input("ime", name, "doktora");
    Input("prezime", surname, "doktora");

    capitalizeName(name);
    capitalizeName(surname);

    strcpy(newDoctor->name, name);
    strcpy(newDoctor->surname, surname);

    PrintSpecializations(*root);
    Input("specijalizaciju", specialization, "doktora");
    capitalizeName(specialization);

    newDoctor->availableAppointments = 10;
    newDoctor->appointments = NULL;
    newDoctor->next = NULL;
    newDoctor->patients = NULL;

    *root = InsertDoctor(*root, specialization, name, surname, 10);

    clearScreen();
    printf("Doktor uspjesno kreiran\n\n");
}

void DeleteDoctorByNameSurname(SpecializationNodePtr root){
    printf("\nBrisanje doktora: \n");
    PrintDoctors(root);

    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];

    Input("ime", name, "doktora");
    Input("prezime", surname, "doktora");

    capitalizeName(name);
    capitalizeName(surname);

    if(!SearchDoctorByName(root, name, surname)){
        clearScreen();
        printf("\nDoktor '%s %s' nije pronadjen.\n", name, surname);
        return;
    }

    SpecializationNodePtr updatedRoot = DeleteDoctor(root, name, surname);

    if (updatedRoot) {
        clearScreen();
        printf("\nDoktor '%s %s' je uspjesno obrisan.\n", name, surname);
    }
}