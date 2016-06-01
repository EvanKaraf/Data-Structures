#include "DisjointSetsInterface.h"

hello
void MakeSet(int *Represent,int* rank,SetItem ItemToMake){
    Represent[ItemToMake] = ItemToMake;
    rank[ItemToMake] = 1;
}

int Find(int *Represent,SetItem ItemToFind){
    if (Represent[ItemToFind] != ItemToFind)
        Represent[ItemToFind] = Find(Represent,Represent[ItemToFind]);
    return Represent[ItemToFind];
}

void Union(int* Represent,int* rank,SetItem FirstItem,SetItem SecondItem){
    SetItem ParentFirst = Find(Represent,FirstItem);
    SetItem ParentSecond = Find(Represent,SecondItem);

    if (ParentFirst == ParentSecond) return;

    if (rank[ParentFirst] < rank[ParentSecond]){
        Represent[ParentFirst] = ParentSecond;
        rank[ParentSecond] += rank[ParentFirst];
    }
    else if (rank[ParentFirst] >= rank[ParentSecond]){
        Represent[ParentSecond] = ParentFirst;
        rank[ParentFirst] += rank[ParentSecond];
    }
}
