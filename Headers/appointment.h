#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "patient.h"

typedef struct{
    int id;
    int patientID;
    char date[MAX_DATE_LENGTH];
    char reason[100];
}Appointment;


typedef struct AppointmentNode* AppointmentNodePtr; 
typedef struct AppointmentNode {
    Appointment appointment;
    AppointmentNode* left;
    AppointmentNode* right;
    int height;
} AppointmentNode;


AppointmentNodePtr BalanceAppointmentTree(AppointmentNodePtr root);
bool isAppointmentAvailable(AppointmentNodePtr root, const char* date);
AppointmentNodePtr InsertAppointment(AppointmentNodePtr root, const char* date, int patientID);

#endif