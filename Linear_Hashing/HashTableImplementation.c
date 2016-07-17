#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HashTableInterface.h"
#define OVERFLOW 2.4
#define EmptyKey "0"
#define EmptyData "0"
#define STARTSZ 4
#define HASH 1
#define REHASH -1

/*int h(Key key,int noSegment) {
    int c = 1;
    int M = 16411; //16411
    int result = ((key*c)%M)%(STARTSZ << noSegment);            Function for integers
    return result;
}*/

/*int searchAll(Table T){
    char key[100];
    char user_filename[150];
    int count = 0;
    printf("Enter filename to read from:\n");
    scanf("%s", user_filename);
    FILE *file=fopen(user_filename, "r");
    if (!file) {
        printf("Error opening file..\n");
        return -1;                                                                      For debugging purposes.
    }
    while (fscanf(file, "%s", key) == 1) {
        if (SearchHash(T,key) == -1){
            if(count == 0){
                printf("first key I couldn't find was %s\n\n",key);
            }
            count++;
        }
    }
    printf("Couldnt find %d keys",count);
}*/


/*Hash function. */
int h(char A[100],int round){
    int h=0, a=701;
    char *K;
    K = A;
    for (; *K!='\0'; K++)
            h = (a*h + *K) % (STARTSZ << round);
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
    T->TableArray = malloc(STARTSZ * sizeof(TableEntry));
    for (i=0; i<STARTSZ; i++) {
        strcpy(T->TableArray[i].key,EmptyKey);
        strcpy(T->TableArray[i].data,EmptyData);
        T->TableArray[i].L = NULL;
        T->TableArray[i].LEnd = NULL;
    }
}

/*Reallocates enough memory for one more segment. */
Table* extendTable(Table *T){
    int i;
    T->TableArray = realloc(T->TableArray,(STARTSZ<<(T->doubles+1))*sizeof(TableEntry));

    for(i = (STARTSZ << T->doubles);i < (STARTSZ << (T->doubles+1));i++){
        strcpy(T->TableArray[i].key,EmptyKey);
        strcpy(T->TableArray[i].data,EmptyData);
        T->TableArray[i].L = NULL;
        T->TableArray[i].LEnd = NULL;
    }

    return T;
}
/*Searches for a given key. Finds initial hash address.
/If the bucket at address has been split find new address
/to check whether key has been rehashed or not.
/When final address is retrieved search there.*/
int SearchHash(Table T,char key[100]){
    ListNode* temp;
    int i = h(key,T.doubles);
    if (i < T.p){
        i = h(key,T.doubles+1);
    }
    if (!strcmp(T.TableArray[i].key,key))
            return i;

    temp = T.TableArray[i].L;
    while (temp){
        if (!strcmp(temp->Entry.key,key)){
            return i;
        }
        temp = temp->next;
    }
    return -1;
}
/*Inserts given node to given bucket's list.*/
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
    if (*L == NodeToRemove) {                                                                           /*If it's in the start of the list. */
        *L = (*L)->next;
        if (*L == NULL)
            *LEnd = NULL;
        free(NodeToRemove);
        return;
    }
    while(temp->next!= NodeToRemove) {                                                                  /*else traverse through the list until you find it.*/
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
    if (Entry->L == NULL) {                                                                             /*If there is only one item in the bucket.*/
        strcpy(Entry->key,EmptyKey);
    } else {
        TableEntry * temp;                                                                              /*else push back one element from the list.*/
        strcpy(Entry->key,Entry->L->Entry.key);
        temp =  &(Entry->L->Entry);
        Entry->L = Entry->L->next;
        free(temp);
    }

}
/*Rehashes given table. Splits T->p bucket. Traverse through
all entries of the T->p bucket and decide if their position will be changed.
If yes reposition them. */
void ReHash(Table *T) {
    int i;

    i = h(T->TableArray[T->p].key,T->doubles+1);
    while((i > ((STARTSZ<<T->doubles)-1)) && strcmp(T->TableArray[T->p].key,EmptyKey)){                 /*If there is some key in the initial entry of the bucket decide repositioning.*/
        HashInsert(T,T->TableArray[T->p].key,T->TableArray[T->p].data,REHASH);
        ResetTableEntry(&(T->TableArray[T->p]));
        i = h(T->TableArray[T->p].key,T->doubles+1);
    }
    if (T->TableArray[T->p].L != NULL) {																/*If list exists,traverse through it and decide repositioning */
        ListNode* temp;
        ListNode* keep;
        temp = T->TableArray[T->p].L;
        while (temp) {
            i = h(temp->Entry.key,T->doubles+1);
            keep = temp->next;
            if (i > ((STARTSZ<<T->doubles)-1)) {
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
        if (i < T->p)                                                                                   /*If bucket of entry has already been rehashed,check with h+1 function.*/
            i = h(key,T->doubles+1);
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
            if (T->p == 0)
                T = extendTable(T);                                                                     /*We need one more segment so allocate needed memory and initialize it.*/
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
