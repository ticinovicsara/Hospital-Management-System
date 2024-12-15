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

void clearScreen() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

bool stringIsValid(char* string){
    for (int i = 0; i < strlen(string); i++) {
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


// void ListAllEmergencyCases(PriorityQueue pq){

// }