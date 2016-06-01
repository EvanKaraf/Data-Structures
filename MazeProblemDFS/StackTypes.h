/* This is the file StackTypes.h   */

typedef struct StackNodeTag {
           int Row;                         /* Coordinates and number of neighbors.*/
           int Column;
           int Neighbors;
           struct StackNodeTag *Link;
        } StackNode;

typedef struct {
           StackNode *ItemList;
        } Stack;
