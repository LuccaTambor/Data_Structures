#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//Book ADT
typedef struct lib {
    char name[100],author[100];
    int id;
    struct lib *next;
}book;

//Clean terminal
void clear() {
    #ifdef WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
}

//Pause script 
void pause() {
    puts("PRESS ENTER.......");
    getchar();
    getchar();
}

void push(book **top) {//Put a node on top of the stack
    book *new = malloc(sizeof(book));
    //Data Insertion
    printf("Insert the book's name:");
    getchar();
    scanf("%[^\n]",new->name);
    printf("Insert the book's ID:");
    scanf("%i", &new->id);
    getchar();
    printf("Insert book's author:");
    scanf("%[^\n]",new->author);
    new->next=NULL;
    if(*top==NULL)
        *top = new;
    else {
        new->next = *top;
        *top = new; 
    }
}

void pop(book **top) {//Excludes the top node of the stack
    book *aux = *top;
    if(*top==NULL)
        puts("Empty Stack!");
    else {
        *top = aux->next;
        free(aux);
    }
    puts("Popped");
}


void PrintStack(book **top) {//Imprime todos os books da pilha
    book *aux = *top;
    if(*top==NULL)
        puts("Empty Stack!");
    else {
        while(aux!=NULL) {
            printf("\nID: %i|", aux->id);
            printf("Name: %s|", aux->name);
            printf("Author: %s\n", aux->author);
            puts("------------------------------------------");
            aux=aux->next;
        }
    }
}

int main()
{
    int op=0,n=0,id;
    //Pointer for the top of the stack
    book *top=NULL;
    do {//menu
        puts("\n---------------------LIBRARY--------------------------------");
        puts("1)Insert book");
        puts("2)Consult books");
        puts("3)Exclude book");
        puts("4)EXIT");
        puts("---------------------------------------------------------------");
        printf("CHOOSE:");
        scanf("%i",&op);
        switch (op) {
        case 1:
            push(&top);//Manda o endereço do top da pilha
            puts("Pushed with Sucess!");
            pause();
            break;
        case 2:
            PrintStack(&top);
            pause();
            break;
        case 3:
            pop(&top);
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