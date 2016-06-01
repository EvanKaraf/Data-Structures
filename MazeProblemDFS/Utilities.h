int ** initializeBoard(int *rows,int *columns);
int** createVisited(int rows,int columns);
void resetVisited(int **visited,int rows,int columns);
void freeBoard(int **visited,int rows);
void getStartPos(int **board,int rows,int columns,int* sRow,int *sCol);
void getGoalPos(int **board,int rows,int columns,int* gRow,int *gCol);
void printBoard(int **board,int rows,int columns);
