#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/patient.h"

static int hash(const char* surname, int size){
    int hash_value = 0;

    for (int i = 0; surname[i] != '\0'; i++) {
        hash_value = (hash_value * 31 + surname[i]) % size;
    }
    return hash_value;
}

HashTable* CreateHashTable(int size){
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if(!ht){
        printf("Nemoguce alocirati tablicu\n");
        return NULL;
    }
    ht->size = size;
    ht->buckets = (NodePosition*)calloc(size, sizeof(NodePosition));
    if(ht->buckets == NULL){
        printf("greska pri alokaciji bucketa\n");
        free(ht);
        return NULL;
    }
    return ht;
}

void InsertPatient(HashTable* ht, Patientptr patient){
    int index = hash(patient->surname, ht->size);
    
    sprintf(patient->id, "%d", index);

    NodePosition newNode = (NodePosition)malloc(sizeof(Node));
    if(!newNode){
        printf("greska pri alokaciji pacijenta\n");
        return;
    }

    newNode->patient = patient;
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
}

Patientptr SearchPatientBySurname(HashTable* ht, const char* surname){
    int index = hash(surname, ht->size);
    NodePosition current = ht->buckets[index];

    while(current != NULL){
        Patientptr p = current->patient;
        if(strcmp(p->surname, surname) == 0){
            return p;
        }
        current = current->next;
    }

    return NULL;
}

Patientptr SearchPatientByID(HashTable* ht, const char* id){
    for(int i = 0; i < ht->size; i++) {
        NodePosition current = ht->buckets[i];
        while (current != NULL) {
            if (strcmp(current->patient->id, id) == 0) {
                return current->patient;
            }
            current = current->next;
        }
    }
    return NULL; 
}

bool DeletePatient(HashTable* ht, const char* id, const char* surname){
    int index = hash(surname, ht->size);
    printf("hash: %d", index);
    NodePosition current = ht->buckets[index];
    NodePosition prev = NULL;

    while(current != NULL){
        if(strcmp(current->patient->id, id) == 0 && strcmp(current->patient->surname, surname) == 0){
            printf("Found matching patient: %s %s\n", id, surname);
            if(prev == NULL){
                ht->buckets[index] = current->next;
            }
            else{
                prev->next = current->next;
            }

            free(current->patient);
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}


void AddToIllnessHistory(Patientptr patient, const char* date, const char* illness, const char* description) {
    RecordPtr newRecord = malloc(sizeof(MedicalRecord));
    strcpy(newRecord->date, date);
    strcpy(newRecord->ilness, illness);
    strcpy(newRecord->description, description);
    newRecord->next = patient->ilnesses;
    patient->ilnesses = newRecord;
}

void AddToCheckupHistory(Patientptr patient, const char* date, const char* description) {
    RecordPtr newRecord = malloc(sizeof(MedicalRecord));
    strcpy(newRecord->date, date);
    strcpy(newRecord->ilness, "Pregled");
    strcpy(newRecord->description, description);
    newRecord->next = patient->checkups;
    patient->checkups = newRecord;
}