#include <stdio.h>
#include <stdlib.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Board Utilities.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int** initializeBoard(int *rows,int *columns){
    int i,j;
    char element;
    int **board;

    printf("Please enter rows and columns separated by space\n\n");                             /*Initialization of board starts here*/
    scanf("%d %d",rows,columns);
    board = malloc(*rows * sizeof(int *));
    if (board == NULL){
        printf("Not Enough Memory.Exiting\n\n");
        exit(0);
    }
    for (i=0;i<*rows;i++){
        board[i]=malloc(*columns * sizeof(int));
        if (board[i]==NULL) {
            printf("Not Enough Memory.Exiting.\n\n");
            exit(0);
        }
    }

    getchar();
    for (i=0;i<*rows;i++){
        j = 0;
        while ((element=getchar()) != '\n'){                                                    /*Turn char input into integers for easier manipulation*/
            if (element == '.')
                board[i][j] = 1;
            else if (element == '#')
                board[i][j] = 0;
            else if (element == 'S')
                board[i][j] = 2;
            else if (element == 'G')
                board[i][j] = 3;
            else{
                printf("Invalid Input.Exiting\n\n");
                exit(0);
            }
            j++;
        }
    }
    if (j != *columns ){
        printf("Invalid Input.Exiting\n\n");                                                    /*Ends here.*/
        exit(0);
    }

    return board;
}

void printBoard(int **board,int rows,int columns){
    int i,j;
    for (i=0;i<rows;i++){
        putchar('\n');
        for(j=0;j<columns;j++){
            if (board[i][j] == 2)
                printf("S");
            else if(board[i][j] == 3)
                printf("G");
            else if(board[i][j] == 1)
                printf(".");
            else if(board[i][j] == 8)
                printf("+");
            else
                printf("#");
        }
    }

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Visited Utilities.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int** createVisited(int rows,int columns){
    int i,j,**visited;
    visited = malloc(rows * sizeof(int *));
    if (visited == NULL){
        printf("Not Enough Memory.Exiting\n\n");
        exit(0);
    }
    for (i=0;i<rows;i++){
        visited[i]=malloc(columns * sizeof(int));
        if (visited[i]==NULL) {
            printf("Not Enough Memory.Exiting.\n\n");
            exit(0);
        }
    }
    for (i=0;i<rows;i++){
        for (j=0;j<columns;j++){
            visited[i][j] = 0;
        }
    }
return visited;
}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Misc Utilities.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void freeBoard(int **board,int rows){
    int i;
    for (i=0;i<rows;i++){
        free(board[i]);
    }
    free(board);

}

void getStartPos(int **board,int rows,int columns,int* sRow,int *sCol){
    int i,j;
    for (i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if (board[i][j] == 2){
                *sRow = i;
                *sCol = j;
            }
        }
    }
}

void getGoalPos(int **board,int rows,int columns,int* gRow,int *gCol){
    int i,j;
    for (i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if (board[i][j] == 3){
                *gRow = i;
                *gCol = j;
            }
        }
    }
}


