#include "../Headers/appointment.h"
#include "../Headers/patient.h"
#include "../Headers/doctor.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int getHeight(AppointmentNodePtr node);
int getBalance(AppointmentNodePtr node);
AppointmentNodePtr rotate(AppointmentNodePtr root, int direction);

int max(int a, int b) {
    return (a > b) ? a : b;
}

bool isAppointmentAvailable(AppointmentNodePtr root, const char* date) {
    if (root == NULL) {
        return true;
    }
    int cmp = strcmp(date, root->appointment.date);
    if (cmp < 0) {
        return isAppointmentAvailable(root->left, date);
    }
    else if (cmp > 0) {
        return isAppointmentAvailable(root->right, date);
    }
    else {
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
    }
    else if (cmp > 0) {
        root->right = InsertAppointment(root->right, date, patientID);
    }
    else{
        return root;
    }
    return BalanceAppointmentTree(root);
}

AppointmentNodePtr BalanceAppointmentTree(AppointmentNodePtr root) {
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) < 0) {
            root->left = rotate(root->left, 1);
        }
        return rotate(root, 0);
    }

    if (balance < -1) {
        if (getBalance(root->right) > 0) {
            root->right = rotate(root->right, 0);
        }
        return rotate(root, 1);
    }

    return root;
}

int getHeight(AppointmentNodePtr node) {
    return node ? node->height : 0;
}

int getBalance(AppointmentNodePtr node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AppointmentNodePtr rotate(AppointmentNodePtr root, int direction) {
    AppointmentNodePtr newRoot;
    if (direction == 0) {
        newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
    } else {
        newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}
