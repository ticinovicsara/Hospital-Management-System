#include "../Headers/doctor.h"
#include <string.h>

SpecializationNodePtr InsertDoctor(SpecializationNodePtr root, char* specialization, char* name, int available_appointments){
    if(!root){
        SpecializationNodePtr node = (SpecializationNodePtr)malloc(sizeof(SpecializationNode));
        if(!node){
            printf("Neuspjesna alokacija node za doktora\n");
            return NULL;
        }

        strcpy(node->specialization, specialization);
        node->doctors = NULL;

        DoctorPtr newDoctor = (DoctorPtr)malloc(sizeof(Doctor));
        if (!newDoctor) {
            printf("Neuspjesna alokacija za doktora\n");
            free(node);
            return NULL;
        }
        strcpy(newDoctor->name, name);
        newDoctor->appointments = NULL;
        newDoctor->availableAppointments = available_appointments;
        newDoctor->next = NULL;

        node->doctors = newDoctor;
        node->left = node->right = NULL;
        node->height = 1;
        return node;
    }

    if (strcmp(specialization, root->specialization) < 0) {
        root->left = insertDoctor(root->left, specialization, name, available_appointments);
    } else if (strcmp(specialization, root->specialization) > 0) {
        root->right = insertDoctor(root->right, specialization, name, available_appointments);
    } else {
        DoctorPtr newDoctor = (DoctorPtr)malloc(sizeof(Doctor));
        if(!newDoctor){
            printf("Neuspjesna alokacija za doktora\n");
            return root;
        }
        strcpy(newDoctor->name, name);
        newDoctor->appointments = NULL;
        newDoctor->availableAppointments = available_appointments;
        newDoctor->next = root->doctors;
        root->doctors = newDoctor;
    }


    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && strcmp(specialization, root->left->specialization) < 0)
        return rightRotation(root);
    if (balance < -1 && strcmp(specialization, root->right->specialization) > 0)
        return leftRotation(root);
    if (balance > 1 && strcmp(specialization, root->left->specialization) > 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    if (balance < -1 && strcmp(specialization, root->right->specialization) < 0) {
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

