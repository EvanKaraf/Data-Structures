#include <stdio.h>
#include <stdlib.h>
#include "Utilities.h"



int foundPath(int **board,int rows,int columns);

int main(void){

    int **board,rows,columns;

    board = initializeBoard(&rows,&columns);

    if (foundPath(board,rows,columns)){
        printf("\nFound a path!!\n");
    }
    else
        printf("\nThere is no path...\n");

    printBoard(board,rows,columns);
    freeBoard(board,rows);

return 0;
}
