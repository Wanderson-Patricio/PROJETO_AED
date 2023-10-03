#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#define MAX_RESOURCES 3 // A quantidade de recursos por compartimento
#define MAX_PERMUTATIONS 6 // 3 recursos por compartimento, dando 3! permutacções
#define MAX_SIZE 667 // 6 diferentes recursos (666+1)

// Anderson
// Definicao da estrutura recurso, identificada pelo seu id
typedef struct resource{
    char nome[50];
    int id;
}Resource;

// Anderson
// Um compartmento e um vetor de recursos
typedef struct compartment{
    Resource recursos[MAX_RESOURCES];
}Compartment;

// Anderson
// A insercao dos compartimentos e feita em uma tabela de recursos
// temos um vetor indicando a quantidade de compartimentos em cada linha
// um contador para dizer quantas insercoes ocorreram desde a ultima abertura
// e um contador de aberturas
typedef struct table{
    Compartment tabela[MAX_SIZE][MAX_PERMUTATIONS];
    int qtds[MAX_SIZE];
    int contador;
    int aberturas;
}Table;

// A partir de um id e criado um novo recurso
Resource createResource(int id);

// Mostra na tela as informacoes do recurso r
void infoResource(Resource r);

// A partir de uma lista de ids sao criados os recursos e inseridos em um compartimento novo
Compartment createCompartment(int ids[]);

// Mostra na tela as informacoes de um compartimento
void infoCompartment(Compartment c);

// Anderson
// verifica se dois compartimentos sao iguais
int isEquals(Compartment a, Compartment b);

// Cria uma tabela vazia
Table* createTable();

// Libera a tabela da memoria
void deleteTable(Table* t);

// Mostra na tela as informacoes da tabela
void infoTable(Table* t);

/************************************************************/

// Função para concatenar 4 inteiros
// Anderson
int concatenateIntegers(int numbers[], int n);

// Anderson (Cria HEAP Sort e muda)
void selectionSort(int arr[], int n);

// Função hash para o compartimento
// Anderson
int h(Compartment c);

// Anderson
// Funcao para verificar se uma linha alcancou o maximo de permutacoes
int verificaAbertura(Table* t, int linha);

// Anderson
// reseta as informacoes de uma linha
void resetar(Table* t, int linha);

// Anderson
// Funcao para verificar se aquela combinacao de recursos ja existe na linha
// ou se e uma permutacao nova
int isNewPermutation(Table* t, int linha, Compartment c);

// Funcao para inserir um novo compartimento na tabela
void insertCompartment(Table* t, Compartment c);


#endif // HASH_H_INCLUDED
