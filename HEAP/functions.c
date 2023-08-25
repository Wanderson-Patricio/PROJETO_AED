#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
/************************************************/
/***************Implementa��o das Estruturas*****/
/************************************************/

typedef struct heap{
    int tamanho;
    Nave naves[MAX_NAVES + 1];
} Heap;


/************************************************/
/***************Implementa��o das Fun��es********/
/************************************************/

Passageiro criarPassageiro(char* nome, int idade, int doente, int especializado, int origem, int id){
    Passageiro p;
    strcpy(p.nome, nome);
    p.idade = idade;
    p.doente = doente;
    p.especializado = especializado;
    p.origem;
    p.id;

    return p;
}

Nave criarNave(int id, char recursos[][50], Passageiro passageiros[]){
    Nave n;
    n.id = id;

    for(int i = 0; i<MAX_PASSAGEIROS; i++){
        n.passageiros[i] = *(passageiros+i);
    }

    for(int i = 0; i<MAX_RECURSOS; i++){
        strcpy(n.recursos[i], *(recursos + i));
    }

    srand(time(NULL));
    n.prioridade = rand()%100 + 1;
    return n;
}

Heap* criarHeap(){
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->tamanho = 0;

    return h;
}

void liberarHeap(Heap* h){
    free(h);
}


void infoPassageiro(Passageiro p){
    printf("Nome: %s \n", p.nome);
    printf("Idade: %d anos \n", p.idade);
    printf("Id: %d \n", p.id);
    printf("Planeta de Origem: %d \n", p.origem);

    if(p.especializado == 1){
        printf("Possui especializacao. \n");
    }else{
        printf("Nao possui especializacao. \n");
    }

    if(p.doente == 1){
        printf("Esta Doente. \n");
    }else{
        printf("Nao esta Doente. \n");
    }
    printf("\n");
}

void infoNave(Nave n){
    printf("******************************************************* \n");
    printf("Id da Nave: %d \n", n.id);
    printf("Prioridade: %d \n", n.prioridade);
    printf("------Recursos na nave------ \n");

    for(int i = 0; i<MAX_RECURSOS; i++){
        printf("%d - %s \n", i+1, n.recursos[i]);
    }

    printf("\n");
    printf("------Passageiros na nave------ \n");
    for(int i = 0; i<MAX_PASSAGEIROS; i++){
        infoPassageiro(n.passageiros[i]);
    }
    printf("******************************************************* \n");
}

void verificarPrioridade(Nave* n){
    srand(time(NULL));
    int probabilidade = rand()%10 + 1;

    if(probabilidade == 10){
        n->prioridade = rand()%101;
    }
}

void trocar(Heap* h, int i, int j){
    Nave aux = h->naves[i];
    h->naves[i] = h->naves[j];
    h->naves[j] = aux;
}


void subir(Heap* h, int index){
    int j = index/2;

    if(j>=1){
        if(h->naves[index].prioridade > h->naves[j].prioridade){
            trocar(h, index, j);
            subir(h, j);
        }
    }
}


void descer(Heap* h, int index){
    int j = 2*index;

    if(j <= h->tamanho){
        if(j < MAX_NAVES){
            if(h->naves[j+1].prioridade > h->naves[j].prioridade){
                j = j+1;
            }
        }

        if(h->naves[index].prioridade < h->naves[j].prioridade){
            trocar(h, index, j);
            descer(h, j);
        }
    }
}

void inserirNave(Nave n, Heap* h){
    if(h->tamanho < MAX_NAVES){
        verificarPrioridade(&n);
        h->naves[h->tamanho +1] = n;
        h->tamanho++;
        subir(h, h->tamanho);
        printf("Inserido com sucesso. \n");
    }else{
        printf("A fila esta cheia. \n");
    }
}


void removerNave(Heap* h){
    if(h->tamanho > 0){
        printf("Nave a partir \n\n");
        infoNave(h->naves[1]);
        trocar(h, 1, h->tamanho);
        h->tamanho--;
        descer(h, 1);
    }

}


void exibir_heap(Heap* h){
    if(h->tamanho == 0){
        printf("Fila vazia. \n");
    }

    for(int i = 1; i<= h->tamanho; i++){
        infoNave(h->naves[i]);
    }
}

