#include "../Headers/patient.h"
#include "../Headers/read_files.h"
#include <stdio.h>

int main(){
    HashTable* hash_table = CreateHashTable(11);

    ReadPatients(hash_table);

    ListAllPatients(hash_table);



    return 0;
}