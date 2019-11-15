#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct biblio
{
    char nome[100];
    int id;
    struct biblio *esq, *dir;
}livro;

void clear()
{
    #ifdef WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
}

livro *insereArv(int id, char nome[], livro *aux)
{
    if(aux==NULL)
    {
        aux = malloc(sizeof(livro));
        aux->id = id;
        aux->dir = NULL;
        aux->esq = NULL;
    }
    if(num > aux->num)
        return insereArv(num, aux->dir);
    if(num < aux->num)
        return insereArv(num, aux->esq);
    return aux;
}

int main()
{
    int op=0,n=0,id;
    //Declarando os ponteiros para manipulação da lista
    livro *biblioteca;
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
            InsereFim(&inicio,&fim);//Manda os endereços dos ponteiros de marcação
            puts("Inserido com Sucesso");
            getchar();
            getchar();
            break;
        case 2:
            Imprime(inicio);
            getchar();
            getchar();
            break;
        case 3:
            printf("\nInsira o ID do livro que deseja excluir:");
            scanf("%i",&id);
            Excluir(id,&inicio);
            getchar();
            getchar();
            break;
        case 4:
            break;
        default:
            break;
        }
        clear();
    }while(op!=4);
}