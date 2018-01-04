#ifndef __ALGORITHM_GRAPH__H
#define __ALGORITHM_GRAPH__H

#include "../set/set.h"
#define MAX_VERTEX 10

typedef struct adjlist_ {
	int data;
	Set adjcent;
} Adjlist;

typedef struct graph_ {
	int vertex_count;
	int edge_count;
	Adjlist* adjlists[MAX_VERTEX];
} Graph;

/* struct graph init func
   parameters:
		Graph *graph,
   return: void.
*/
void GraphInit(Graph *graph);

/* struct graph insert Vertext func
   parameters:
		Graph *graph,
		int data,
   return: bool.
*/
bool GraphInsertVertex(Graph *graph, int data);

/* struct graph search func
   parameters:
		Graph *graph,
		int data,
   return: int.
*/
int GraphSearchVertex(Graph *graph, int data);

/* struct graph insert edge func
   parameters:
		Graph *graph,
		const int data1,
		const int data2,
*/
bool GraphInsertEdge(Graph *graph, const int data1, const int data2);

/* struct vertex isadjcent func
   parameters:
		Graph *graph,
		int data1,
		int data2,
   return: bool.
*/
bool VertexIsAdjcent(Graph *graph, int data1, int data2); 

/* struct graph show func
   parameters:
		Graph *graph,
   return: void.
*/
void GraphShow(Graph *graph);

#endif /* __ALGORITHM_GRAPH__H */
