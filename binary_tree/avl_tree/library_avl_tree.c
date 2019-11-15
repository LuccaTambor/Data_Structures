#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//Estrutura Abstrata do livro
typedef struct biblio
{
    char nome[100],autor[100];
    int id, disp,altd,alte;
    struct biblio *esq,*dir;
}livro;

//Estrutura do cliente
typedef struct node
{
    char nome[100];
    int cpf, livros[2];
    struct node *prox;
}cliente;

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
    puts("\nPRESSIONE ENTER PARA CONTINUAR.......");
    getchar();
    getchar();
}

//Essa função realiza a rotação de dado node da árvore, para a esquerda.
livro *rotacao_esquerda(livro *aux)
{
    livro *aux1, *aux2;
    aux1 = aux->dir;
    aux2 = aux1->esq;
    aux->dir = aux2;
    aux1->esq = aux;
    if(aux->dir == NULL)
        aux->altd = 0;
    else if(aux->dir->alte > aux->dir->altd)
        aux->altd = aux->dir->alte+1;
    else
        aux->altd = aux->dir->altd+1;

    if(aux1->esq->alte > aux1->esq->altd)
        aux1->alte = aux1->esq->alte+1;
    else
        aux1->alte = aux1->esq->altd+1;
    return aux1;
}

//Essa função realiza a rotação de dado node da árvore, para a direita.
livro *rotacao_direita(livro *aux)
{
    livro *aux1, *aux2;
    aux1 = aux->esq;
    aux2 = aux1->dir;
    aux->esq = aux2;
    aux1->dir = aux;
    if(aux->esq == NULL)
        aux->alte = 0;
    else if(aux->esq->alte > aux->esq->altd)
        aux->alte = aux->esq->alte+1;
    else
        aux->alte = aux->esq->altd+1;

    if(aux1->dir->alte > aux1->dir->altd)
        aux1->altd =    aux1->dir->alte+1;
    else
        aux1->altd =    aux1->dir->altd+1;
    return aux1;
}

//A função abaixo acha a diferença entre as alturas do node, caso seja diferente de 1,-1 ou 0, então ele irá realizar
//uma rotação simples ou dupla
livro *balanceamento(livro *aux)
{
    int d, df;
    d = aux->altd - aux->alte;//achando a diferença de altura
    if(d == 2)
    {
        df = aux->dir->altd - aux->dir->alte;//diferença de altura do filho
        if(df >= 0)
            aux = rotacao_esquerda(aux);//rotação simples a esquerda
        else
        {
            //rotação dupla direita esquerda
            aux->dir = rotacao_direita(aux->dir);
            aux = rotacao_esquerda(aux);
        }
    }
    else if(d == -2)
    {
        df = aux->esq->altd - aux->esq->alte;
        if(df <= 0)
            aux = rotacao_direita(aux);//rotação simples a direita
        else
        {
            //rotação dupla esquerda direita
            aux->esq = rotacao_esquerda(aux->esq);
            aux = rotacao_direita(aux);
        }
    }
    return aux;
}

//Função insere um node livro na arvore, caso ela esteja desbalanceada, chama a função balancear
livro *insere(livro *aux, int id)
{
    livro *novo;//Instanciando o novo livro
    if(aux == NULL)
    {
        //Inserindo seus dados
        novo = malloc(sizeof(livro));
        novo->id = id;
        novo->disp = 1;
        printf("Insira o nome do Livro:");
        getchar();
        scanf("%[^\n]",novo->nome);
        getchar();
        printf("Insira o autor do Livro:");
        scanf("%[^\n]",novo->autor);
        //Zerando seus ponteiros e alturas
        novo->altd = 0;
        novo->alte = 0;
        novo->dir = NULL;
        novo->esq = NULL;
        aux = novo;
    }
    else if(id < aux->id)//Caso id seja menor que o da raiz
    {
        aux->esq = insere(aux->esq, id);
        if(aux->esq->altd > aux->esq->alte)
            aux->alte = aux->esq->altd+1;
        else
            aux->alte = aux->esq->alte+1;
        aux = balanceamento(aux);
    }
    else//caso o id seja maior que o da raiz
    {
        aux->dir = insere(aux->dir, id);
        if(aux->dir->altd > aux->dir->alte)
            aux->altd = aux->dir->altd+1;
        else 
            aux->altd = aux->dir->alte+1;
        aux = balanceamento(aux);
    }
    return aux;
}

