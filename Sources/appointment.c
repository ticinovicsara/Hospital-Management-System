#include "../Headers/patient.h"
#include "../Headers/doctor.h"
#include "../Headers/appointment.h"


bool isAppointmentAvailable(AppointmentNodePtr root, const char* date) {
    if (root == NULL) {
        return true;
    }
    int cmp = strcmp(date, root->appointment.date);
    if (cmp < 0) {
        return isAppointmentAvailable(root->left, date);
    } else if (cmp > 0) {
        return isAppointmentAvailable(root->right, date);
    } else {
        return false;
    }
}

AppointmentNodePtr InsertAppointment(AppointmentNodePtr root, const char* date, int patientID){
    if (root == NULL) {
        AppointmentNodePtr newNode = malloc(sizeof(AppointmentNode));
        newNode->appointment.id = patientID;
        strcpy(newNode->appointment.date, date);
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    int cmp = strcmp(date, root->appointment.date);
    if (cmp < 0) {
        root->left = InsertAppointment(root->left, date, patientID);
    } else if (cmp > 0) {
        root->right = InsertAppointment(root->right, date, patientID);
    }
    return BalanceTree(root);
}




