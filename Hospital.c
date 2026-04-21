#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PILHA - LIFO
typedef struct Atendimento {
    char nome[50];
    int idade;
    char descricao[100];
    struct Atendimento* prox;
} Atendimento;

Atendimento* topo = NULL;//PILHA - LIFO

Atendimento* inicio = NULL;//FILA - FIFO
Atendimento* fim = NULL;//FILA - FIFO

//PUSH - PILHA - LIFO
void adicionarHistorico(struct Atendimento *novo){
    if(novo == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }
    novo->prox = topo; 
    topo = novo;
    printf("\nHistorico adicionado.");
}
//POP - PILHA - LIFO
void retirarHistorico(){
    
     if(topo == NULL){
        printf("Historico vazio.\n");
        return;
    }

    struct Atendimento *temp = topo;
    topo = temp->prox;
    printf("\nHistorico retirado.");
    printf("\nNome: %s | Idade: %d | Desc: %s\n", temp->nome, temp->idade, temp->descricao);
    free(temp);
}   

//ENQUEUE- FILA - FIFO
void cadastrarPaciente(){
    char buffer[20];
    struct Atendimento *novo = (struct Atendimento*)malloc(sizeof(struct Atendimento));
    if(novo == NULL){
        printf("Erro ao alocar memoria.\n");
        return;
    }
    printf("\nNome:");
    fgets(novo->nome, 49, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("\nIdade: ");
    fgets(buffer, sizeof(buffer), stdin);
    novo->idade = atoi(buffer);
    do{
    if(novo->idade < 0){
        printf("Idade invalida\nDigite novamente\n");
        scanf("%d",&novo->idade);

    }}while(novo->idade < 0);
    

    printf("\nDescricao:");
    fgets(novo->descricao, 99, stdin);

    novo->prox = NULL;

    if(inicio == NULL){
        inicio = novo;
        fim = novo;
    }else{
        fim->prox = novo;
        fim = novo;
    }
    printf("\nPaciente adicionado na fila!\n");
}
//DEQUEUE - FILA - FIFO
void atenderPaciente(){
    if(inicio == NULL){
        printf("Fila vazia.\n");
        return;
    }
    struct Atendimento *temp = inicio;

    inicio = temp->prox;
    if(inicio == NULL){
        fim = NULL;
    }

    printf("\nPaciente atendido!\n");
    printf("Nome: %s | Idade: %d | Desc: %s", temp->nome, temp->idade, temp->descricao);

    adicionarHistorico(temp);//Push dentro do Dequeue

    printf("\nPaciente adicionado ao historico.\n");
}

void mostrarFila(){
    if(inicio == NULL){
        printf("Fila vazia.\n");
        return;
    }

    struct Atendimento *atual = inicio;

    while(atual != NULL){
        printf("Nome: %s | Idade: %d | Desc: %s\n", atual->nome, atual->idade, atual->descricao);

        atual = atual->prox;
    }
}



void mostrarHistorico(){
    struct Atendimento *atual = topo;
    if (topo == NULL)
    {
        printf("Historico vazio\n");
        return;
    }
    while(atual != NULL){
        printf("Nome: %s | Idade: %d | Desc: %s\n", atual->nome, atual->idade, atual->descricao);
        atual = atual->prox;
         
    }
     printf("\n");
}   

//BUSCAR
void buscarAtendimento() { 
    char nome[50];
    Atendimento* atual = topo;
    int encontrado = 0;

    printf("\nDigite o nome para busca: ");
    fgets(nome, 49, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("\nEncontrado:\n");
            printf("Nome: %s | Idade: %d | Desc: %s\n",
                   atual->nome, atual->idade, atual->descricao);
            encontrado = 1;
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("\nNenhum atendimento encontrado.\n");
    }
}

//LIBERAR MEMORIA
void liberarHistorico() {//PILHA - LIFO
    Atendimento* temp;
    while (topo != NULL) {
        temp = topo;
        topo = topo->prox;
        free(temp);
    }
}
void liberarFila(){//FILA - FIFO
    Atendimento *temp;
    while(inicio != NULL){
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
    fim = NULL;
}


//INTERFACE
void run_interface(void) {
    int opt;
    int c;

    while (1) {

        printf("\n=== Sistema de Atendimento ===\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Atender paciente\n");
        printf("3 - Mostrar historico\n");
        printf("4 - Buscar atendimento\n");
        printf("5 - Mostrar fila\n");
        printf("6 - Remover historico\n");
        printf("7 - Sair\n");
        printf("\nOpcao: ");
        fflush(stdout);

        c = getchar();

        if (c == '\n') continue;

        while (getchar() != '\n');

        opt = c - '0';

        switch (opt) {
            case 1:
                cadastrarPaciente();
                break;

            case 2:
                atenderPaciente(); // simula atendimento (FIFO)
                break;

            case 3:
                mostrarHistorico();
                break;

            case 4:
                buscarAtendimento();
                break;

            case 5:
                mostrarFila();
                break;
            case 6:
                retirarHistorico();
                break;
            case 7:
                printf("\nSair? (S/N): ");
                fflush(stdout);
                c = getchar();
                while (getchar() != '\n');

                if (c == 's' || c == 'S') {
                    liberarHistorico();
                    liberarFila();
                    printf("\nEncerrando sistema...\n");
                    return;
                }
                break;

            default:
                printf("\nOpcao invalida.\n");
        }
    }
}

//MAIN
int main() {
    run_interface();
    return 0;
}