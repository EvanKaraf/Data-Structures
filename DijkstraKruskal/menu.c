#include <stdio.h>
#include <stdlib.h>
#define G_FROM_FILE 1
#define G_MANUAL 2
#define PRINT_ADJ 3
#define RUN_DIJK 4
#define RUN_KRUSKAL 5
#define EXAMPLE 6
#define QUIT 7
#include "GraphsInterface.h"

void runDijkstra(Graph G){
    printf("Choose a source node for Dijkstra's algorithm![0,%d]\n",G.n-1);
    int source,flag;
   do{
	flag = 0;
    	scanf("%d",&source);
   	if (source<0 || source > G.n-1){
        	printf("Wrong source.Try again..\n");
		flag = 1;
   	 }
    }while(flag);

    Dijkstra(G,source);
}

void runKruskal(Graph G){
    printf("INFO: Kruskal's algorithm works only for undirected graphs.YOU HAVE BEEN WARNED!\n");
    Kruskal(G);
}

void options(void){
    printf("~~~~~~Dijkstra's and Kruskal's Algorithms Implementation!~~~~~~\n");
    printf("Choose an option:\n");
    printf("------------------------------\n");
    printf("1. Input a graph from file.\n");
    printf("2. Input a graph manually.\n");
    printf("3. Print adjacency list.\n");
    printf("4. Run Dijkstra's Algorithm.\n");
    printf("5. Run Kruskal's Algorithm.\n");
    printf("6. Example graph to try the program\n");
    printf("\n7. Quit.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void printExample(void){
    printf("    2   \n");
    printf(" 0------1\n");
    printf(" |     /|\n");
    printf("8|   5  | 6\n");
    printf(" |  /   |\n");
    printf(" | /    |\n");
    printf(" 2------3\n");
    printf("    9    \n");

}
void runPresentation(Graph *G){
    G->n = 4;
    InitializeGraph(G);

    printf("The following undirected graph will be used as an input example:\n\n");
    printExample();

    CreateGraphNode(0,1,2,&(G->firstedge[0]));
    CreateGraphNode(1,0,2,&(G->firstedge[1]));

    CreateGraphNode(0,2,8,&(G->firstedge[0]->nextedge));
    CreateGraphNode(2,0,8,&(G->firstedge[2]));

    CreateGraphNode(2,3,9,&(G->firstedge[2]->nextedge));
    CreateGraphNode(3,2,9,&(G->firstedge[3]));

    CreateGraphNode(2,1,5,&(G->firstedge[2]->nextedge->nextedge));
    CreateGraphNode(1,2,5,&(G->firstedge[1]->nextedge));

    CreateGraphNode(1,3,6,&(G->firstedge[1]->nextedge->nextedge));
    CreateGraphNode(3,1,6,&(G->firstedge[3]->nextedge));

    printf("Input successful.\n");
}


void menu(void) {
    int choice;
    system("clear");
    options();
    printf("Input:");
    scanf("%d",&choice);

    while (1) {
        Graph G;
        int returnVal;

        switch (choice) {
        case G_FROM_FILE:
            returnVal = readGraphFromFile(&G);
            system("clear");
            options();
            if (returnVal == 1)        printf("Result = SUCCESS\n");
            else if (returnVal == 0)    printf("Wrong input!\n");
            else                        printf("Error opening file...\n");
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        case G_MANUAL:
            readGraph(&G);
            system("clear");
            options();
            printf("Result = SUCCESS\n");
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        case PRINT_ADJ:
            system("clear");
            options();
            PrintAdjList(&G);
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        case RUN_DIJK:
            runDijkstra(G);
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        case RUN_KRUSKAL:
            runKruskal(G);
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        case EXAMPLE:
            runPresentation(&G);
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        case QUIT:
            printf("Exiting...\n");
	    return;
            break;
        default:
            printf("not a valid choice!\n");
            printf("Enter new input:");
            scanf("%d",&choice);
            break;
        }

    }
}


