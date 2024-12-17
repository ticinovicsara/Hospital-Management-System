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

    InputName(name, "pacijenta");
    InputSurname(surname, "pacijenta");
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
    
    InputSurname(surname, "pacijenta");

    if(!DeletePatient(ht, id, surname)){
        clearScreen();
        printf("\nPacijent sa navedenim ID-om i prezimenom ne postoji\n\n");
        return;
    }
    clearScreen();
    printf("\nPacijent sa ID %s i prezimenom %s je obrisan.\n", id, surname);
    printf("\n");
}


void ReserveAnAppointment(HashTable ht, SpecializationNodePtr root){
    printf("Rezerviranje termina kod doktora:\n");

    char specialization[MAX_NAME_LENGTH];
    char doctorName[MAX_NAME_LENGTH];
    char doctorSurname[MAX_NAME_LENGTH];
    char appointment[MAX_DATE_LENGTH];

    printf("\nUnesite specijalizaciju: ");
    ListAllSpecializations(root);
    fgets(specialization, MAX_NAME_LENGTH, stdin);
    specialization[strcspn(specialization, "\n")] = '\0';  // Uklanja newline karakter


    ListDoctorsBySpecialization(root, specialization);
    InputName(doctorName, "doktora");
    InputSurname(doctorSurname, "doktora");

    DoctorPtr doctor = SearchDoctorByName(root, doctorName, doctorSurname);
    if(!doctor){
        printf("Doktor nije pronadjen\n");
        return;
    }

    printf("\n\nOdaberite termin: ");
    ListAvailableAppointments(doctor);
    getDate(appointment);

    if (!isAppointmentAvailable(doctor->appointments, appointmentDate)) {
        printf("Termin %s nije dostupan, pokusajte ponovo.\n", appointmentDate);
        return;
    }

    printf("\nUnesite ID pacijenta: ");
    char patientID[10];
    getID(patientID);
    Patientptr patient = FindPatientByID(ht, patientID);
    if (!patient) {
        printf("Pacijent nije pronadjen.\n");
        return;
    }

    doctor->appointments = InsertAppointment(doctor->appointments, appointment, patient->id);
    doctor->availableAppointments--;

    AddToPatientHistory(patient, appointment, "Zakazan termin kod doktora");

    printf("Termin %s je uspjesno rezerviran za pacijenta %s %s kod doktora %s %s.\n", appointment, patient->name, patient->surname, doctor->name, doctor->surname);
}

bool isAppointmentAvailable(AppointmentNodePtr root, const char* date) {
    if (root == NULL) {
        return true;
    }
    int cmp = strcmp(date, root->appointment.date);
    if (cmp < 0) {
        return isAppointmentAvailable(root->left, date);
    } else if (cmp > 0) {
        return isAppointmentAvailable(root->right, date);
    } else {
        return false;
    }
}

AppointmentNodePtr InsertAppointment(AppointmentNodePtr root, const char* date, int patientID) {
    if (root == NULL) {
        AppointmentNodePtr newNode = malloc(sizeof(AppointmentNode));
        newNode->appointment.id = patientID;
        strcpy(newNode->appointment.date, date);
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    int cmp = strcmp(date, root->appointment.date);
    if (cmp < 0) {
        root->left = InsertAppointment(root->left, date, patientID);
    } else if (cmp > 0) {
        root->right = InsertAppointment(root->right, date, patientID);
    }
    return BalanceTree(root);
}

void AddToIllnessHistory(Patientptr patient, const char* date, const char* illness, const char* description) {
    RecordPtr newRecord = malloc(sizeof(Record));
    strcpy(newRecord->date, date);
    strcpy(newRecord->ilness, illness);
    strcpy(newRecord->description, description);
    newRecord->next = patient->illnesses;
    patient->illnesses = newRecord;
}

void AddToCheckupHistory(Patientptr patient, const char* date, const char* description) {
    RecordPtr newRecord = malloc(sizeof(Record));
    strcpy(newRecord->date, date);
    strcpy(newRecord->ilness, "Pregled");
    strcpy(newRecord->description, description);
    newRecord->next = patient->checkups;
    patient->checkups = newRecord;
}



