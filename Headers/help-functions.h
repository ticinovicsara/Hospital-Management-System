#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "patient.h"
#include "doctor.h"
#include <stdbool.h>

void ListAllPatients(HashTable* ht);
void ListAllDoctors(SpecializationNodePtr root);
void PrintDoctors(SpecializationNodePtr root);
void PatientDetails(Patientptr patient);

void clearScreen();
void clearBuffer();

bool stringIsValid(char* string);
bool isValidDate(const char* date);
void inputNameAndSurname(char* name, char* surname);
bool isValidID(const char* id);
void getID(char* id);

#endif