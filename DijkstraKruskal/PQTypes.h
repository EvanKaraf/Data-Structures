#ifndef PQTYPES_H_INCLUDED
#define PQTYPES_H_INCLUDED

#include "GraphsInterface.h"

#define MAXCOUNT 100
typedef Edge* PQItem;
typedef PQItem PQArray[MAXCOUNT+1];

typedef struct {
    int Count;
    PQArray ItemArray;
} PriorityQueue;

#endif
