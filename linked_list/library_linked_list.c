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

void InsertEnd(book **start, book **end) {//Insert a node in the end of the list
    book *new = (book *)malloc(sizeof(book));//Allocating memory for book node
    //Data Insertion
    printf("Insert the book's name:");
    getchar();
    scanf("%[^\n]",new->name);
    printf("Insert the book's ID:");
    scanf("%i", &new->id);
    getchar();
    printf("Insert book's author:");
    scanf("%[^\n]",new->author);
    if(*start==NULL) { //Empty list 
        *start = new;
        *end = new;
        new->next = NULL;
    }
    else {//List is not empty
        (*end)->next=new;
        *end = new;
        (*end)->next = NULL;
    }
}

void InsertStart(book **start) {//Insert node in the beggining of the list
    book *new = (book *)malloc(sizeof(book));//Allocating memory for book node
    //Data Insertion
    printf("Insert the book's name:");
    getchar();
    scanf("%[^\n]",new->name);
    printf("Insert the book's ID:");
    scanf("%i", &new->id);
    getchar();
    printf("Insert book's author:");
    scanf("%[^\n]",new->author);
    new->next=*start;
    *start=new;
}

void PrintListNodes(book *start) {//printint nodes of the list
    puts("--------------------OUR BOOKS-----------------");
    book *aux = start;//aux node
    while(aux!=NULL) {
        printf("\nID: %i|", aux->id);
        printf("Name: %s|", aux->name);
        printf("Author: %s\n", aux->author);
        puts("------------------------------------------");
        aux=aux->next;
    }
}

void DeleteNode(int id, book **start) {//Excludes a node from the list
    book *aux,*ant;
    aux = *start;
    if(*start==NULL)
        printf("List is empty!");
    while(aux->id!=id && aux->next!=NULL) {
        ant = aux;
        aux = aux->next;
    }
    if(aux->id==id && aux->next!=NULL) {
        ant->next = aux->next;
        free(aux);
    }
    else if(aux->id==id && aux->next==NULL) {
        ant->next=NULL;
        free(aux);
    }
    else
        puts("Theres no book with this ID!");
}

int main() {
    int op=0,n=0,id;
    //Pointers of the list
    book *start=NULL,*end=NULL, *aux=NULL;
    do {//Menu
        puts("\n---------------------LIBRARY--------------------------------");
        puts("1)Insert book");
        puts("2)Consult books");
        puts("3)Exclude book");
        puts("4)EXIT");
        puts("---------------------------------------------------------------");
        printf("CHOOSE:");
        scanf("%i",&op);
        switch (op){
        case 1:
            InsertEnd(&start,&end);
            puts("Insert with sucess");
            pause();
            break;
        case 2:
            PrintListNodes(start);
            pause();
            break;
        case 3:
            printf("\nInsert the ID of the book you want to delete:");
            scanf("%i",&id);
            DeleteNode(id,&start);
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