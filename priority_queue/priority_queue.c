#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

//ADT
typedef struct node {
    int id,priority,time,attended;//attended is times a node has been in the start of the queue
    char name[100];
    struct node *prox,*ant;
}queue;

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

void Insertion(queue **end, queue **start) {//Insert in a position on the queue depending on the priority
    queue *new = malloc(sizeof(queue)); 
    queue *aux = * start;
    //Data Insertion
    printf("Insert name:");
    getchar();
    scanf("%[^\n]",new->name);
    getchar();
    printf("Insert ID:");
    scanf("%i",&new->id);
    printf("Insert the priority:");
    scanf("%i",&new->priority);
    int a = 5 + rand() % 55;//Generating a random time
    new->time = a;
    new->attended = 1;
    if(*start==NULL) {//Empry Queue
        *start = new;
        *end = new;
        new->prox =NULL;
        new->ant = NULL;
    }
    else {
        while(aux != NULL && aux->priority > new->priority) 
            aux = aux->prox;
        if(*start == aux) { 
            new->prox = *start;
            (*start)->ant = new;
            new->ant = NULL;
            *start = new;
        }
        else if(aux == NULL) {
            new->ant = *end;
            (*end)->prox = new;
            new->prox = NULL;
            *end = new;
        }
        else { 
            new->prox = aux;
            aux->ant->prox = new;
            new->ant = aux->ant;
            aux->ant = new;
        }
    }
}

void PrintQueue(queue **start) {//Prints all nodes of the queue in order
    queue *aux = *start;
    if(aux==NULL)
        puts("Empry Queue!");
    else {
        while(aux!=NULL) {
            printf("\n|name: %s | ID:%i | priority:%i | Time:%i|\n",aux->name,aux->id,aux->priority,aux->time);
            aux=aux->prox;
        }
    }
}

void Round(queue **start, queue **end) {
    queue *first = *start;//First node of the queue
    if(*start==NULL)//Queue is empty
        puts("Empry Queue!");
    else {
        first->time = first->time - 5;//Reducing 5 on the time
        if(first->attended > 1) {//Verifing if it was attended more than two times
            if(first->attended == 1)//Attend only one time, just increment attended
                first->attended++;
            else if(first->attended == 2) {//Attended two times, reduce priority and attended
                first->priority--;
                first->attended--;
            }
        }
        
        if(first->time>0) {//Time is not over
            *start = first->prox;//The next node is now the first

            queue *aux = *end;//Auxiliar node
            if(*start==NULL) {
                *start = first;
                *end = first;
                first->prox =NULL;
                first->ant =NULL;
            }
            else {//Re-inserting the first node in the queue
                while(aux !=NULL && first->priority > aux->priority)
                    aux = aux->ant;
                
                if(aux->prox == NULL) {
                    (*end)->prox = first;
                    first->ant = *end;
                    first->prox = NULL;
                    *end = first;
                }
                else if(aux->ant == NULL) {
                    first->prox = *start;
                    (*start)->ant=first;
                    first->ant = NULL;
                    *start = first;
                }
                else {
                    first->ant = aux;
                    aux->prox->ant = first;
                    first->prox = aux->prox;
                    aux->prox = first;
                }
            }
        }
        else {//Time is over
            *start = first->prox;
            free(first);
        }   
        puts("A round has passed");
    }   
}

int main() {
    queue *start=NULL,  *end=NULL;//Queue pointers
    int op=0;
    //Menu 
    do {
        puts("\n-----------------PRIORITY QUEUE--------------------------");
        puts("1)Insert on queue");
        puts("2)Execute rounds until queue is empty");
        puts("3)Print Queue");
        puts("2)Execute one round");
        puts("5)EXIT");
        puts("---------------------------------------------------------------");
        printf("CHOOSE:");
        scanf("%i",&op);
        switch (op) {
            case 1:
                Insertion(&end,&start);
                pause();
                break;
            case 2:
                while(start!=NULL) {
                    puts("-----------------------QUEUE-----------------");
                    PrintQueue(&start);
                    Round(&start,&end);
                }
                pause();
                break;
            case 3:
                PrintQueue(&start);
                pause();
                break;
            case 4:
                Round(&start,&end);
                PrintQueue(&start);
                break;
            default:
                break;
        }
        clear();
    } while (op<=4);
    puts("Program end....");
}