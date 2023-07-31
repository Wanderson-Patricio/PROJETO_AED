#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define MAX_PASSAGEIROS 5
#define MAX_NAVES 100
#define MAX_RECURSOS 3

/************************************************/
/***************Implementa��o das Estruturas*****/
/************************************************/

// Um passgeiro pssui um id (identificador �nico), um nome, uma idade e um planeta de origem
// Al�m disso, um passageiro possui um identificador para dizer se ele est� doente, e se ele tem alguma especializa��o
// Por exemplo, se � um m�dico.
typedef struct passageiro{
    char id[8];
    char nome[50];
    int idade;
    char origem[4];
    int doente;
    int especializado;
} Passageiro;

// Uma nave possui um id, um conjunto de passageiros, e uma lista de recursos
// Al�m de ter uma prioridade, dependendo de seus recursos e passageiros
typedef struct nave{
    char id[8];
    char recursos[MAX_RECURSOS][50];
    Passageiro passageiros[MAX_PASSAGEIROS];
    int prioridade;
} Nave;

// A fila de Prioridades tem uma lista de naves, com tamanho m�ximo de MAX_NAVES
// al�m de uma vari�vel que indica a quantidade na fila
typedef struct heap{
    int tamanho;
    Nave naves[MAX_NAVES];
} Heap;

/************************************************/
/***************Implementa��o das Fun��es********/
/************************************************/

// Essa fun��o cria um passageiro atrav�s de suas informa��es
Passageiro criarPassageiro(char* nome, int idade, int doente, int especializado, char* origem, char* id){
    Passageiro p;
    strcpy(p.nome, nome);
    p.idade = idade;
    p.doente = doente;
    p.especializado = especializado;
    strcpy(p.origem, origem);
    strcpy(p.id, id);

    return p;
}

// Essa fun��o calcula a prioridade inicial de uma nave com base nos recursos e passageiros
int calculaPrioridade(Nave n){
    int prioridade = 0;

    for(int i = 0; i < MAX_PASSAGEIROS; i++){

        // Se o passageiro � especializado a prioridade aumenta em 5
        if(n.passageiros[i].especializado == 1){
            prioridade += 5;
        }

        // Se o passageiro est� doente a prioridade aumenta em 5
        if(n.passageiros[i].doente == 1){
            prioridade += 3;
        }
    }

    for(int i = 0; i < MAX_RECURSOS; i++){

        // Se algum dos recursos da nave for essencial a prioridade aumenta em 20
        if(strcmp(n.recursos[i], "ALIMENTOS") == 0 || strcmp(n.recursos[i], "REMEDIOS") == 0 || strcmp(n.recursos[i], "ARMAMENTO") || strcmp(n.recursos[i], "RECURSOS RAROS")){
            prioridade += 20;
        }
    }

    return prioridade;
}

// Essa fun��o cria uma nave atrav�s de suas informa��es
Nave criarNave(char* id, char recursos[][50], Passageiro passageiros[]){
    Nave n;
    strcpy(n.id, id);

    for(int i = 0; i<MAX_PASSAGEIROS; i++){
        n.passageiros[i] = *(passageiros+i);
    }

    for(int i = 0; i<MAX_RECURSOS; i++){
        strcpy(n.recursos[i], *(recursos + i));
    }

    n.prioridade = calculaPrioridade(n);
    return n;
}

// Cria uma Fila de Prioridades vazia
Heap criarHeap(){
    Heap h;
    h.tamanho = 0;

    return h;
}


// Imprime as informa��es do passageiro p
void infoPassageiro(Passageiro p){
    printf("Nome: %s \n", p.nome);
    printf("Idade: %d anos \n", p.idade);
    printf("Id: %s \n", p.id);
    printf("Planeta de Origem: %s \n", p.origem);

    if(p.especializado == 1){
        printf("Possui especializa��o. \n");
    }else{
        printf("N�o possui especializa��o. \n");
    }

    if(p.doente == 1){
        printf("Est� Doente. \n");
    }else{
        printf("N�o est� Doente. \n");
    }
    printf("\n");
}

// Imprime as informa��es da nave n
void infoNave(Nave n){
    printf("******************************************************* \n");
    printf("Id da Nave: %s \n", n.id);
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

// Essa fun��o escolhe um n�mero aleat�rio entre 1 e 10
// Se o n�mero for igual a 10 (10% de chance) ele altera a prioridade da nave
// Atrav�s da alterarPrioridade()
void verificarPrioridade(Nave* n){
    srand(time(NULL));
    int probabilidade = rand()%10 + 1;

    if(probabilidade == 10){
        n->prioridade = alterarPrioridade();
    }
}

// Retorna um n�mero aleat�rio entre 0 e 100
int alterarPrioridade(){
    srand(time(NULL));

    int newPrioridade = rand()%101;
    return newPrioridade;
}

// Explica��o
void inserirNave(Nave n, Heap* h){
    if(h->tamanho < MAX_NAVES){
        verificarPrioridade(&n);
        h->naves[h->tamanho] = n;
        subir(h, h->tamanho);
        h->tamanho++;
        printf("Inserido com sucesso. \n");
    }else{
        printf("A fila est� cheia. \n");
    }
}

// Explica��o
void removerNave(Heap* h){
    if(h->tamanho > 0){
        printf("Nave a partir \n\n");
        infoNave(h->naves[0]);
        trocar(h, 0, h->tamanho - 1);
        h->tamanho--;
        h->naves[h->tamanho].prioridade = -1;
    }

}


// Troca de lugar as naves i e j da Heap h
void trocar(Heap* h, int i, int j){
    Nave aux = h->naves[i];
    h->naves[i] = h->naves[j];
    h->naves[j] = aux;
}

// Explica��o
void subir(Heap* h, int index){
    int j = (int) index/2;

    if(j>=0){
        if(h->naves[index].prioridade > h->naves[j].prioridade){
            trocar(h, index, j);
            subir(h, j);
        }
    }
}

// Explica��o
void descer(Heap* h, int index){
    int j = 2*index;

    if(j <= MAX_NAVES){
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


#endif // FUNCTIONS_H_INCLUDED
