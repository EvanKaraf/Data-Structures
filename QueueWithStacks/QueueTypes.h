/* This is the file QueueTypes.h */

#include "StackInterface.h"


typedef struct QueueNodeTag {
                     ItemType Item;
                     struct QueueNodeTag *Link;
                } QueueNode;

typedef struct {
                    Stack First;
                    Stack Secondary;
               }Queue;
