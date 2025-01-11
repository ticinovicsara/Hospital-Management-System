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

static void ListAllSpecializations(SpecializationNodePtr root);

void clearScreen(){
    system("clear");
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

void PressAnyKey(){
    clearBuffer();
    printf("\nPristisnite bilo sto za nastavak...\n\n");
    getchar();
}


bool stringIsValid(char* string){
    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            return false;
        }
    }
    return true;
}

void capitalizeName(char *str){
    if (str[0] != '\0') {
        str[0] = toupper(str[0]);
        for (int i = 1; str[i] != '\0'; i++) {
            str[i] = tolower(str[i]);
        }
    }
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
    printf("------------------------------------------------------------------\n");
    RecordPtr temp = patient->ilnesses;
    if (temp == NULL) {
        printf("\nNema podataka o bolesti\n");
    } else {
        while (temp != NULL) {
            printf("%-20s %-15s %-30s\n", temp->ilness, temp->date, temp->description);
            temp = temp->next;
        }
    }

    printf("\n\n------------------------ POVIJEST PREGLEDA -----------------------\n");
    printf("%-20s %-15s %-30s\n", "Vrsta pregleda", "Datum", "Opis");
    printf("------------------------------------------------------------------\n");

    RecordPtr checkupTemp = patient->checkups;
    if (checkupTemp == NULL) {
        printf("\nNema podataka o pregledima\n");
    } else {
        while (checkupTemp != NULL) {
            printf("%-20s %-15s %-30s\n", checkupTemp->ilness, checkupTemp->date, checkupTemp->description);
            checkupTemp = checkupTemp->next;
        }
    }
    printf("\n------------------------------------------------------------------\n");
    PressAnyKey();
    clearScreen();
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
    PressAnyKey();
    clearScreen();
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

void Input(char* message, char* input, char* role){
    do {
        printf("\nUnesite %s %s: ", message, role);
        scanf("%s", input);

        if (!stringIsValid(input)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(input));
}

void InputNumberBetween(char* message, int* priority, int min, int max) {
    int valid = 0;
    char buffer[100];

    do {
        printf("\n%s (%d - %d): ", message, min, max);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (sscanf(buffer, "%d", priority) == 1 && *priority >= min && *priority <= max) {
                valid = 1;
            } else {
                printf("\nNeispravan unos, unesite broj u opsegu od %d do %d.\n", min, max);
            }
        } else {
            clearScreen();
            printf("Neispravan, pokusajte ponovo.\n");
        }
    } while (!valid);
}

void getNumberInput(char* input) {
    int validInput = 0;

    do {
        printf("Unesite broj: ");
        fgets(input, 10, stdin);

        input[strcspn(input, "\n")] = '\0';

        validInput = 1;
        for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
            if (!isdigit(input[i])) {
                validInput = 0;
                break;
            }
        }

        if (!validInput) {
            printf("Unos nije broj, pokusajte ponovo.\n\n");
        }
    } while (!validInput);
}


static void ListAllSpecializations(SpecializationNodePtr root) {
    if (root == NULL) {
        return;
    }

    ListAllSpecializations(root->left);

    printf("-> %s\n", root->specialization);

    ListAllSpecializations(root->right);
}

void PrintSpecializations(SpecializationNodePtr root) {
    printf("\n\n--- Trenutne specijalizacije ---\n");
    ListAllSpecializations(root);
    printf("---------------------------------\n");
}

bool ListDoctorsBySpecialization(SpecializationNodePtr root, const char* specialization){
    SpecializationNodePtr result = SearchDoctorBySpecialization(root, specialization);
    if (result == NULL) {
        printf("Nema doktora za specijalizaciju '%s'\n", specialization);
        return false;
    }

    printf("\nDoktori u specijalizaciji:\n\n");

    printf("\n---------------------\n");
    printf("    %s", specialization);
    printf("\n---------------------\n");

    DoctorPtr doctor = result->doctors;
    if (doctor == NULL) {
        return false;
    } 
    else {
        while (doctor != NULL) {
            printf("\n -> %s %s\n", doctor->name , doctor->surname);
            doctor = doctor->next;
        }
    }
    printf("\n---------------------\n");

    return true;
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

    printf("\nHitni slucajevi u redu:\n");
    printf("     -----------------------------------------------------------------\n");
    printf("     \tPRIORITET\tID PACIJENTA\t\tOPIS\n");
    printf("     -----------------------------------------------------------------\n");

    for (int i = 0; i < pq->size; i++) {
        printf("\t%-10d\t%-15s\t\t%-20s\n", 
               pq->queue[i].priority, 
               pq->queue[i].patientId, 
               pq->queue[i].description);
    }

    printf("     -----------------------------------------------------------------\n\n");
    PressAnyKey();
    clearScreen();
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

