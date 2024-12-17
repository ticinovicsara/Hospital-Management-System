#include "../Headers/doctor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

SpecializationNodePtr balanceSpecializationNode(SpecializationNodePtr root);
SpecializationNodePtr rightRotation(SpecializationNodePtr root);
SpecializationNodePtr leftRotation(SpecializationNodePtr root);
int max(int a, int b);
int getHeight(SpecializationNodePtr node);
int getBalance(SpecializationNodePtr node);

SpecializationNodePtr InsertDoctor(SpecializationNodePtr root, char* specialization, char* name, char* surname, int available_appointments){
    if(!root){
        SpecializationNodePtr node = (SpecializationNodePtr)malloc(sizeof(SpecializationNode));
        if(!node){
            return NULL;
        }
        
        strcpy(node->specialization, specialization);
        node->doctors = NULL;
        node->left = node->right = NULL;
        node->height = 1;

        DoctorPtr newDoctor = (DoctorPtr)malloc(sizeof(Doctor));
        if (!newDoctor) {
            free(node);
            return NULL;
        }

        strncpy(newDoctor->name, name, MAX_NAME_LENGTH);
        newDoctor->name[MAX_NAME_LENGTH - 1] = '\0';
        strncpy(newDoctor->surname, surname, MAX_NAME_LENGTH);
        newDoctor->surname[MAX_NAME_LENGTH - 1] = '\0';
        newDoctor->appointments = NULL;
        newDoctor->availableAppointments = available_appointments;
        newDoctor->next = NULL;

        node->doctors = newDoctor;
        return node;
    }

    if (specialization == NULL || name == NULL || surname == NULL) {
        return NULL;
    }


    if (strcmp(specialization, root->specialization) < 0) {
        root->left = InsertDoctor(root->left, specialization, name, surname, available_appointments);
    }
    else if (strcmp(specialization, root->specialization) > 0) {
        root->right = InsertDoctor(root->right, specialization, name, surname, available_appointments);
    }
    else {
        DoctorPtr newDoctor = (DoctorPtr)malloc(sizeof(Doctor));
        if(!newDoctor){
            return root;
        }

        strcpy(newDoctor->name, name);
        strcpy(newDoctor->surname, surname);
        newDoctor->appointments = NULL;
        newDoctor->availableAppointments = available_appointments;
        newDoctor->next = root->doctors;
        root->doctors = newDoctor;
        return root;
    }
    
    root = balanceSpecializationNode(root);
    return root;
}

DoctorPtr SearchDoctorByName(SpecializationNodePtr root, const char* name, const char* surname) {
    if (!root) {
        return NULL;
    }

    DoctorPtr foundDoctor = SearchDoctorByName(root->left, name, surname);
    if (foundDoctor) return foundDoctor;

    DoctorPtr currentDoctor = root->doctors;
    while (currentDoctor != NULL) {
        if (strcmp(currentDoctor->name, name) == 0 && strcmp(currentDoctor->surname, surname) == 0) {
            return currentDoctor;
        }
        currentDoctor = currentDoctor->next;
    }

    return SearchDoctorByName(root->right, name, surname);
}

DoctorPtr SearchDoctorBySpecialization(SpecializationNodePtr root, const char* specialization) {
    if (!root) {
        return NULL;
    }

    if (strcmp(specialization, root->specialization) < 0) {
        return SearchDoctorBySpecialization(root->left, specialization);
    }
    else if (strcmp(specialization, root->specialization) > 0) {
        return SearchDoctorBySpecialization(root->right, specialization);
    }
    else {
        return root;
    }
}

SpecializationNodePtr DeleteDoctor(SpecializationNodePtr root, const char* name, const char* surname) {
    if (!root) {
        return NULL;
    }

    if (strcmp(name, root->specialization) < 0) {
        root->left = DeleteDoctor(root->left, name, surname);
    }
    else if (strcmp(name, root->specialization) > 0) {
        root->right = DeleteDoctor(root->right, name, surname);
    }
    else {
        DoctorPtr prev = NULL;
        DoctorPtr current = root->doctors;

        while (current != NULL) {
            if (strcmp(current->name, name) == 0 && strcmp(current->surname, surname) == 0) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    root->doctors = current->next;
                }

                free(current);
                printf("Doktor %s %s obrisan\n", name, surname);
                return root;
            }
            prev = current;
            current = current->next;
        }
    }

    root = balanceSpecializationNode(root);
    return root;
}


SpecializationNodePtr balanceSpecializationNode(SpecializationNodePtr root) {
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotation(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotation(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(SpecializationNodePtr node) {
    if (!node) return 0;
    return node->height;
}

int getBalance(SpecializationNodePtr node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

SpecializationNodePtr rotate(SpecializationNodePtr root, int direction) {
    SpecializationNodePtr newRoot;

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


SpecializationNodePtr rightRotation(SpecializationNodePtr root) {
    return rotate(root, 0);
}

SpecializationNodePtr leftRotation(SpecializationNodePtr root) {
    return rotate(root, 1);
}

