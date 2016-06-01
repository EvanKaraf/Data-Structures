#include "QueueInterface.h"


int main(void){
    Stack S;
    Queue Q;
    StackNode ch;
    InitializeQueue(&Q);
    int i;
    for(i=65;i<69;i++){
        ch.Item = i;
        Insert(ch.Item,&Q);
    }
    Remove(&Q,ch.Item);
    Remove(&Q,ch.Item);
}
