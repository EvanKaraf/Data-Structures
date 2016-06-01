#include <stdio.h>
#include <stdlib.h>
#include "PQInterface.h"
#include "StackInterface.h"
#include "DisjointSetsInterface.h"
#define INFINITY 999999
#define UNDEFINED -1

void CreateGraphNode (Vertex startpoint,Vertex endpoint,int weight,Edge** temp) {
    Edge* listNode;
    listNode = malloc(sizeof (Edge));

    if (!(*temp))
        (*temp) = listNode;
    else
        (*temp)->nextedge = listNode;

    listNode->endpoint = endpoint;
    listNode->weight = weight;
    listNode->nextedge = NULL;
    listNode->startpoint = startpoint;
}

void readGraph(Graph *G){

    Edge* temp;
    int edgeNumber;
    int i,flag;
    int startPoint,endPoint,weight;
    printf("Enter number of vertices and edges of the desired graph separated by space:\n");
    scanf("%d %d",&(G->n),&edgeNumber);
    printf("Vertices = %d\nEdges = %d\n",G->n,edgeNumber);
    InitializeGraph(G);
    for (i=0; i<edgeNumber; i++) {
        do {
            flag = 0;
            printf("Enter %d pair and its edge's weight\n",i+1);
            scanf("%d %d %d",&startPoint,&endPoint,&weight);
            if (startPoint > G->n || startPoint < 0 || endPoint > G->n || endPoint < 0) {		    /*Wrong input so try again.*/
                printf("Entered vertices not in range,try again!\n");
                flag = 1;
            }

        } while(flag);
        temp = G->firstedge[startPoint];
        if (!temp)
            CreateGraphNode(startPoint,endPoint,weight,&(G->firstedge[startPoint]));
        else {
            while(temp->nextedge) {
                temp = temp->nextedge;
            }
            CreateGraphNode(startPoint,endPoint,weight,&temp);
        }
    }

}


int readGraphFromFile(Graph *G){
    char user_filename[100];
    printf("INFO:File must be in the following format:\n");
    printf("Number of vertices number of edges\n");
    printf("edges-time pairs in format SOURCE DESTINATAION WEIGHT\n");
    printf("Enter filename:");
    scanf("%s", user_filename);
    FILE *file=fopen(user_filename, "r");
    if (!file) {
        return -1;
    }
    Edge* temp;
    int edgeNumber;
    int i;
    int startPoint,endPoint,weight;

    fscanf(file,"%d %d",&(G->n),&edgeNumber);
    InitializeGraph(G);
    for (i=0; i<edgeNumber; i++) {
        fscanf(file,"%d %d %d",&startPoint,&endPoint,&weight);
        if (startPoint > G->n || startPoint < 0 || endPoint > G->n || endPoint < 0)
            return 0;

        temp = G->firstedge[startPoint];
        if (!temp)
            CreateGraphNode(startPoint,endPoint,weight,&(G->firstedge[startPoint]));
        else {
            while(temp->nextedge) {
                temp = temp->nextedge;
            }
            CreateGraphNode(startPoint,endPoint,weight,&temp);
        }
    }
    return 1;

}
void InitializeGraph(Graph *G) {
    int i;
    for (i=0; i<G->n; i++ )
        G->firstedge[i] = NULL;
}

void PrintAdjList(Graph *G) {
    int i;
    printf("Result:\n");

    for (i=0 ; i<G->n ; i++) {
        printf("%d:", i);
        Edge *temp;
        temp = G->firstedge[i];
        while (temp) {
            printf(" %d(%d),", temp->endpoint,temp->weight);
            temp = temp->nextedge;
        }
        printf("\n");

    }
        printf("\b \n");
        printf("Parentheses are the weight of the edge\n");
        printf("--------------\n");
    return;
}


