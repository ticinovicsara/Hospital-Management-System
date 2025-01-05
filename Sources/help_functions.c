#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

#include "../Headers/patient.h"
#include "../Headers/doctor.h"
#include "../Headers/help-functions.h"
#include "../Headers/emergency.h"

void clearScreen(){
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


bool stringIsValid(char* string){
    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            return false;
        }
    }
    return true;
}


bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const char* date) {
    if (strlen(date) != 10 || date[2] != '.' || date[5] != '.') {
        return false;
    }

    int day, month, year;

    if (sscanf(date, "%2d.%2d.%4d", &day, &month, &year) != 3) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}

void getDate(char* date){
    while (1) {
        printf("\nUnesite datum u formatu (DD.MM.YYYY): ");
        scanf("%s", date);

        if (isValidDate(date)) {
            break;
        } else {
            printf("Datum nije valjan, pokusajte ponovo.\n");
        }
    }
}

bool isValidID(char* id) {
    int lenght = strlen(id);
    if (lenght == 0) {
        return false;
    }

    for (int i = 0; i < lenght; i++) {
        if (!isdigit(id[i])) {
            return false;
        }
    }

    return true;
}

void getID(char* id) {
    while (1) {
        printf("\nUnesite ID: ");
        
        if (scanf("%s", id) != 1) {
            while (getchar() != '\n');
            printf("Neispravan unos, pokusajte ponovo.\n");
            continue;
        }

        if (isValidID(id)) {
            break;
        } else {
            printf("Neispravan ID, unesite ponovno\n");
        }
        while (getchar() != '\n');
    }
}

void PatientDetails(Patientptr patient){
    clearScreen();
    printf("\n---------------------------- PACIJENT ----------------------------\n");
    printf("Ime i prezime:\t\t%s %s\n", patient->name, patient->surname);
    printf("ID:\t\t\t%s\n", patient->id);
    printf("Datum rođenja:\t\t%s\n", patient->birthDate);
    printf("\n\n------------------------ POVIJEST BOLESTI ------------------------\n");
    printf("%-20s %-15s %-30s\n", "Bolest", "Datum", "Opis");
    printf("---------------------------------------------------------------\n");
    RecordPtr temp = patient->ilnesses;
    if (temp == NULL) {
        printf("\nNema podataka o bolesti\n");
    } else {
        while (temp != NULL) {
            printf("%-20s %-15s %-30s\n", temp->ilness, temp->date, temp->description);
            temp = temp->next;
        }
    }

    printf("\n------------------------ POVIJEST PREGLEDA ----------------------\n");
    printf("%-20s %-15s %-30s\n", "Vrsta pregleda", "Datum", "Opis");
    printf("---------------------------------------------------------------\n");

    RecordPtr checkupTemp = patient->checkups;
    if (checkupTemp == NULL) {
        printf("\nNema podataka o pregledima\n");
    } else {
        while (checkupTemp != NULL) {
            printf("%-20s %-15s %-30s\n", checkupTemp->ilness, checkupTemp->date, checkupTemp->description);
            checkupTemp = checkupTemp->next;
        }
    }
    printf("\n---------------------------------------------------------------\n");
    printf("\nPristisnite bilo sto za nastavak...");
    getchar();
    getchar();
    return;
}

void ListAllPatients(HashTable* ht) {
    printf("\nSvi pacijenti: \n");
    printf("     --------------------------------------------------------------\n");
    printf("\tID\tIME\t   PREZIME\t\tDATUM RODJENJA\n");
    printf("     --------------------------------------------------------------\n");

    for(int i = 0; i < ht->size; i++) {
        NodePosition current = ht->buckets[i];

        while(current != NULL) {
            Patientptr p = current->patient;
            printf("\t%-5s\t%-10s %-10s\t\t%-12s\n", p->id, p->name, p->surname, p->birthDate);
            current = current->next;
        }
    }

    printf("\n\n");
}


void PrintDoctors(SpecializationNodePtr root) {
    printf("Svi doktori:\n");
    printf("     --------------------------------------------------------------------------\n");
    printf("\tSPECIJALIZACIJA\t\tIME\t    PREZIME\t    DOSTUPNI TERMINI\n");
    printf("     --------------------------------------------------------------------------\n");


    ListAllDoctors(root);
    printf("\n\n");
}

