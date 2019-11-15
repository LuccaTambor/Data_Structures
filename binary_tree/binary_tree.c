#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct node
{
    int num;
    struct node *esq, *dir;
}arv;

void insereArv(arv **aux, int num)
{
	if(*aux == NULL)
	{
		*aux = malloc(sizeof(arv));
		(*aux)->num = num;
		(*aux)->esq = NULL;
		(*aux)->dir = NULL;
	}
	else
	{
		if(num > (*aux)->num)
			insereArv(&(*aux)->dir , num);
		else if(num < (*aux)->num)
			insereArv(&(*aux)->esq , num);
	}	
}

void Ordem(arv *raiz)
{
	if(raiz != NULL)
	{
		Ordem(raiz->esq);
		printf("%i ", raiz->num);
		Ordem(raiz->dir);
	}
}

void PreOrdem(arv *raiz)
{
	if(raiz != NULL)
	{
		printf("%i ", raiz->num);
		PreOrdem(raiz->esq);
		PreOrdem(raiz->dir);
	}
}

void PosOrdem(arv *raiz)
{
	if(raiz != NULL)
	{
		PosOrdem(raiz->esq);
		PosOrdem(raiz->dir);
		printf("%i ", raiz->num);
	}
}

arv *buscaNo (arv *raiz, int num, arv **pai)
{
	arv *atual = raiz;
	*pai = NULL;
	while(atual)
	{
		if(atual->num == num)
			return atual;
		*pai = atual;
		if(num < atual->num)
			atual = atual->esq;
		else
			atual = atual->dir;
	}
	return(NULL);
}

arv *removeNo(arv *raiz, int num){
    arv *pai, *no, *p, *q;
    //p apontará para o pai do nó que irá no lugar do nó removido que no caso será apontado pelo ponteiro q
    no = buscaNo(raiz, num, &pai);
    
    //se não existir o nó da árvore, ele retorna  o ponteiro da árvore sem alteração
    if(no == NULL) 
		return raiz;
    
    //caso o nó a ser removido tiver algum filho, q receberá o filho existente
    if(!no->esq || !no->dir)
        if(!no->esq) 
            q = no->dir;
        else 
            q = no->esq;
    else{ //caso ele tiver dois filhos
        //de padrão, o primeiro pai possivel de um possivel q será o do nó a ser removido
        p = no;
        //a regra de remoção é pegar o elemento mais a direita da sub-árvore a esquerda
        
        q = no->esq;//sub arvore esquerda
        while(q->dir){ //elemento a direita
            p = q;
            q = q->dir;
        }
        //tratamento do caso de p for diferente do nó a ser removido
        if(p != no){
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }
    //caso a remoção foi na raiz da árvore
    if(!pai)
	{
        free(no);
        return(q);
    }
    
    //teste para ver qual lado que terá que mexer de pai para apontar para o novo elemento
    if(pai->num < num) 
        pai->dir = q;
    else
        pai->esq = q;

    free(no);
    return raiz; 
}


int main()
{
    int i,num,op;
    arv *raiz=NULL;
	do
	{
		puts("-----MENU-----");
		puts("1)Inserir na árvore");
		puts("2)Ordem");
		puts("3)PreOrdem");
		puts("4)PosOrdem");
		puts("5)Remover nó");
		scanf("%i",&op);
		switch (op)
		{
		case 1:
			scanf("%i",&num);
			insereArv(&raiz, num);
		case 2:
			Ordem(raiz);
			printf("\n");
			break;
		case 3:
			PreOrdem(raiz);
			printf("\n");
			break;
		case 4:
			PosOrdem(raiz);
			printf("\n");
			break;
		case 5:
			puts("Insira o número do nó que deseja apagar:");
			int n;
			scanf("%i",&n);
			raiz = removeNo(raiz,num);
			break;
		default:
			break;
		}
	} while (op<=5);
	
	
}