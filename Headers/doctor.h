#ifndef DOCTOR_H
#define DOCTOR_H

#include "patient.h"
#include "appointment.h"

typedef struct Node* NodePosition;

typedef struct _doctor{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    AppointmentNodePtr appointments;
    int availableAppointments;
    struct _doctor* next;
    NodePosition patients;
}Doctor;

typedef Doctor* DoctorPtr;

typedef struct _specializationNode{
    char specialization[MAX_NAME_LENGTH];
    DoctorPtr doctors;
    struct _specializationNode* left;
    struct _specializationNode* right;
    int height;
}SpecializationNode;

typedef SpecializationNode* SpecializationNodePtr;

SpecializationNodePtr BalanceTree(SpecializationNodePtr root);
SpecializationNodePtr InsertDoctor(SpecializationNodePtr root, char* specialization, char* name, char* surname, int available_appointments);
SpecializationNodePtr DeleteDoctor(SpecializationNodePtr root, const char* name, const char* surname);
SpecializationNodePtr SearchDoctorBySpecialization(SpecializationNodePtr root, const char* specialization);
SpecializationNodePtr SearchDoctorAndSpecialization(SpecializationNodePtr root, const char* name, const char* surname, DoctorPtr* foundDoctor);
DoctorPtr SearchDoctorByName(SpecializationNodePtr root, const char* name, const char* surname);

void AddDoctor(SpecializationNodePtr* root);
void DeleteDoctorByNameSurname(SpecializationNodePtr root);

#endif