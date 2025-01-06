#ifndef MENUS_H
#define MENUS_H

#include "patient.h"
#include "doctor.h"
#include "emergency.h"

void showPatientMenu(HashTable* ht, SpecializationNodePtr root);
void showDoctorMenu(SpecializationNodePtr root);
void ReadDoctors(SpecializationNodePtr *root);
void ReadEmergencyCases(PriorityQueue* pq);

#endif
