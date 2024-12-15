#ifndef READ_FILES_H
#define READ_FILES_H

#include "patient.h"
#include "doctor.h"
#include "emergency.h"

void ReadPatients(HashTable* ht);
void ReadDoctors(SpecializationNodePtr *root);
void ReadEmergencyCases(PriorityQueue* pq);

#endif
