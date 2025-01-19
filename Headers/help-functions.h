#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

typedef struct _patient* Patientptr;
typedef struct HashTable HashTable;
typedef struct _doctor* DoctorPtr;
typedef struct _specializationNode* SpecializationNodePtr;
typedef struct AppointmentNode* AppointmentNodePtr;
typedef struct _priorityQueue PriorityQueue;

#include <stdbool.h>

void PatientDetails(Patientptr patient);
void ListAllPatients(HashTable* ht);
void PrintIllnessHistory(Patientptr patient);
void PrintCheckupHistory(Patientptr patient);

void PrintDoctors(SpecializationNodePtr root);
void PrintSpecializations(SpecializationNodePtr root);
bool ListDoctorsBySpecialization(SpecializationNodePtr root, const char* specialization);
void ListAvailableAppointments(DoctorPtr doctor);
void InOrderAppointments(AppointmentNodePtr root, int* count);

void ListAllEmergencyCases(PriorityQueue* pq);

void clearScreen();
void clearBuffer();
void PressAnyKey();
int max(int a, int b);

bool stringIsValid(char* string);
void capitalizeName(char *str);

bool isLeapYear(int year);
bool isValidDate(const char* date);
void getDate(char* date);
bool isValidID(char* id);
void getID(char* id);
void getNumberInput(char* input);

void Input(char* message, char* input, char* role);
void InputReason(char* message, char* input, char* role);
void InputNumberBetween(char* message, int* priority, int min, int max);

void FreeAllResources(HashTable* ht, SpecializationNodePtr root);
#endif