#ifndef GRAPHTYPES_H_INCLUDED
#define GRAPHTYPES_H_INCLUDED

#define MAXVERTEX 50

typedef enum {FALSE, TRUE} Boolean;

typedef int Vertex;

typedef struct edge {
   Vertex startpoint;
   Vertex endpoint;
   int weight;
   struct edge *nextedge;
} Edge;

typedef struct graph {
   int n;     /* number of vertices in the graph */
   Edge *firstedge[MAXVERTEX];
} Graph;

#endif
