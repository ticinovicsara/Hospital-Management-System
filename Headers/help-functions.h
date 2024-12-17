#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "patient.h"
#include "doctor.h"
#include <stdbool.h>

void ListAllPatients(HashTable* ht);
void ListAllDoctors(SpecializationNodePtr root);
void PrintDoctors(SpecializationNodePtr root);
void PatientDetails(Patientptr patient);
void ListAllSpecializations(SpecializationNodePtr root);
void ListDoctorsBySpecialization(SpecializationNodePtr root, const char* specialization);
void ListAvailableAppointments(Doctor doctor);

void clearScreen();
void clearBuffer();

bool stringIsValid(char* string);
void InputName(char* name, char* role)
void InputSurname(char* surname, char* role);
void getDate(char* date);
void getID(char* id);

#endif