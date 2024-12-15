#include "../Headers/emergency.h"

void initializeQueue(PriorityQueue* pq) {
    pq->size = 0;
}

void upheap(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->queue[index].priority >= pq->queue[parent].priority) {
            break;
        }

        EmergencyCase temp = pq->queue[index];
        pq->queue[index] = pq->queue[parent];
        pq->queue[parent] = temp;

        index = parent;
    }
}

void enqueue(PriorityQueue* pq, EmergencyCase newCase) {
    if (pq->size >= MAX_QUEUE_SIZE) {
        printf("Red je pun!\n");
        return;
    }

    pq->queue[pq->size] = newCase;
    upheap(pq, pq->size);
    pq->size++;
}

void downheap(PriorityQueue* pq, int index) {
    int leftChild, rightChild, smallest;

    while (2 * index + 1 < pq->size) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        smallest = index;

        if (leftChild < pq->size && pq->queue[leftChild].priority < pq->queue[smallest].priority) {
            smallest = leftChild;
        }
        if (rightChild < pq->size && pq->queue[rightChild].priority < pq->queue[smallest].priority) {
            smallest = rightChild;
        }
        if (smallest == index) {
            break;
        }

        EmergencyCase temp = pq->queue[index];
        pq->queue[index] = pq->queue[smallest];
        pq->queue[smallest] = temp;

        index = smallest;
    }
}

EmergencyCase dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Red je prazan!\n");
        EmergencyCase empty = {0};
        return empty;
    }

    EmergencyCase highestPriorityCase = pq->queue[0];

    pq->queue[0] = pq->queue[pq->size - 1];
    pq->size--;
    
    downheap(pq, 0);

    return highestPriorityCase;
}

EmergencyCase peek(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Red je prazan!\n");
        EmergencyCase empty = {0};
        return empty;
    }
    return pq->queue[0];
}

