#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <patient.h>

typedef struct _appointment{
    int id;
    int patientID;
    char date[MAX_DATE_LENGTH];
    char reason[100];
}Appointment;

typedef struct _appointment* AppointmentNodePtr;
typedef struct _appointmentNode{
    Appointment appointment;
    AppointmentNodePtr left;
    AppointmentNodePtr right;
    int height;
}AppointmentNode;


#endif