#include "../Headers/patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hash(const char* fname, const char* lname, int size){
    int hash_value = 0;

    char full_name [MAX_NAME_LENGTH * 2 + 1] = "";
    strcat(full_name, fname);
    strcat(full_name, lname);

    for(int i=0; full_name[i] != '\0'; i++){
        hash_value = (hash_value * 31 + full_name[i]) % size;
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
    int index = hash(patient->name, patient->surname, ht->size);
    
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

void SearchPatientByName(HashTable* ht, char* name, char* surname){
    int index = hash(name, surname, ht->size);
    NodePosition current = ht->buckets[index];

    while(current != NULL){
        Patientptr p = current->patient;
        if(strcmp(p->name, name) == 0 && strcmp(p->surname, surname) == 0){
            printf("\nPacijent: %s %s", p->name, p->surname);
            printf("\tID: %-10s\tIme: %-20s %-20s\tDatum Rodjenja: %-12s\n", p->id, p->name, p->surname, p->birthDate);
            return;
        }
        current = current->next;
    }

    printf("Pacijent nije nadjen\n");
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

void DeletePatient(HashTable* ht, const char* id, const char* surname){
    int index = hash(id, "", ht->size);
    NodePosition current = ht->buckets[index];
    NodePosition prev = NULL;

    while(current != NULL){
        if(strcmp(current->patient->id, id) == 0 && strcmp(current->patient->surname, surname) == 0){
            if(prev == NULL){
                ht->buckets[index] = current->next;
            }
            else{
                prev->next = current->next;
            }

            free(current->patient);
            free(current);
            printf("Pacijent sa ID %s i prezimenom %s je obrisan.\n", id, surname);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Pacijent sa ID %s nije pronadjen.\n", id);
}
