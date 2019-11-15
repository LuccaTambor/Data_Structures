#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//Estrutura Abstrata do livro
typedef struct biblio
{
    char nome[100],autor[100];
    int id;
    struct biblio *prox;
}livro;

//Função que limpa a tela
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


//A função push coloca um livro no topo da pilha
void push(livro **topo)
{
    livro *novo = malloc(sizeof(livro));
    printf("Insira o nome do Livro:");
    getchar();
    scanf("%[^\n]",novo->nome);
    printf("Insira o Id do Livro:");
    scanf("%i", &novo->id);
    getchar();
    printf("Insira o autor do Livro:");
    scanf("%[^\n]",novo->autor);
    novo->prox=NULL;
    if(*topo==NULL)
        *topo = novo;
    else
    {
        novo->prox = *topo;
        *topo = novo; 
    }
}


//A função pop exclui o livro no topo da pilha
void pop(livro **topo)
{
    livro *aux = *topo;
    if(*topo==NULL)
        puts("Nenhum livro");
    else
    {
        *topo = aux->prox;
        free(aux);
    }
    puts("popped");
}

//Imprime todos os livros da pilha
void printS(livro **topo)
{
    livro *aux = *topo;
    if(*topo==NULL)
        puts("Nenhum Livro!");
    else
    {
        while(aux!=NULL)
        {
            printf("\nID do livro: %i|", aux->id);
            printf("Nome do Livro: %s|", aux->nome);
            printf("Autor do livro: %s\n", aux->autor);
            puts("------------------------------------------");
            aux=aux->prox;
        }
    }
}

int main()
{
    int op=0,n=0,id;
    //Declarando o topo da pilha
    livro *topo=NULL;
    do//Loop do menu de opções
    {
        
        puts("\n---------------------BIBLIOTECA--------------------------------");
        puts("1)Inserir Livro");
        puts("2)Consultar Livros");
        puts("3)Excluir Livro");
        puts("4)SAIR");
        puts("---------------------------------------------------------------");
        printf("ESCOLHA:");
        scanf("%i",&op);
        switch (op)
        {
        case 1:
            push(&topo);//Manda o endereço do topo da pilha
            puts("Inserido com Sucesso");
            pause();
            break;
        case 2:
            printS(&topo);
            pause();
            break;
        case 3:
            pop(&topo);
            pause();
            break;
        case 4:
            break;
        default:
            break;
        }
        clear();
    }while(op!=4);
}