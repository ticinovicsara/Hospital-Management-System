#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "patient.h"

typedef struct{
    char* patientID;
    char date[MAX_DATE_LENGTH];
    char reason[100];
}Appointment;

typedef struct AppointmentNode {
    Appointment appointment;
    struct AppointmentNode* left;
    struct AppointmentNode* right;
    int height;
} AppointmentNode;

typedef AppointmentNode* AppointmentNodePtr;

AppointmentNodePtr BalanceAppointmentTree(AppointmentNodePtr root);
bool isAppointmentAvailable(AppointmentNodePtr root, const char* date);
AppointmentNodePtr InsertAppointment(AppointmentNodePtr root, const char* date, char* patientID, char* reason);

#endif