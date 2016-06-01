#ifndef DISJOINTSETSTYPES_H_INCLUDED
#define DISJOINTSETSTYPES_H_INCLUDED
#include "GraphsInterface.h"
typedef Vertex SetItem;

void MakeSet(int *Represent,int* rank,SetItem ItemToMake);
int Find(int *Represent,SetItem ItemToFind);
void Union(int* Represent,int* rank,SetItem FirstItem,SetItem SecondItem);

#endif
