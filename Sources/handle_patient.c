#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Headers/doctor.h"
#include "../Headers/patient.h"
#include "../Headers/appointment.h"
#include "../Headers/help-functions.h"

void AddPatient(HashTable ht){
    printf("\nUnesite podatke za novog pacijenta:\n");

    Patientptr newPatient = (Patientptr)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Greska pri alokaciji memorije za pacijenta\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];

    Input("ime", name, "pacijenta");
    Input("prezime", surname, "pacijenta");

    capitalizeName(name);
    capitalizeName(surname);

    strcpy(newPatient->name, name);
    strcpy(newPatient->surname, surname);

    char birth[MAX_DATE_LENGTH];
    getDate(birth);
    strcpy(newPatient->birthDate, birth);

    newPatient->ilnesses = NULL;
    newPatient->checkups = NULL;

    InsertPatient(&ht, newPatient);

    clearScreen();
    getchar();
    printf("Pacijent uspjesno kreiran\n\n");
    return;
}


void DeletePatientByIDSurname(HashTable* ht) {
    printf("Brisanje pacijenta po ID-u i prezimenu:\n");

    char id[10];
    char surname[MAX_NAME_LENGTH];

    getID(id);
    
    Input("prezime", surname, "pacijenta");
    capitalizeName(surname);

    if(!DeletePatient(ht, id, surname)){
        clearScreen();
        printf("\nPacijent sa navedenim ID-om i prezimenom ne postoji\n\n");
        return;
    }
    clearScreen();
    printf("Pacijent sa ID '%s' i prezimenom '%s' je obrisan.\n", id, surname);
    printf("\n");
}


void ReserveAnAppointment(HashTable ht, SpecializationNodePtr root){
    printf("--- Rezerviranje termina kod doktora ---");

    char specialization[MAX_NAME_LENGTH];
    char doctorName[MAX_NAME_LENGTH];
    char doctorSurname[MAX_NAME_LENGTH];
    char appointment[MAX_DATE_LENGTH];

    PrintSpecializations(root);
    printf("\n\nUnesite specijalizaciju: ");
    fgets(specialization, MAX_NAME_LENGTH, stdin);
    specialization[strcspn(specialization, "\n")] = '\0';
    capitalizeName(specialization);

    if(!ListDoctorsBySpecialization(root, specialization)){
        clearScreen();
        printf("Nema doktora za specijalizaciju '%s'\n", specialization);
        return;
    }
    Input("ime", doctorName, "doktora");
    Input("prezime", doctorSurname, "doktora");

    capitalizeName(doctorName);
    capitalizeName(doctorSurname);

    DoctorPtr doctor = SearchDoctorByName(root, doctorName, doctorSurname);
    if(!doctor){
        clearScreen();
        getchar();
        printf("Doktor nije pronadjen\n\n");
        return;
    }

    printf("\n\nOdaberite termin: ");
    ListAvailableAppointments(doctor);
    getDate(appointment);
    getchar();

    if (!isAppointmentAvailable(doctor->appointments, appointment)) {
        clearScreen();
        printf("Termin %s nije dostupan, pokusajte ponovo.\n", appointment);
        return;
    }

    printf("\nUnesite ID pacijenta: ");
    ListAllPatients(&ht);
    char patientID[10];
    getID(patientID);
    Patientptr patient = SearchPatientByID(&ht, patientID);
    getchar();
    if (!patient) {
        printf("Pacijent nije pronadjen.\n");
        return;
    }

    char reason[50];
    InputReason("razlog", reason, "termina");

    doctor->appointments = InsertAppointment(doctor->appointments, appointment, patient->id, reason);
    doctor->availableAppointments--;

    AddPatientToDoctor(doctor, patient);
    
    AddToCheckupHistory(patient, appointment, reason);

    clearScreen();
    printf("Termin %s je uspjesno rezerviran za pacijenta '%s %s' kod doktora '%s %s'.\n", appointment, patient->name, patient->surname, doctor->name, doctor->surname);
}