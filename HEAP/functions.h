#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define MAX_PASSAGEIROS 5
#define MAX_NAVES 20
#define MAX_RECURSOS 3

/************************************************/
/***************Implementa��o das Estruturas*****/
/************************************************/

// Explica��o
typedef struct passageiro{
    char id[8];
    char nome[50];
    int idade;
    char origem[4];
    int doente;
    int especializado;
} Passageiro;

// Explica��o
typedef struct nave{
    char id[8];
    char recursos[MAX_RECURSOS][50];
    Passageiro passageiros[MAX_PASSAGEIROS];
    int prioridade;
} Nave;

// Explica��o
typedef struct heap{
    int tamanho;
    Nave naves[MAX_NAVES];
} Heap;

/************************************************/
/***************Implementa��o das Fun��es********/
/************************************************/

// Explica��o
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

// Explica��o
int calculaPrioridade(Nave n){
    int prioridade = 0;

    for(int i = 0; i < MAX_PASSAGEIROS; i++){
        if(n.passageiros[i].especializado == 1){
            prioridade += 5;
        }

        if(n.passageiros[i].doente == 1){
            prioridade += 3;
        }
    }

    for(int i = 0; i < MAX_RECURSOS; i++){
        if(strcmp(n.recursos[i], "Alimento") == 0 || strcmp(n.recursos[i], "Medicina") == 0 || strcmp(n.recursos[i], "Armamento") || strcmp(n.recursos[i], "Recursos raros")){
            prioridade += 20;
        }
    }

    return prioridade;
}

// Explica��o
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

// Explica��o
Heap criarHeap(){
    Heap h;
    h.tamanho = 0;

    return h;
}


// Explica��o
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

// Explica��o
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

// Explica��o
void verificarPrioridade(Nave* n){
    srand(time(NULL));
    int probabilidade = rand()%10 + 1;

    if(probabilidade == 10){
        n->prioridade = alterarPrioridade();
    }
}

// Explica��o
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


// Explica��o
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
