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
    int id;
    char nome[50];
    int idade;
    int origem;
    int doente;
    int especializado;
} Passageiro;


// Uma nave possui um id, um conjunto de passageiros, e uma lista de recursos
// Al�m de ter uma prioridade, dependendo de seus recursos e passageiros
typedef struct nave{
    int id;
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


// A nave é inserida no final, e sobe até a posição correta (função subir())
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


// É trocado o primeiro com o último elemento da heap, e faz o primeiro elemento (antes último) descer
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


// Verifica se a nave na posição index atende a condição da heap, caso contrario, ela sobe para a posição i/2
// O processo é feito de maneira recursiva até ela chegar a posição correta
void subir(Heap* h, int index){
    int j = (int) index/2;

    if(j>=0){
        if(h->naves[index].prioridade > h->naves[j].prioridade){
            trocar(h, index, j);
            subir(h, j);
        }
    }
}


// Verifica se a nave na posição index atende a condição da heap, caso contrario, ela desce para a posição 2i ou 2i+1
// O processo é feito de maneira recursiva até ela chegar a posição correta
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


// Exibe a informação de todas as naves de uma heap
void exibir_heap(Heap* h, int i){
    if(i < h->tamanho){
        infoNave(h->naves[i]);
        system("pause");
        system("cls");
        exibir_heap(h, 2*i);
        exibir_heap(h, 2*i + 1);
    }
}

/************************************************/
/***************Funções de inicialização*********/
/***************E Finalização********************/
/************************************************/

void gera_heap_por_csv(char* passageiros, char* recursos, Heap* h){

}


void inicializar(){
    Heap fila = criarHeap();
    gera_heap_por_csv("passageiros.csv", "recursos.csv", &fila);


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
                removerNave(&fila);
                system("pause");
                system("cls");
                break;
            }

            case 2:{
                exibir_heap(&fila, 0);
                break;
            }

            case 3:{
                int nave, prioridade;

                printf("Digite o índice da nave que deseja alterar (Disponíveis: até %d). \n", fila.tamanho);
                scanf("%d", &nave);
                system("cls");

                if(nave > fila.tamanho || nave <= 0){

                    printf("Indice invalido. \n");

                }else{

                    printf("Qual sera a nova prioridade? \n");
                    scanf("%d", &prioridade);

                    fila.naves[nave-1].prioridade = prioridade;
                    subir(&fila, nave-1);
                    descer(&fila, nave-1);

                    printf("Prioridade alterada. \n");

                }

                system("pause");
                system("cls");
                break;
            }

            case 4:{
                Nave newNave;
                Passageiro passageiro_aux;
                char nome[50], id[8], origem[4], recursos[50];
                int idade, doente, especializado;

                printf("Id da nave? \n");
                gets(id);
                getchar();
                strcpy(newNave.id, id);

                for(int i = 0; i < MAX_PASSAGEIROS; i++){
                    printf("Id do passageiro %d: \n", i+1);
                    gets(id);
                    //getchar();
                    strcpy(passageiro_aux.id, id);

                    printf("Nome do passageiro %d: \n", i+1);
                    gets(nome);
                    //getchar();
                    strcpy(passageiro_aux.nome, nome);

                    printf("Planeta de origem do passageiro %d: \n", i+1);
                    gets(origem);
                    //getchar();
                    strcpy(passageiro_aux.origem, origem);

                    printf("Idade do passageiro %d: \n", i+1);
                    scanf("%d", &idade);
                    //getchar();
                    passageiro_aux.idade = idade;

                    printf("Possui Especializacao?\nSIM - Digite 1\,NAO - Digite 0  \n");
                    scanf("%d", &especializado);
                    //getchar();
                    passageiro_aux.especializado = especializado;

                    printf("Esta Doente?\nSIM - Digite 1\,NAO - Digite 0  \n");
                    scanf("%d", &doente);
                    //getchar();
                    passageiro_aux.doente = doente;

                    newNave.passageiros[i] = passageiro_aux;
                }

                for(int i=0; i < MAX_RECURSOS; i++){
                    printf("Qual o recurso %d da nave? \n", i+1);
                    gets(recursos);
                    getchar();
                    strcpy(newNave.recursos[i], recursos);
                }

                inserirNave(newNave, &fila);
                system("pause");
                system("cls");
                break;
            }

            case 5:{
                int nave;

                printf("Digite o índice da nave que deseja visualizar (Disponíveis: até %d). \n", fila.tamanho);
                scanf("%d", &nave);
                system("cls");

                if(nave > fila.tamanho || nave <= 0){

                    printf("Indice invalido. \n");

                }else{

                    infoNave(fila.naves[nave-1]);

                }

                system("pause");
                system("cls");
                break;
            }

            case 0: continuar = 0; break;
            default: printf("Opcao invalida. \n"); break;

        }
    }
}


void finalizar(){
    printf("Obrigado por usar o nosso programa. :):)\n");
}

#endif // FUNCTIONS_H_INCLUDED
