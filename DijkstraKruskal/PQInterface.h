#ifndef PQINTERFACE_H_INCLUDED
#define PQINTERFACE_H_INCLUDED

/* this is the file "PQInterface.h"      */

#include "PQTypes.h"
/* defines types PQItem and PriorityQueue */

void Initialize (PriorityQueue *);
int Empty (PriorityQueue *);
int Full (PriorityQueue *);
void Insert (PQItem, PriorityQueue *);
PQItem Remove (PriorityQueue *);

#endif
