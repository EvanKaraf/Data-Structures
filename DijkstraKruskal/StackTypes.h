#ifndef STACKTYPES_H_INCLUDED
#define STACKTYPES_H_INCLUDED

typedef int ItemTypeStack;


typedef struct StackNodeTag {
           ItemTypeStack Item;
           struct StackNodeTag *Link;
        } StackNode;

typedef struct {
           StackNode *ItemList;
        } Stack;

#endif
