/* This is the file StackImplementation.c */

#include <stdio.h>
#include <stdlib.h>
#include "StackInterface.h"

void InitializeStack(Stack *S)
{
   S->ItemList=NULL;
}

int Empty(Stack *S)
{
   return (S->ItemList==NULL);
}

int Full(Stack *S)
{
  return 0;
}
/* We assume an already constructed stack is not full since it can potentially */
/* grow as a linked structure  */

void Push(int row,int column,int neighbors,Stack *S)
{
   StackNode *Temp;

   Temp=(StackNode *) malloc(sizeof(StackNode));

   if (Temp==NULL){
      printf("system storage is exhausted");
   } else {
      Temp->Link = S->ItemList;
      Temp->Row = row;
      Temp->Column = column;
      Temp->Neighbors = neighbors;
      S->ItemList = Temp;
   }
}


void Pop(Stack *S, int *row,int *column,int *neighbors)
{
   StackNode *Temp;

   if (S->ItemList==NULL){
     printf("attempt to pop the empty stack");
   } else {
      Temp=S->ItemList;
      *row = Temp->Row;
      *column = Temp->Column;
      *neighbors = Temp->Neighbors;
      S->ItemList=Temp->Link;
      free(Temp);
   }
}
