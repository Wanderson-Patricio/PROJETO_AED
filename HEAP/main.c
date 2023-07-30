#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "functions.h"

int main(){
    setlocale(LC_ALL, "portuguese");

    Passageiro p1 = criarPassageiro("aaa", 21, 1, 1, "TER", "TER0001");
    Passageiro p2 = criarPassageiro("bbb", 21, 1, 1, "TER", "TER0001");
    Passageiro p3 = criarPassageiro("ccc", 21, 1, 1, "TER", "TER0001");
    Passageiro p4 = criarPassageiro("ddd", 21, 1, 1, "TER", "TER0001");
    Passageiro p5 = criarPassageiro("eee", 21, 1, 1, "TER", "TER0001");

    Passageiro p[5];
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
    p[4] = p5;

    char recursos[3][50];
    strcpy(recursos[0], "Alimentos");
    strcpy(recursos[1], "Armamento");
    strcpy(recursos[2], "Medicina");


    Nave n1 = criarNave("TER0001", recursos, p);
    Nave n2 = criarNave("TER0002", recursos, p);
    Nave n3 = criarNave("TER0003", recursos, p);
    Nave n4 = criarNave("TER0004", recursos, p);
    Nave n5 = criarNave("TER0005", recursos, p);
    Nave n6 = criarNave("TER0006", recursos, p);
    Nave n7 = criarNave("TER0007", recursos, p);
    Nave n8 = criarNave("TER0008", recursos, p);
    Nave n9 = criarNave("TER0009", recursos, p);
    Nave n10 = criarNave("TER0010", recursos, p);
    n5.prioridade = 1000;


    Heap h = criarHeap();

    inserirNave(n1, &h);
    inserirNave(n2, &h);
    inserirNave(n3, &h);
    inserirNave(n4, &h);
    inserirNave(n5, &h);
    inserirNave(n6, &h);
    inserirNave(n7, &h);
    inserirNave(n8, &h);
    inserirNave(n9, &h);
    inserirNave(n10, &h);

    removerNave(&h);
    return 0;
}
