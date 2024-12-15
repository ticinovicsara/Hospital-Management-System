#include "../Headers/read_files.h"
#include <stdio.h>

int main(){
    HashTable* hash_table = CreateHashTable(11);
    ReadPatients(hash_table);

    SpecializationNodePtr root = NULL;
    ReadDoctors(&root);

    ListAllPatients(hash_table);

    PrintDoctors(root);

    return 0;
}