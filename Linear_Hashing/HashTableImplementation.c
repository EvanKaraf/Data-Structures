#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HashTableTypes.h"
#define MAX 300000
#define OVERFLOW 2.4
#define EmptyKey "0"
#define STARTSZ 4
#define HASH 1
#define REHASH -1

/*int h(Key key,int noSegment) {
    int c = 1;
    int M = 16411; //16411
    int result = ((key*c)%M)%(STARTSZ << noSegment);            Function for integers
    return result;
}*/

int h(char A[100],int noSegment){
    int h=0, a=127;
    char *K;
    K = A;
    for (; *K!='\0'; K++)
            h = (a*h + *K) % (STARTSZ << noSegment);
    return h;
}

/*Initializes given hash table for use.*/
void InitializeTable(Table *T) {
    int i;
    T->p = 0;
    T->doubles = 0;
    T->loadFactor = 0.0;
    T->buckets = STARTSZ;
    T->entriesCount = 0;
    T->TableArray = malloc(MAX * sizeof(TableEntry));
    for (i=0; i<MAX; i++) {
        strcpy(T->TableArray[i].key,EmptyKey);
        T->TableArray[i].L = NULL;
        T->TableArray[i].LEnd = NULL;
    }
}
/*Searches for a given key. Finds initial hash address.
/If the bucket at adress has been split find new address
/to check whether key has been rehashed or not.
/When final address is retrieved search there.*/
int SearchHash(Table T,char key[100]){
    int i = h(key,T.doubles);
    if (i < T.p){
        i = h(key,T.doubles+1);
    }
    if (T.TableArray[i].L == NULL){
        if (strcmp(T.TableArray[i].key,key))
            return -1;  /*Not found! */
    }
    else{
        ListNode* temp;
        temp = T.TableArray[i].L;
        while (temp){
            if (!strcmp(temp->Entry.key,key)){
                return i;
            }
            temp = temp->next;
        }
        return -1;
    }
    return i;  /*In case it is the only item in the bucket. */
}
/*Inserts given node to given bucket.*/
void InsertList(TableEntry *T,ListNode* NodeToInsert) {
    if (T->L==NULL) {
        T->L = NodeToInsert;
        NodeToInsert->next = NULL;
        T->LEnd = NodeToInsert;
    } else {
        T->LEnd->next = NodeToInsert;
        NodeToInsert->next = NULL;
        T->LEnd = T->LEnd->next;
    }
}
/*Removes given node from given list.*/
void RemoveListNode(ListNode** L,ListNode** LEnd,ListNode* NodeToRemove) {
    ListNode* temp;
    temp = *L;
    if (*L == NodeToRemove) {
        *L = (*L)->next;
        if (*L == NULL)
            *LEnd = NULL;
        free(NodeToRemove);
        return;
    }
    while(temp->next!= NodeToRemove) {
        temp = temp->next;
    }
    if (temp->next == *LEnd) {
        free(temp->next);
        temp->next = NULL;
        *LEnd = temp;
    } else {
        temp->next = temp->next->next;
        free(NodeToRemove);
    }
}
/*Resets given entry meaning that either clears its list
/or pushes back an entry from list to bucket's starting entry.*/
void ResetTableEntry(TableEntry *Entry) {
    if (Entry->L == NULL) {
        strcpy(Entry->key,EmptyKey);
    } else {
        TableEntry * temp;
        temp =  &(Entry->L->Entry);
        RemoveListNode(&(Entry->L),&(Entry->LEnd),Entry->L);
        Entry = temp;
    }

}
/*Rehashes given table. Splits T->p bucket. Traverse through
all entries of the T->p bucket and decide if their position will be changed.
If yes reposition them. */
int ReHash(Table *T) {
    int i;
    int oldPos;
    if (strcmp(T->TableArray[T->p].key,EmptyKey)) {														/*If there is some key in the initial entry of the bucket decide repositioning.*/
        oldPos = h(T->TableArray[T->p].key,T->doubles);
        i = h(T->TableArray[T->p].key,T->doubles+1);
        if (i!= oldPos) {
            HashInsert(T,T->TableArray[T->p].key,T->TableArray[T->p].data,REHASH);
            ResetTableEntry(&(T->TableArray[T->p]));
        }
    }
    if (T->TableArray[T->p].L != NULL) {																/*If list exists,traverse through it and decide repositioning */
        ListNode* temp;
        ListNode* keep;
        temp = T->TableArray[T->p].L;
        while (temp) {
            oldPos = h(temp->Entry.key,T->doubles);
            i=h(temp->Entry.key,T->doubles+1);
            keep = temp->next;
            if (oldPos != i) {
                HashInsert(T,temp->Entry.key,temp->Entry.data,REHASH);
                RemoveListNode(&(T->TableArray[T->p].L),&(T->TableArray[T->p].LEnd),temp);
            }
            temp = keep;
        }
    }
}
/*Hashes given key.Returns either position or a default value when a rehash is needed.*/
int HashInsert(Table *T,char key[100],char D[20],int mode) {
    int i;
    if (mode == REHASH)																					/*If it's called for rehashing find the appropriate address in next segment.*/
        i = h(key,T->doubles+1);
    if (mode == HASH){
        i = h(key,T->doubles);
        T->entriesCount++;
        T->loadFactor = T->entriesCount/(double)T->buckets;
    }
    if (strcmp(T->TableArray[i].key,EmptyKey)) {
        ListNode* NewEntry;
        NewEntry = malloc(sizeof(ListNode));
        if (NewEntry == NULL) printf("malloc");
        strcpy(NewEntry->Entry.key,key);
        strcpy(NewEntry->Entry.data,D);
        InsertList(&(T->TableArray[i]),NewEntry);
    } else {
        strcpy(T->TableArray[i].key,key);
        strcpy(T->TableArray[i].data,D);
    }
    if (mode == HASH){																					/*If it's called for hash check for overflow and act accordingly.*/
        if (T->loadFactor > OVERFLOW) {
            T->buckets++;
            ReHash(T);
            T->p++;
            if (T->p % (STARTSZ << T->doubles) == 0) {
                T->doubles++;
                T->p = 0;
            }
            return -1;
        }
    }
    return i;
}
