#ifndef STACKINTERFACE_H_INCLUDED
#define STACKINTERFACE_H_INCLUDED

#include "StackTypes.h"

extern void InitializeStack(Stack *S);
extern int  EmptyStack(Stack *S);
extern int  FullStack(Stack *S);
extern void Push(ItemTypeStack X, Stack *S);
extern void Pop(Stack *S, ItemTypeStack *X);

#endif
