#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "header.h"

int main(){
    setlocale(LC_ALL, "portuguese");
    int ids1[]  = {3,1,2};
    int ids2[]  = {1,3,2};
    int ids3[]  = {2,1,3};
    int ids4[]  = {2,3,1};
    int ids5[]  = {5,2,4};
    int ids6[]  = {3,2,1};
    int ids7[]  = {2,4,5};
    int ids8[]  = {2,5,4};
    int ids9[]  = {4,2,5};
    int ids10[] = {5,4,2};
    int ids11[] = {1,2,3};
    Compartment c1  = createCompartment(ids1);
    Compartment c2  = createCompartment(ids2);
    Compartment c3  = createCompartment(ids3);
    Compartment c4  = createCompartment(ids4);
    Compartment c5  = createCompartment(ids5);
    Compartment c6  = createCompartment(ids6);
    Compartment c7  = createCompartment(ids7);
    Compartment c8  = createCompartment(ids8);
    Compartment c9  = createCompartment(ids9);
    Compartment c10 = createCompartment(ids10);
    Compartment c11 = createCompartment(ids11);


    Table* t = createTable();

    for(int i=0; i<100; i++){
        insertCompartment(t, c1);
        insertCompartment(t, c2);
        insertCompartment(t, c3);
        insertCompartment(t, c4);
        insertCompartment(t, c5);
        insertCompartment(t, c6);
        insertCompartment(t, c7);
        insertCompartment(t, c8);
        insertCompartment(t, c9);
        insertCompartment(t, c10);
        insertCompartment(t, c11);
    }

    printf("\n");
    infoTable(t);

    deleteTable(t);

    return 0;
}
