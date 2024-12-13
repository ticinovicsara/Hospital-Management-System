#include "../Headers/read_files.h"
#include "../Headers/patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void ReadPatients(HashTable* ht){
    FILE* fp = fopen("Seed/patients.txt", "r");
    if(!fp){
        printf("Datoteka 'patients.txt' se ne moze otvoriti\n");
        return;
    }

    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, fp)){
        Patientptr newPatient = (Patientptr)malloc(sizeof(Patient));
        if (!newPatient) {
            printf("Greska pri alokaciji memorije za pacijenta\n");
            continue;
        }

        newPatient->history = NULL; 

        if (sscanf(buffer, "%49[^,],%49[^,],%14[^,]", newPatient->name, newPatient->surname, newPatient->birthDate) != 3) {
            printf("Greska pri parsiranju podataka pacijenta\n");
            free(newPatient);
            continue;
        }

        char* records_start = buffer + strlen(newPatient->name) + strlen(newPatient->surname) + strlen(newPatient->birthDate) + 3;
        char* record_token = strtok(records_start, ";");

         while (record_token != NULL) {
            RecordPtr newRecord = (RecordPtr)malloc(sizeof(MedicalRecord));
            if (!newRecord) {
                printf("Greska pri alokaciji memorije za medicinski zapis\n");
                break;
            }

            char illness[MAX_ILLNESS_LENGTH] = "";
            char date[MAX_DATE_LENGTH] = "";
            char description[MAX_DESCRIPTION_LENGTH] = "";

            if (sscanf(record_token, "%49[^,],%10[^,],%199[^,]", illness, date, description) == 3) {
                strncpy(newRecord->ilness, illness, MAX_ILLNESS_LENGTH - 1);
                strncpy(newRecord->date, date, MAX_DATE_LENGTH - 1);
                strncpy(newRecord->description, description, MAX_DESCRIPTION_LENGTH - 1);

                newRecord->next = newPatient->history;
                newPatient->history = newRecord;

            } else {
                printf("Greska pri parsiranju medicinskog zapisa: %s\n", record_token);
                free(newRecord);
            }

            record_token = strtok(NULL, ";");
        }
        InsertPatient(ht, newPatient);
    }
    fclose(fp);
}
