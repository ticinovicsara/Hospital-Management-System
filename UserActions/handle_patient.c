#include "../Headers/patient.h"
#include <stdlib.h>
#include <stdio.h>

void clearScreen() {
    system("cls");
}


void AddPatient(HashTable ht){
    clearScreen();
    printf("\nUnesite podatke za novog pacijenta:\n");

    Patientptr newPatient = (Patientptr)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Greska pri alokaciji memorije za pacijenta\n");
        return NULL;
    }

    do {
        printf("\nUnesite ime pacijenta: ");
        scanf("%49s", newPatient->name);

        if (!stringIsValid(newPatient->name)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(newPatient->name));

    do {
        printf("\nUnesite prezime pacijenta: ");
        scanf("%49s", newPatient->surname);

        if (!stringIsValid(newPatient->surname)) {
            printf("Neispravan unos, pokusajte ponovo.\n");
        }
    } while (!stringIsValid(newPatient->surname));

    do {
        printf("\nUnesite datum rodjenja pacijenta u formatu (DD.MM.YYYY): ");
        scanf("%14s", newPatient->birthDate);

        if (!isValidDate(newPatient->birthDate)) {
            printf("Datum nije valjan, pokusajte ponovo.\n");
        }
    } while (!isValidDate(newPatient->birthDate));

    newPatient->history = NULL;

    InsertPatient(ht, newPatient);

    printf("Pacijent uspjesno kreiran.\n");
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