/************************************************/
/***************Funções de inicialização*********/
/***************E Finalização********************/
/************************************************/

void gera_heap_por_csv(char* passageiros, char* recursos, Heap* h){

}


void inicializar(){
    Heap *fila = criarHeap();


    int continuar = -1;
    int opcao;

    while(continuar != 0){
        printf("------------------------------------------------------- \n");
        printf("Digite a opcao desejada. \n\n");

        printf("1 - Enviar a primeira nave pelo portal. \n");
        printf("2 - Exibir a informacao de todas as naves da fila. \n");
        printf("3 - Alterar a prioridade de uma nave. \n");
        printf("4 - Inserir uma nave na fila. \n");
        printf("5 - Exibir as informacoes de uma nave. \n");
        printf("0 - Sair. \n");
        printf("------------------------------------------------------- \n\n");

        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);
        if(opcao == 0){
            continuar = 0;
        }
        system("cls");

        switch(opcao){
            case 1:{
                removerNave(fila);
                system("pause");
                system("cls");
                break;
            }

            case 2:{
                exibir_heap(fila);
                system("pause");
                system("cls");
                break;
            }

            case 3:{
                int nave, prioridade;

                printf("Digite o indice da nave que deseja alterar (Disponiveis: ate %d). \n", fila->tamanho);
                scanf("%d", &nave);
                system("cls");

                if(nave > fila->tamanho || nave <= 0){

                    printf("Indice invalido. \n");

                }else{

                    printf("Qual sera a nova prioridade? \n");
                    scanf("%d", &prioridade);

                    fila->naves[nave].prioridade = prioridade;
                    subir(fila, nave);
                    descer(fila, nave);

                    printf("Prioridade alterada. \n");

                }

                system("pause");
                system("cls");
                break;
            }

            case 4:{
                Nave newNave;
                Passageiro passageiro_aux;
                char nome[50], recursos[50];
                int idade, doente, especializado, id, origem;

                printf("Id da nave? \n");
                scanf("%d", &id);
                newNave.id = id;

                for(int i = 0; i < MAX_PASSAGEIROS; i++){
                    printf("Id do passageiro %d: \n", i+1);
                    scanf("%d", &id);
                    passageiro_aux.id = id;

                    printf("Nome do passageiro %d: \n", i+1);
                    fflush(stdin);
                    fgets(nome, 50, stdin);
                    strcpy(passageiro_aux.nome, nome);

                    printf("Planeta de origem do passageiro %d: \n", i+1);
                    scanf("%d", &origem);
                    passageiro_aux.origem = origem;

                    printf("Idade do passageiro %d: \n", i+1);
                    scanf("%d", &idade);
                    passageiro_aux.idade = idade;

                    printf("Possui Especializacao?\nSIM - Digite 1\nNAO - Digite 0  \n");
                    scanf("%d", &especializado);
                    passageiro_aux.especializado = especializado;

                    printf("Esta Doente?\nSIM - Digite 1\nNAO - Digite 0  \n");
                    scanf("%d", &doente);
                    passageiro_aux.doente = doente;

                    newNave.passageiros[i] = passageiro_aux;
                }

                for(int i=0; i < MAX_RECURSOS; i++){
                    printf("Qual o recurso %d da nave? \n", i+1);
                    fflush(stdin);
                    fgets(recursos, 50, stdin);
                    strcpy(newNave.recursos[i], recursos);
                }

                inserirNave(newNave, fila);
                system("pause");
                system("cls");
                break;
            }

            case 5:{
                int nave;

                printf("Digite o indice da nave que deseja visualizar (Disponiveis: ate %d). \n", fila->tamanho);
                scanf("%d", &nave);
                system("cls");

                if(nave > fila->tamanho || nave <= 0){

                    printf("Indice invalido. \n");

                }else{

                    infoNave(fila->naves[nave]);

                }

                system("pause");
                system("cls");
                break;
            }

            case 0: continuar = 0; break;
            default: printf("Opcao invalida. \n"); break;

        }
    }

    liberarHeap(fila);
}


void finalizar(){
    printf("Obrigado por usar o nosso programa. :):)\n");
}