//Funções que imprimen a árvore de livros em Ordem, PreOrdem e PosOrdem, respectivamente, mas apenas se o livro estiver
//Disponível na biblioteca, ou seja, não está emprestado
void Ordem(livro *raiz)
{
	if(raiz != NULL)
	{
		Ordem(raiz->esq);
        if(raiz->disp == 1)
        {
            printf("\nID do livro: %i|", raiz->id);
            printf("Nome do Livro: %s|", raiz->nome);
            printf("Autor do livro: %s\n", raiz->autor);
            puts("------------------------------------------");
        }
		Ordem(raiz->dir);
	}
}

void PreOrdem(livro *raiz)
{
	if(raiz != NULL)
	{
		if(raiz->disp == 1)
        {
            printf("\nID do livro: %i|", raiz->id);
            printf("Nome do Livro: %s|", raiz->nome);
            printf("Autor do livro: %s\n", raiz->autor);
            puts("------------------------------------------");
        }
		PreOrdem(raiz->esq);
		PreOrdem(raiz->dir);
	}
}

void PosOrdem(livro *raiz)
{
	if(raiz != NULL)
	{
		PosOrdem(raiz->esq);
		PosOrdem(raiz->dir);
		if(raiz->disp == 1)
        {
            printf("\nID do livro: %i|", raiz->id);
            printf("Nome do Livro: %s|", raiz->nome);
            printf("Autor do livro: %s\n", raiz->autor);
            puts("------------------------------------------");
        }
	}
}

//A função abaixo remove um livro dado um ID da arvore e realiza as substituições para manter o balanceamento da arvore
livro *remover(livro *aux, int id)
{
    livro *p, *p2;
    if(aux->id == id)
    {
        if(aux->disp == 1)
        {
            if(aux->esq == aux->dir)//o elemento não tem filhos
            {
                free(aux);
                return NULL;
            }
            else if(aux->esq == NULL)//o elemento não tem filho a esquerdas
            {
                p = aux->dir;
                free(aux);
                return p;
            }
            else if(aux->dir == NULL)//o elemento não tem filho a direita
            {
                p = aux->esq;
                free(aux);
                return p;
            }
            else//o elemento tem ambos os filhos
            {
                p2 = aux->dir;
                p = aux->dir;
                while(p->esq != NULL)
                    p = p->esq;
                p->esq = aux->esq;
                free(aux);
                return p2;
            }
        }
        else
            puts("O livro não está disponível!");
    }
    else if(aux->id < id)   
        aux->dir = remover(aux->dir, id);
    else
        aux->esq = remover(aux->esq, id);
    return aux;
}

//busca um livro na arvore
livro *busca(livro *raiz, int id)
{
    livro *no = raiz;
    if(no->id == id)
        return no;
    else
    {
        if(no->id > id)
            no = busca(no->esq, id);
        else
            no = busca(no->dir, id);   
    }
}

//A função abaixo cadatra um cliente e o armazena em uma lista comumm
void cadastraCliente(cliente **inicio, cliente **fim)
{
    cliente *novo = malloc(sizeof(cliente));
    printf("Insira o nome do cliente:");
    getchar();
    scanf("%[^\n]", novo->nome);
    getchar();
    printf("Insira o CPF do cliente:");
    scanf("%i", &novo->cpf);
    novo->livros[0] = novo->livros[1] = 0;//O cliente não tem nenhum livro emprestado com ele;
    novo->prox = NULL;
    if(*inicio == NULL)
    {
        *inicio = novo;
        *fim = novo;
    }
    else
    {
        (*fim)->prox = novo;
        *fim = novo;
    }
    puts("Cadastro concluido!!");
}

void emprestimo(livro *raiz, cliente *inicio,int cpf)
{
    cliente *aux = inicio;
    livro *l = NULL;
    while(aux!=NULL && aux->cpf != cpf)
        aux = aux->prox;
    if(aux!=NULL)
    {
        if(aux->livros[1] != 0)
            puts("Esse cliente já possui o limite de livros!");
        else
        {
            int id;
            puts("--LIVROS DISPONÍVEIS--");
            Ordem(raiz);
            printf("Insira o ID do livro que irá ser emprestado:");
            scanf("%i",&id);
            l = busca(raiz, id);
            if(l->disp==1)
            {
                if(aux->livros[0] == 0)
                    aux->livros[0] = l->id;
                else
                    aux->livros[1] = l->id;
                l->disp = 0;
                printf("\nLivro %s retirado por %s!!",l->nome,aux->nome);
            }
            else
            {
                puts("ESSE LIVRO NÃO ESTÁ DISPONÍVEL!!!");
            }
        }
    }
    else
    {
        puts("Esse cliente não existe!");
    } 
}

