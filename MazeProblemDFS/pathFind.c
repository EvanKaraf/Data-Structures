#include "StackInterface.h"
#include "Utilities.h"

typedef struct currentPosition{

    int Row;
    int Col;

    }Position;



int foundPath(int **board,int rows,int columns){

    Stack S,Draw;
    int flag,count,i;
    int **visited;
                    /* COLUMNS: {RowMod,ColMod,RowRes,ColRes} */
    int moves[4][4] =         { {-1,0,0,-1},                              /* Up    */
                                {1,0,0, -1},                              /* Down  */
                                {0,1,-1, 0},                              /* Right */
                                {0,-1,-1,0} };                            /* Left  */
    Position Pos,Start,Goal;


    visited = createVisited(rows,columns);
    InitializeStack(&S);
    InitializeStack(&Draw);

    moves[1][2] = rows - 1;                                                     /*Set values of grid's size bound borders. */
    moves[2][3] = columns - 1;

    getStartPos(board,rows,columns,&Start.Row,&Start.Col);
    getGoalPos(board,rows,columns,&Goal.Row,&Goal.Col);

    Push(Start.Row,Start.Col,0,&S);
    visited[Start.Row][Start.Col] = 1;
    flag = 0;
    int neighbors = 0;
    while (!Empty(&S)){
        Pop(&S,&Pos.Row,&Pos.Col,&neighbors);
        if (Pos.Row == Goal.Row && Pos.Col == Goal.Col){
            flag = 1;
            break;
        }
        count = 0;
        board[Pos.Row][Pos.Col] = 8;
        for (i=0;i<4;i++){
            if((Pos.Row != moves[i][2]) && (Pos.Col != moves[i][3]) &&
               (board[Pos.Row + moves[i][0]][Pos.Col + moves[i][1]] != 0) &&
               visited[Pos.Row+moves[i][0]][Pos.Col+moves[i][1]] == 0){
                            count++;
                            visited[Pos.Row+moves[i][0]][Pos.Col+moves[i][1]] = 1;
                            Push(Pos.Row+moves[i][0],Pos.Col + moves[i][1],count,&S);
                            Push(Pos.Row+moves[i][0],Pos.Col + moves[i][1],count,&Draw);
            }
        }
        if (count == 0){
            neighbors = 1;
            while(neighbors == 1 && !Empty(&Draw)){
                Pop(&Draw,&Pos.Row,&Pos.Col,&neighbors);
                board[Pos.Row][Pos.Col] = 1;

            }
        }
    }

    while(!Empty(&Draw))
        Pop(&Draw,&Pos.Row,&Pos.Col,&neighbors);                    /*Just empty Draw in case it has remaining nodes. */
    while(!Empty(&S))
        Pop(&S,&Pos.Row,&Pos.Col,&neighbors);                       /*Just empty S in case it has remaining nodes. */
    board[Start.Row][Start.Col] = 2;
    freeBoard(visited,rows);

    return flag;
}
