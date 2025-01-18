#ifndef EMERGENCYCASE_H
#define EMERGENCYCASE_H

#define MAX_QUEUE_SIZE 100
#include "patient.h"

typedef struct _emergencyCase{
    char patientId[10];
    char description[100];
    int priority;
}EmergencyCase;

typedef struct _priorityQueue{
    EmergencyCase queue[MAX_QUEUE_SIZE];
    int size;
}PriorityQueue;


void showEmergencyCaseMenu(PriorityQueue* pq, HashTable* ht);
void initializeQueue(PriorityQueue* pq);
void enqueue(PriorityQueue* pq, EmergencyCase newCase);
EmergencyCase dequeue(PriorityQueue* pq);
EmergencyCase peek(PriorityQueue* pq);

void AddEmergencyCase(PriorityQueue* pq, HashTable* ht);

#endif