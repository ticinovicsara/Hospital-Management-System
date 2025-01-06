#include "../Headers/emergency.h"
#include "../Headers/help-functions.h"
#include <stdio.h> 
#include <string.h>


void AddEmergencyCase(PriorityQueue* pq, HashTable* ht){
    EmergencyCase newCase;
    ListAllPatients(ht);

    char id[10];
    getNumberInput(id);
    Patientptr patient = SearchPatientByID(ht, id);
    if(!patient){
        clearScreen();
        printf("Pacijent s ID-om '%s' nije nadjen\n", id);
        return;
    }

    strcpy(newCase.patientId, id);

    Input("opis", newCase.description, "hitnog slucaja");

    clearBuffer();

    int priority;
    InputNumberBetween("Unesite prioritet hitnog slucaja (manji broj = veci prioritet)", &priority, 1, 10);
    newCase.priority = priority;

    enqueue(pq, newCase);
    clearScreen();                 
    printf("Hitni slucaj dodan\n");
}