#ifndef PATIENT_H
#define PATIENT_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define MAX_ILLNESS_LENGTH 50
#define MAX_DATE_LENGTH 11
#define MAX_DESCRIPTION_LENGTH 200

typedef struct _medicalRecord* RecordPtr;
typedef struct _medicalRecord{
    char date[15];
    char ilness[MAX_NAME_LENGTH];
    char description[200];
    RecordPtr next;
}MedicalRecord;

typedef struct _patient* Patientptr;
typedef struct _patient{
    char id[10];
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char birthDate[15];
    RecordPtr history;
}Patient;

typedef struct _node* NodePosition;
typedef struct _node{
    Patientptr patient;
    NodePosition next;
}Node;

typedef struct HashTable{
    int size;
    NodePosition* buckets;
}HashTable;

HashTable* CreateHashTable(int size);
void InsertPatient(HashTable* ht, Patientptr patient);
Patientptr SearchPatientByID(HashTable* ht, const char* id);
bool DeletePatient(HashTable* ht, const char* id, const char* surname);
void ListAllPatients(HashTable* ht);
Patientptr SearchPatientBySurname(HashTable* ht, const char* surname);
void DeletePatientByIDSurname(HashTable* ht);
void AddPatient(HashTable ht);

#endif