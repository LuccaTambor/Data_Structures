#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

//Estrutura da fila de prioridade, duplamente encadeada
typedef struct node
{
    int id,prioridade,tempo,atendimento;
    char nome[100];
    struct node *prox,*ant;
}fila;

//Função de limpar tela
void clear()
{
    #ifdef WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
}

//Função que pausa o programa até o usuário pressionar ENTER
void pause()
{
    puts("PRESSIONE ENTER PARA CONTINUAR.......");
    getchar();
    getchar();
}

void insereOrdenado(fila **fim, fila **inicio)//Coloca um cliente no final da fila, não levando em conta a prioridade
{
    fila *novo = malloc(sizeof(fila)); 
    fila *aux = * inicio;
    //Inserindo os dados no node
    printf("Insira o nome do cliente:");
    getchar();
    scanf("%[^\n]",novo->nome);
    getchar();
    printf("Insira o Id:");
    scanf("%i",&novo->id);
    printf("Insira a prioridade do cliente:");
    scanf("%i",&novo->prioridade);
    int a = 5 + rand() % 55;
    novo->tempo = a;
    novo->atendimento = 1;
    if(*inicio==NULL)//Caso a fila esteja vazia
    {
        *inicio = novo;
        *fim = novo;
        novo->prox =NULL;
        novo->ant = NULL;
    }
    else//Há clientes na fila já
    {
        while(aux != NULL && aux->prioridade > novo->prioridade) 
            aux = aux->prox;
        if(*inicio == aux)
        { 
            novo->prox = *inicio;
            (*inicio)->ant = novo;
            novo->ant = NULL;
            *inicio = novo;
        }
        else if(aux == NULL) 
        {
            novo->ant = *fim;
            (*fim)->prox = novo;
            novo->prox = NULL;
            *fim = novo;
        }
        else
        { 
            novo->prox = aux;
            aux->ant->prox = novo;
            novo->ant = aux->ant;
            aux->ant = novo;
        }
    }
}

void printFP(fila **inicio)//Imprime a Fila de prioridade na ordem em que está 
{
    fila *aux = *inicio;
    if(aux==NULL)
        puts("A fila está vazia!");
    else
    {
        while(aux!=NULL)
        {
            printf("\n|Nome: %s | Id:%i | Prioridade:%i | Tempo:%i|\n",aux->nome,aux->id,aux->prioridade,aux->tempo);
            aux=aux->prox;
        }
    }
}

//Roda a fila, passando 5 de tempo, caso o cliente atendido não tenha seu tempo zerado ele volta pro final da fila
void rodada(fila **inicio, fila **fim)
{
    fila *cliente = *inicio;
    if(*inicio==NULL)
        puts("A Fila está vazia!");
    else
    {
        cliente->tempo = cliente->tempo - 5;
        if(cliente->atendimento > 1)
        {
            if(cliente->atendimento == 1)
                cliente->atendimento++;
            else if(cliente->atendimento == 2)
            {
                cliente->prioridade--;
                cliente->atendimento--;
            }
        }
        
        if(cliente->tempo>0)
        {
            *inicio = cliente->prox;

            fila *aux = *fim;
            if(*inicio==NULL)
            {
                *inicio = cliente;
                *fim = cliente;
                cliente->prox =NULL;
                cliente->ant =NULL;
            }
            else
            {
                while(aux !=NULL && cliente->prioridade > aux->prioridade)
                    aux = aux->ant;
                
                if(aux->prox == NULL)
                {
                    (*fim)->prox = cliente;
                    cliente->ant = *fim;
                    cliente->prox = NULL;
                    *fim = cliente;
                }
                else if(aux->ant == NULL)
                {
                    cliente->prox = *inicio;
                    (*inicio)->ant=cliente;
                    cliente->ant = NULL;
                    *inicio = cliente;
                }
                else
                {
                    cliente->ant = aux;
                    aux->prox->ant = cliente;
                    cliente->prox = aux->prox;
                    aux->prox = cliente;
                }
            }
        }
        else
        {
            *inicio = cliente->prox;
            free(cliente);
        }   
        puts("A Fila Andou");
    }   
}

int main()
{
    fila *inicio=NULL,  *fim=NULL;//Ponteiros marcadores da fila
    int op=0;
    //Menu de opções
    do
    {
        puts("\n---------------------GARÇOM-------------------------------");
        puts("1)Colocar na fila");
        puts("2)Executar até esvaziar a fila");
        puts("3)Consultar");
        puts("2)Executar uma rodada de atendimento");
        puts("5)SAIR");
        puts("---------------------------------------------------------------");
        printf("ESCOLHA:");
        scanf("%i",&op);
        switch (op)
        {
            case 1:
                insereOrdenado(&fim,&inicio);
                pause();
                break;
            case 2:
                while(inicio!=NULL)
                {
                    puts("-----------------------Fila-----------------");
                    printFP(&inicio);
                    rodada(&inicio,&fim);
                }
                pause();
                break;
            case 3:
                printFP(&inicio);
                pause();
                break;
            case 4:
                rodada(&inicio,&fim);
                printFP(&inicio);
                break;
            default:
                break;
        }
        clear();
    } while (op<=4);
    puts("O Bar fechou!");
}