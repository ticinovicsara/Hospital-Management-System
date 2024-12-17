#ifndef APPOINTMENT_H
#define APPOINTMENT_H

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


bool isAppointmentAvailable(AppointmentNodePtr root, const char* date);
AppointmentNodePtr InsertAppointment(AppointmentNodePtr root, const char* date, int patientID);

#endif