void Dijkstra(Graph G,Vertex start) {
    int i;
    int *dist;                                                                                              /*Keeps minimum distance from source for every graph node.*/
    int *prev;                                                                                              /*Keeps the previous node that is connected to a given graph node.*/
    int *visited;                                                                                           /*Whether a node has been already traversed.*/
    Vertex currentNode,nextNode;                                                                            /*Used for traversing through graph.*/
    Edge *traverseTemp;
    Edge* tempEdge;
    Edge dummyStart;                                                                                        /*Create a "fake" start to insert to PQ to start going because we got no edge with endpoint == source.*/
    int altDistance;

    if (!G.firstedge[start]){                                                                               /*Node's adjacency list is empty so just return with no result.*/
        printf("Node is not connected!\n");
        return;
    }
                                                                                                            /*Initialization starts here.*/
    dist = malloc(G.n * sizeof(int)); 									                                    /*Keeps the minimum distance to every node from source.*/
    prev = malloc(G.n * sizeof(int));									                                    /*Keeps the parent of a given node to print path.*/
    visited = malloc(G.n * sizeof(int));

    PriorityQueue Visit;
    Initialize(&Visit);

    for (i=0; i<G.n; i++) {
        dist[i] = INFINITY;
        prev[i] = UNDEFINED;
        visited[i] = 0;
    }
    dist[start] = 0;

    dummyStart.endpoint = start;
    dummyStart.weight = 0;                                                                                      /*Create a dummy node to start the process.*/

    Insert(&dummyStart,&Visit);
                                                                                                                /*Initialization ends here.*/

    while(!Empty(&Visit)) {
        tempEdge = Remove(&Visit);                                                                              /*Returns lowest item from PQ based on weight. */
        if (visited[tempEdge->endpoint] == 0){
            visited[tempEdge->endpoint] = 1;
            currentNode = tempEdge->endpoint;                                                                   /*Edge's endpoint acts as current vertex. */
            for (traverseTemp=G.firstedge[currentNode]; traverseTemp; traverseTemp = traverseTemp->nextedge) {  /*Traverse through the adjacency list. */
                nextNode = traverseTemp->endpoint;
                altDistance = dist[currentNode] + traverseTemp->weight;                                         /*If found a new better path change node's distance from source. */
                if (altDistance < dist[nextNode]) {
                    dist[nextNode] = altDistance;
                    prev[nextNode] = currentNode;
                    Insert(traverseTemp,&Visit);
                }
            }
        }
    }

    Stack S;
    InitializeStack(&S);
    int nodeToPrint;
    printf("Source node: %d\n",start);
    for (i=0; i<G.n; i++) {
        if (i!=start) {											                                                /*Backtrack in prev array to print and the path with the help of a stack in order to print nice-looking results.*/
            if (dist[i] == INFINITY) {
                printf("Source is not connected with %d\n",i);
                continue;
            }
            printf("Distance to %d is %2d and path is ",i,dist[i]);
            Push(i,&S);
            nodeToPrint = prev[i];
            while (nodeToPrint != UNDEFINED) {

                Push(nodeToPrint,&S);
                nodeToPrint = prev[nodeToPrint];
            }

            while(!EmptyStack(&S)) {
                Pop(&S,&nodeToPrint);
                printf("%d->",nodeToPrint);
            }
            printf("\b\b  ");
            printf("\n");
        } else
            printf("Distance to self is always 0\n");
    }
    free(dist);
    free(prev);
    free(visited);

}



void Kruskal(Graph G){
    int i;
    int *represent = malloc(G.n * sizeof(int));
    int *rank = malloc(G.n * sizeof(int));
    for (i=0;i<G.n;i++){
        MakeSet(represent,rank,i);									    /*Create starting sets for every element. */
    }
    PriorityQueue PQ;
    Initialize(&PQ);
    Edge *temp;
    Vertex start;
    Vertex end;
    for (i=0;i<G.n;i++){										    /*Insert all edges in priority queue in order to dequeue them with increasing order. */
        temp = G.firstedge[i];
        while (temp){
            Insert(temp,&PQ);
            temp=temp->nextedge;
        }
    }
    int verticesCount=0;
    int minPathWeight=0;
    printf("Edges contained in minimum spanning tree are:\n");
    while (verticesCount<G.n-1 && !Empty(&PQ)){
        temp = Remove(&PQ);
        start = Find(represent,temp->startpoint);
        end = Find(represent,temp->endpoint);								   /*Remove edges one by one and if their vertices aren't in the same set (means it's not a circle) merge them and print them because it's part of the MST */

        if (start != end){
            verticesCount++;
            minPathWeight += temp->weight;
            printf("%d->%d\n",temp->startpoint,temp->endpoint);
            Union(represent,rank,temp->startpoint,temp->endpoint);
        }
    }
    printf("And minimum spanning tree's cost is %d\n",minPathWeight);
}
