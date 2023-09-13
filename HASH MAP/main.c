#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(){
    int ids1[] = {3,4,5,2};
    int ids2[] = {2,1,3,4};
    int ids3[] = {4,1,5,2};
    int ids4[] = {5,5,4,2};
    Compartment c1 = createCompartment(ids1);
    Compartment c2 = createCompartment(ids2);
    Compartment c3 = createCompartment(ids3);
    Compartment c4 = createCompartment(ids4);

    Table* t = createTable();
    insertCompartment(t, c1);
    insertCompartment(t, c2);
    insertCompartment(t, c3);
    insertCompartment(t, c4);

    printf("%d \n", t->contador);
    deleteTable(t);
    return 0;
}
