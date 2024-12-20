#ifndef DOCTOR_H
#define DOCTOR_H

#include "patient.h"
#include "appointment.h"

typedef struct _doctor* DoctorPtr;
typedef struct _doctor{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    AppointmentNodePtr appointments;
    int availableAppointments;
    DoctorPtr next;
}Doctor;

typedef struct _specializationNode* SpecializationNodePtr;
typedef struct _specializationNode{
    char specialization[MAX_NAME_LENGTH];
    DoctorPtr doctors;
    SpecializationNodePtr left;
    SpecializationNodePtr right;
    int height;
}SpecializationNode;


SpecializationNodePtr BalanceTree(SpecializationNodePtr root);
SpecializationNodePtr InsertDoctor(SpecializationNodePtr root, char* specialization, char* name, char* surname, int available_appointments);
SpecializationNodePtr DeleteDoctor(SpecializationNodePtr root, const char* name, const char* surname);
SpecializationNodePtr SearchDoctorBySpecialization(SpecializationNodePtr root, const char* specialization);
DoctorPtr SearchDoctorByName(SpecializationNodePtr root, const char* name, const char* surname);

#endif