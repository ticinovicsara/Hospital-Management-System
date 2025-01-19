#include "patient.h"
#include "appointment.h"
#include "doctor.h"
#include "help-functions.h"
#include <stdlib.h>
#include <stdio.h>

static void FreeHashTable(HashTable* ht);
static void FreeSpecializationTree(SpecializationNodePtr root);
static void FreeDoctor(DoctorPtr doctor);
static void FreeAppointmentTree(AppointmentNodePtr root);
static void FreeNodeList(NodePosition node);
static void FreePatient(Patientptr patient);
static void FreeMedicalRecords(RecordPtr record);

void FreeAllResources(HashTable* ht, SpecializationNodePtr root) {
    FreeHashTable(ht);

    FreeSpecializationTree(root);
}

static void FreeHashTable(HashTable* ht) {
    if (ht == NULL) return;

    for (int i = 0; i < ht->size; ++i) {
        FreeNodeList(ht->buckets[i]);
    }

    free(ht->buckets);

    free(ht);
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

    free(root);
}

static void FreeDoctor(DoctorPtr doctor) {
    if (doctor == NULL) return;

    FreeNodeList(doctor->patients); 

    FreeAppointmentTree(doctor->appointments);

    free(doctor);
}

static void FreeAppointmentTree(AppointmentNodePtr root) {
    if (root == NULL) return;

    FreeAppointmentTree(root->left);
    FreeAppointmentTree(root->right);

    free(root->appointment.patientID);
    free(root);
}


static void FreeNodeList(NodePosition node) {
    while (node != NULL) {
        NodePosition temp = node;

        FreePatient(node->patient);

        node = node->next;
        free(temp);
    }
}

static void FreePatient(Patientptr patient) {
    if (patient == NULL) return;

    FreeMedicalRecords(patient->ilnesses);

    FreeMedicalRecords(patient->checkups);

    free(patient);
}

static void FreeMedicalRecords(RecordPtr record) {
    while (record != NULL) {
        RecordPtr temp = record;
        record = record->next;
        free(temp);
    }
}
