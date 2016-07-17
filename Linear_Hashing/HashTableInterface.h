#ifndef HASHTABLEINTERFACE_H_INCLUDED
#define HASHTABLEINTERFACE_H_INCLUDED
#include "HashTableTypes.h"

int h(char K[100],int noSegment);
void InitializeTable(Table *T);
int SearchHash(Table T,KeyType key);
void InsertList(TableEntry *T,ListNode* NodeToInsert);
void ResetTableEntry(TableEntry *Entry);
void RemoveListNode(ListNode** L,ListNode** LEnd,ListNode* NodeToRemove);
void ReHash(Table *T);
int HashInsert(Table *T,KeyType key,char D[20],int mode);


#endif
