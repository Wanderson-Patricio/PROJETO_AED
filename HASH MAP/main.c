#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "header.h"

#define MAX_LINHAS 1024

int main(){
    setlocale(LC_ALL, "portuguese");

    Table *t = createTable();

    int ids[MAX_RESOURCES], coluna;
    char *S[MAX_LINHAS], *ptr;
    FILE *fptr;

    fptr = fopen("recursos1.csv", "r");

    while(fgets(S, MAX_LINHAS, fptr) != NULL){
        ptr = strtok(S, ",");
        coluna = 0;

        while(ptr != NULL){
            ids[coluna] = atoi(ptr);
            coluna++;
            ptr = strtok(NULL, ",");
        }

        insertCompartment(t, createCompartment(ids));
    }

    fclose(fptr);

    printf("\n");
    infoTable(t);

    deleteTable(t);

    return 0;
}
