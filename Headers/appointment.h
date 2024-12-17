#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "patient.h"

struct Appointment {
    int id;
    int patientID;
    char date[MAX_DATE_LENGTH];
    char reason[100];
};

typedef struct _appointmentNode *AppointmentNodePtr;

struct AppointmentNode {
    Appointment appointment;
    AppointmentNodePtr left;
    AppointmentNodePtr right;
    int height;
};

bool isAppointmentAvailable(AppointmentNodePtr root, const char* date);
AppointmentNodePtr InsertAppointment(AppointmentNodePtr root, const char* date, int patientID);

#endif