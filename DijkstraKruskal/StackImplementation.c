#include <stdio.h>
#include <stdlib.h>
#include "StackInterface.h"

void InitializeStack(Stack *S) {
    S->ItemList=NULL;
}

int EmptyStack(Stack *S) {
    return (S->ItemList==NULL);
}

int FullStack(Stack *S) {
    return 0;
}
/* We assume an already constructed stack is not full since it can potentially */
/* grow as a linked structure  */

void Push(ItemTypeStack X, Stack *S) {
    StackNode *Temp;

    Temp=(StackNode *) malloc(sizeof(StackNode));

    if (Temp==NULL) {
        printf("system storage is exhausted");
    } else {
        Temp->Link=S->ItemList;
        Temp->Item=X;
        S->ItemList=Temp;
    }
}


void Pop(Stack *S, ItemTypeStack *X) {
    StackNode *Temp;

    if (S->ItemList==NULL) {
        printf("attempt to pop the empty stack");
    } else {
        Temp=S->ItemList;
        *X=Temp->Item;
        S->ItemList=Temp->Link;
        free(Temp);
    }
}
