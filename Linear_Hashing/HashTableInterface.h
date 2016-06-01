#ifndef HASHTABLEINTERFACE_H_INCLUDED
#define HASHTABLEINTERFACE_H_INCLUDED
#include "HashTableTypes.h"

int h(char K[100],int noSegment);
void InitializeTable(Table *T);
int SearchHash(Table T,char key[100]);
void InsertList(TableEntry *T,ListNode* NodeToInsert);
void ResetTableEntry(TableEntry *Entry);
void RemoveListNode(ListNode** L,ListNode** LEnd,ListNode* NodeToRemove);
int ReHash(Table *T);
int HashInsert(Table *T,char key[100],char D[20],int mode);


#endif
