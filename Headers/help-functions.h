#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "patient.h"
#include "doctor.h"
#include "emergency.h"
#include "appointment.h"
#include <stdbool.h>

void PatientDetails(Patientptr patient);
void ListAllPatients(HashTable* ht);
void PrintIllnessHistory(Patientptr patient);
void PrintCheckupHistory(Patientptr patient);

void PrintDoctors(SpecializationNodePtr root);
void ListAllDoctors(SpecializationNodePtr root);
void ListAllSpecializations(SpecializationNodePtr root);
void ListDoctorsBySpecialization(SpecializationNodePtr root, const char* specialization);
void ListAvailableAppointments(DoctorPtr doctor);
void InOrderAppointments(AppointmentNodePtr root, int* count);

void ListAllEmergencyCases(PriorityQueue* pq);

void clearScreen();
void clearBuffer();
void PressAnyKey();
int max(int a, int b);

bool stringIsValid(char* string);
bool isLeapYear(int year);
bool isValidDate(const char* date);
void getDate(char* date);
bool isValidID(char* id);
void getID(char* id);

void InputName(char* name, char* role);
void InputSurname(char* surname, char* role);

#endif