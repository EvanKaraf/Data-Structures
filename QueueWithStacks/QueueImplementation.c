/* This is the file QueueImplementation.c */

#include <stdio.h>
#include <stdlib.h>
#include "QueueInterface.h"


void InitializeQueue(Queue *Q)
{
    (Q->First).ItemList = NULL;
    (Q->Secondary).ItemList = NULL;
}

int EmptyQueue(Queue *Q)
{
   return((Q->First).ItemList == NULL);
}

int FullQueue(Queue *Q)
{
   return(0);
}
/* We assume an already constructed queue */
/* is not full since it can potentially grow */
/* as a linked structure.                   */

void Insert(ItemType R, Queue *Q)
{
    Push(R,&(Q->First));
    printf("Inserted %c\n",R);
}


void Remove(Queue *Q, ItemType *F)
{
    ItemType *X;
    X = malloc(sizeof(ItemType));

    if ((Q->First).ItemList == NULL){
        printf("attempt to remove item from an empty queue");
    }
    else {
        while(!Empty(&(Q->First))){
            Pop(&(Q->First),X);
            Push(*X,&(Q->Secondary));
        }
        Pop(&(Q->Secondary),X);
        printf("Removed %c\n",*X);
        while(!Empty(&(Q->Secondary))){
            Pop(&(Q->Secondary),X);
            Push(*X,&(Q->First));
        }
    }
    free(X);
}
