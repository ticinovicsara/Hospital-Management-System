#ifndef EMERGENCYCASE_H
#define EMERGENCYCASE_H

#define MAX_QUEUE_SIZE 100

typedef struct _emergencyCase{
    int id;
    char description[100];
    int priority;
}EmergencyCase;

typedef struct {
    EmergencyCase queue[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue;


void showEmergencyCaseMenu(PriorityQueue* pq);
void initializeQueue(PriorityQueue* pq);
void upheap(PriorityQueue* pq, int index);
void enqueue(PriorityQueue* pq, EmergencyCase newCase);
void downheap(PriorityQueue* pq, int index);
EmergencyCase dequeue(PriorityQueue* pq);
EmergencyCase peek(PriorityQueue* pq);

#endif