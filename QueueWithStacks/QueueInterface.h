/* This is the file QueueInterface.h   */

#include "QueueTypes.h"

void InitializeQueue(Queue *Q);
int EmptyQueue(Queue *);
int FullQueue(Queue *);
void Insert(ItemType R, Queue *Q);
void Remove(Queue *Q, ItemType *F);
