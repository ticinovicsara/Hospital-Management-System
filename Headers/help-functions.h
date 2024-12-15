#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "patient.h"
#include "doctor.h"

void ListAllPatients(HashTable* ht);
void ListAllDoctors(SpecializationNodePtr root);
void PrintDoctors(SpecializationNodePtr root);

#endif