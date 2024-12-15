#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "../Headers/patient.h"
#include "../Headers/doctor.h"
#include "../Headers/help-functions.h"


void ListAllPatients(HashTable* ht) {
    printf("\nSvi pacijenti: \n");
    printf("     --------------------------------------------------------------\n");
    printf("\tID\tIME\t   PREZIME\t\tDATUM RODJENJA\n");
    printf("     --------------------------------------------------------------\n");

    for(int i = 0; i < ht->size; i++) {
        NodePosition current = ht->buckets[i];

        while(current != NULL) {
            Patientptr p = current->patient;
            printf("\t%-5s\t%-10s %-10s\t\t%-12s\n", p->id, p->name, p->surname, p->birthDate);
            current = current->next;
        }
    }

    printf("\n\n");
}


void PrintDoctors(SpecializationNodePtr root) {
    printf("Svi doktori:\n");
    printf("     --------------------------------------------------------------------------\n");
    printf("\tSPECIJALIZACIJA\t\tIME\t    PREZIME\t    DOSTUPNI TERMINI\n");
    printf("     --------------------------------------------------------------------------\n");


    ListAllDoctors(root);
    printf("\n\n");
}

void ListAllDoctors(SpecializationNodePtr root){
    if(root == NULL){
        return;
    }
    DoctorPtr currDoctor = root->doctors;
    if (currDoctor == NULL) {
        printf("\tNema doktora u ovoj specijalizaciji.\n");
    }
    else {
        while (currDoctor != NULL) {
            printf("\t%-23s %-11s %-15s %-5d\n", root->specialization, currDoctor->name, currDoctor->surname, currDoctor->availableAppointments);
            currDoctor = currDoctor->next;
        }
    }

    ListAllDoctors(root->left);
    ListAllDoctors(root->right);
}
