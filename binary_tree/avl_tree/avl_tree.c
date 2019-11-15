#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    int num, altd, alte;
    struct node *esq, *dir;
}avl;

void rotacao_esquerda(avl **aux)
{
    avl *aux1, *aux2;
    aux1 = (*aux)->dir;
}

void inserir(avl **aux, int num)
{
    avl *novo;
    if(*aux == NULL)
    {
        novo = malloc(sizeof(avl));
        novo->num = num;
        novo->alte = 0;
        novo->altd = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *aux = novo;
    }
    else if(num < (*aux)->num)
    {
        inserir(&(*aux)->esq, num);
        if((*aux)->esq->altd > (*aux)->esq->alte)
            (*aux)->alte = (*aux)->esq->altd +1;
        else
            (*aux)->alte = (*aux)->esq->alte +1;
        aux = 
        
    }
}


int main()
{

}