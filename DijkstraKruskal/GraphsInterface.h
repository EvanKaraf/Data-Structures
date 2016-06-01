#ifndef DISJOINTSETSINTERFACE_H_INCLUDED
#define DISJOINTSETSINTERFACE_H_INCLUDED

#include "GraphTypes.h"

void CreateGraphNode (Vertex startPoing,Vertex endpoint,int weight,Edge** temp);
void InitializeGraph(Graph *G);
void PrintAdjList(Graph *G);
void Dijkstra(Graph G,Vertex start);
int readGraphFromFile(Graph *G);
void readGraph(Graph *G);
void Kruskal(Graph G);

#endif
