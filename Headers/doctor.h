#ifndef DOCTOR_H
#define DOCTOR_H
#include <patient.h>
#include <appointment.h>

typedef struct _doctor* DoctorPtr;
typedef struct _doctor{
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char specialization[MAX_NAME_LENGTH];
    AppointmentNodePtr appointments;
    int availableAppointments;
    DoctorPtr next;
}Doctor;

typedef struct _specializationNode* SpecializationNodePtr;
typedef struct _specializationNode{
    Doctor doctor;
    SpecializationNodePtr left;
    SpecializationNodePtr right;
    int height;
}SpecializationNode;




#endif