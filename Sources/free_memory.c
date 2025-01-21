#include "patient.h"
#include "appointment.h"
#include "doctor.h"
#include "help-functions.h"
#include <stdlib.h>
#include <stdio.h>

#define SAFE_FREE(ptr) if (ptr) { free(ptr); ptr = NULL; }

static void FreeHashTable(HashTable* ht);
static void FreeSpecializationTree(SpecializationNodePtr root);
static void FreeDoctor(DoctorPtr doctor);
static void FreeAppointmentTree(AppointmentNodePtr root);
static void FreeNodeList(NodePosition node);
static void FreePatient(Patientptr patient);
static void FreeMedicalRecords(RecordPtr record);

void FreeAllResources(HashTable* ht, SpecializationNodePtr root, PriorityQueue* pq) {
    FreeHashTable(ht);

    if (pq) {
        free(pq);
    }

    FreeSpecializationTree(root);
}

static void FreeHashTable(HashTable* ht) {
    if (ht == NULL) return;

    for (int i = 0; i < ht->size; ++i) {
        FreeNodeList(ht->buckets[i]);
    }

    SAFE_FREE(ht->buckets);
    SAFE_FREE(ht);
}

static void FreeSpecializationTree(SpecializationNodePtr root) {
    if (root == NULL) return;

    FreeSpecializationTree(root->left);
    FreeSpecializationTree(root->right);

    DoctorPtr doctor = root->doctors;
    while (doctor != NULL) {
        DoctorPtr temp = doctor;
        doctor = doctor->next;
        FreeDoctor(temp);
    }

    SAFE_FREE(root);
}

static void FreeDoctor(DoctorPtr doctor) {
    if (doctor == NULL) return;

    if (doctor->patients != NULL) {
        FreeNodeList(doctor->patients);
        doctor->patients = NULL; 
    }

    if (doctor->appointments != NULL) {
        FreeAppointmentTree(doctor->appointments);
        doctor->appointments = NULL;
    }

    SAFE_FREE(doctor);
}

static void FreeAppointmentTree(AppointmentNodePtr root) {
    if (root == NULL) return;

    FreeAppointmentTree(root->left);
    FreeAppointmentTree(root->right);

    SAFE_FREE(root);
}

static void FreeNodeList(NodePosition node) {
    while (node != NULL) {
        NodePosition temp = node;

        if (node->patient != NULL) {
            FreePatient(node->patient);
            node->patient = NULL;
        }

        node = node->next;
        SAFE_FREE(temp);
    }
}

static void FreePatient(Patientptr patient) {
    if (patient == NULL) return;

    FreeMedicalRecords(patient->ilnesses);

    FreeMedicalRecords(patient->checkups);

    SAFE_FREE(patient);
}

static void FreeMedicalRecords(RecordPtr record) {
    while (record != NULL) {
        RecordPtr temp = record;
        record = record->next;
        SAFE_FREE(temp);
    }
}