void devolucao(livro *raiz, cliente *inicio, int cpf)
{
    cliente *aux = inicio;
    livro *l = NULL;
    int id;
    while(aux!=NULL && aux->cpf != cpf)
        aux = aux->prox;
    if(aux!=NULL)
    {
        if(aux->livros[0] == 0 && aux->livros[1] == 0)//Vendo se o cliente tem algum livro em seu nome
            printf("Esse cliente não tem nenhuma livro retirado!");
        else
        {
            printf("Livros emprestados a %s: %i %i",aux->nome, aux->livros[0],aux->livros[1]);
            printf("\nQual dos livros está sendo devolvido:");
            scanf("%i",&id);
            if(id == aux->livros[0] || id == aux->livros[1])//Verificando se o ID é um dos livros no nome do cliente
            {
                l = busca(raiz,id);
                l->disp = 1;
                printf("Livro %s devolvido!", l->nome);
                //tirando Id do livro do vetor do cliente na posição certa
                if(id == aux->livros[1])
                    aux->livros[1] = 0;
                else if(id == aux->livros[0] && aux->livros != 0)
                {
                    aux->livros[0] = aux->livros [1];
                    aux->livros[1] = 0;
                }   
            }
            else
                printf("O usuário nem tem esse livro em seu nome!");
        }
    }
    else
        puts("Esse cliente não existe!");
}

void mostraClientes(cliente *inicio)//Imprimindo os clientes da lista
{
    puts("--------------------CLIENTES CADASTRADOS-----------------");
    cliente *aux = inicio;//Usando um node auxiliar
    if(inicio == NULL)
        puts("Lista vazia");
    else
    {
        while(aux!=NULL)
        {
            printf("\nNome: %s|", aux->nome);
            printf("CPF: %i|", aux->cpf);
            if(aux->livros[1] == 0 && aux->livros[0] == 0)
                printf("sem livros emprestados");
            else
                printf("ID dos livros emprestados: %i %i", aux->livros[0],aux->livros[1]);
            puts("------------------------------------------");
            aux=aux->prox;
        }
    }
}

int main()
{
    int op=0,n=0,id,cpf;
    //Declarando a raiz da árvore
    livro *raiz = NULL;
    //Declarando inicio e fim da lista de clientes
    cliente *inicio = NULL, *fim = NULL;
    do//Loop do menu de opções
    {
        
        puts("\n---------------------BIBLIOTECA--------------------------------");
        puts("1)Inserir Livro");
        puts("2)Consultar Disponíveis Livros em Ordem");
        puts("3)Consultar Disponíveis Livros em PreOrdem");
        puts("4)Consultar Disponíveis Livros em PosOrdem");
        puts("5)Excluir Livro da biblioteca");
        puts("6)Cadastrar Cliente");
        puts("7)Mostrar Clientes Cadastrados");
        puts("8)Empréstimo de livro");
        puts("9)Devolução de livro");
        puts("10)SAIR");
        puts("---------------------------------------------------------------");
        printf("ESCOLHA:");
        scanf("%i",&op);
        switch (op)
        {
        case 1:
            printf("Insira o id do Livro:");
            scanf("%i",&id);
            raiz = insere(raiz,id);//Manda o endereço do topo da pilha
            puts("Inserido com Sucesso");
            pause();
            break;
        case 2:
            Ordem(raiz);
            pause();
            break;
        case 3:
            PreOrdem(raiz);
            pause();
            break;
        case 4:
            PosOrdem(raiz);
            pause();
            break;
        case 5:
            printf("Insira o Id do Livro que deseja deletar:");
            scanf("%i",&id);
            raiz = remover(raiz,id);
            pause();
            break;
        case 6:
            cadastraCliente(&inicio,&fim);
            pause();
            break;
        case 7:
            mostraClientes(inicio);
            pause();
            break;
        case 8:
            mostraClientes(inicio);
            printf("Insira o cpf no cliente desejado:");
            scanf("%i",&cpf);
            emprestimo(raiz,inicio,cpf);
            pause();
            break;
        case 9:
            mostraClientes(inicio);
            printf("Insira o cpf no cliente desejado:");
            scanf("%i",&cpf);
            devolucao(raiz,inicio,cpf);
            pause();
            break;
        case 10:
            break;
        default:
            op = 0;
            break;
        }
        clear();
    }while(op!=10);
}