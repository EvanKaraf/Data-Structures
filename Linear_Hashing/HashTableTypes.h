#ifndef HASHTABLETYPES_H_INCLUDED
#define HASHTABLETYPES_H_INCLUDED

typedef struct {
    char key[100];
    char data[20];
    struct listnode *L;
    struct listnode *LEnd;
} TableEntry;

typedef struct listnode {
    TableEntry Entry;
    struct listnode* next;
} ListNode;

typedef struct {
    TableEntry *TableArray;
    int p;
    int doubles;
    int entriesCount;
    int buckets;
    double loadFactor;
} Table;

#endif
