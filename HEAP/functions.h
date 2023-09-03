#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define MAX_PASSAGEIROS 5
#define MAX_NAVES 100
#define MAX_RECURSOS 3
#define MAX_LINHAS 1000
#define TOTAL_NAVES_CSV 26

typedef struct passageiro{
    int id;
    char nome[50];
    int idade;
    int origem;
    int doente;
    int especializado;
} Passageiro;


typedef struct nave{
    int id;
    char recursos[MAX_RECURSOS][50];
    Passageiro passageiros[MAX_PASSAGEIROS];
    int prioridade;
} Nave;

// O heap é uma fila de naves

typedef struct heap Heap;


/************************************************/
/***************Declaração das Funções***********/
/************************************************/

// Essa função cria um passageiro através de suas informações

Passageiro criarPassageiro(char* nome, int idade, int doente, int especializado, int origem, int id);

// Essa função cria uma nave através de suas informações

Nave criarNave(int id, char recursos[][50], Passageiro passageiros[]);

// Cria uma Fila de Prioridades vazia

Heap* criarHeap();

// Libera a Fila da memória

void liberarHeap(Heap* h);

// Imprime as informações do passageiro p

void infoPassageiro(Passageiro p);

// Imprime as informações da nave n

void infoNave(Nave n);


// Essa função escolhe um número aleatório entre 1 e 10
// Se o número for igual a 10 (10% de chance) ele altera a prioridade da nave

void verificarPrioridade(Nave* n);

// Troca de lugar as naves i e j da Heap h

void trocar(Heap* h, int i, int j);

// Verifica se a nave na posição index atende a condição da heap, caso contrario, ela sobe para a posição i/2
// O processo é feito de maneira recursiva até ela chegar a posição correta

void subir(Heap* h, int index);

// Verifica se a nave na posição index atende a condição da heap, caso contrario, ela desce para a posição 2i ou 2i+1
// O processo é feito de maneira recursiva até ela chegar a posição correta

void descer(Heap* h, int index);

// A nave é inserida no final, e sobe até a posição correta (função subir())

void inserirNave(Nave *n, Heap* h);

// É trocado o primeiro com o último elemento da heap, e faz o primeiro elemento (antes último) descer

void removerNave(Heap* h);

// Ordena um vetor qualquer em uma heap

void ordenaHeap(Heap* h);

// Exibe a informação de todas as naves de uma heap

void exibir_heap(Heap* h);


void adiciona_passageiros(char* file_passageiros, Heap* h);
void adiciona_recursos(char* file_recursos, Heap* h);
void inicializar();
void finalizar();

#endif // FUNCTIONS_H_INCLUDED
