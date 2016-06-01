/* This is the file StackInterface.h */
#include "StackTypes.h"

extern void InitializeStack(Stack *S);
extern int Empty(Stack *S);
extern int Full(Stack *S);
extern void Push(int row,int column,int neighbors,Stack *S);
extern void Pop(Stack *S, int *row,int *column,int* neighbors);