void ListAllDoctors(SpecializationNodePtr root){
    if(root == NULL){
        return;
    }
    DoctorPtr currDoctor = root->doctors;
    if (currDoctor == NULL) {
        printf("\tNema doktora u ovoj specijalizaciji.\n");
    }
    else {
        while (currDoctor != NULL) {
            printf("\t%-23s %-11s %-15s %-5d\n", root->specialization, currDoctor->name, currDoctor->surname, currDoctor->availableAppointments);
            currDoctor = currDoctor->next;
        }
    }

    ListAllDoctors(root->left);
    ListAllDoctors(root->right);
}

void InputName(char* name, char* role){
    do {
        printf("\nUnesite ime %s: ", role);
        scanf("%s", name);

        if (!stringIsValid(name)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(name));
}
void InputSurname(char* surname, char* role) {
    do {
        printf("\nUnesite prezime %s: ", role);
        scanf("%s", surname);

        if (!stringIsValid(surname)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(surname));
}


void ListAllSpecializations(SpecializationNodePtr root){
    printf("Dostupne specijalizacije: \n\n");

    if(root == NULL){
        return;
    }

    ListAllSpecializations(root->left);

    printf("%s\n", root->specialization);
    
    ListAllSpecializations(root->right);
}

void ListDoctorsBySpecialization(SpecializationNodePtr root, const char* specialization){
    printf("Dostupni doktori u specijalizaciji '%s':\n", specialization);
    
    SpecializationNodePtr result = SearchDoctorBySpecialization(root, specialization);
    if (result == NULL) {
        printf("Specijalizacija '%s' nije pronadjena.\n\n", specialization);
        return;
    }

    DoctorPtr doctor = root->doctors;
    if (doctor == NULL) {
        printf("Nema doktora za specijalizaciju '%s'\n\n", specialization);
    } 
    else {
        while (doctor != NULL) {
            printf("\t%s %s\n", doctor->name, doctor->surname);
            doctor = doctor->next;
        }
    }
}

void ListAvailableAppointments(DoctorPtr doctor){
    printf("Dostupni termini doktora: %s %s\n\n", doctor->name, doctor->surname);

    if (doctor == NULL) {
        printf("Nema informacija o doktoru\n");
        return;
    }

    if (doctor->appointments == NULL) {
        printf("Trenutno nema zakazanih termina\n");
        return;
    }

    int scheduledCount = 0;
    InOrderAppointments(doctor->appointments, &scheduledCount);

    int freeAppointments = doctor->availableAppointments - scheduledCount;

    if (freeAppointments > 0) {
        printf("\nBroj slobodnih termina: %d\n", freeAppointments);
    } else {
        printf("\nNema slobodnih termina.\n");
    }
}

void InOrderAppointments(AppointmentNodePtr root, int* count) {
    if (root == NULL) {
        return;
    }

    InOrderAppointments(root->left, count);

    printf("\tDatum: %s, Razlog: %s\n", root->appointment.date, root->appointment.reason);
    (*count)++;

    InOrderAppointments(root->right, count);
}

void ListAllEmergencyCases(PriorityQueue* pq){
    if (pq->size == 0) {
        printf("Nema hitnih slucajeva u redu.\n");
        return;
    }

    printf("Hitni slucajevi u redu:\n");
    for (int i = 0; i < pq->size; i++) {
        printf("ID: %d, Opis: %s, Prioritet: %d\n", pq->queue[i].id, pq->queue[i].description, pq->queue[i].priority);
    }
}

void PrintIllnessHistory(Patientptr patient) {
    printf("\n--- Povijest bolesti ---\n");
    RecordPtr temp = patient->ilnesses;
    if (temp == NULL) {
        printf("Nema podataka o bolestima.\n");
    } else {
        while (temp != NULL) {
            printf("Datum: %-15s | Bolest: %-20s | Opis: %-30s\n", temp->date, temp->ilness, temp->description);
            temp = temp->next;
        }
    }
}

void PrintCheckupHistory(Patientptr patient) {
    printf("\n--- Povijest pregleda ---\n");
    RecordPtr temp = patient->checkups;
    if (temp == NULL) {
        printf("Nema podataka o pregledima.\n");
    } else {
        while (temp != NULL) {
            printf("Datum: %-15s | Vrsta: %-20s | Opis: %-30s\n", temp->date, temp->ilness, temp->description);
            temp = temp->next;
        }
    }
}

