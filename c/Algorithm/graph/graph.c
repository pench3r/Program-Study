#include "graph.h"

// define graph init func
void GraphInit(Graph *graph) {
	graph->vertex_count = 0;
	graph->edge_count = 0;
	// graph->adjlists = (Adjlist *)calloc(MAX_VERTEX, sizeof(Adjlist));	
}

// define graph insert func
bool GraphInsertVertex(Graph *graph, int data) {
	Adjlist *new_adjlist = (Adjlist *)malloc(sizeof(Adjlist));
	new_adjlist->data = data;
	SetInit(&new_adjlist->adjcent);		
	graph->adjlists[graph->vertex_count] = new_adjlist;
	graph->vertex_count++;
	return true;
}

// define graph show func
void GraphShow(Graph *graph) {
	printf("Show the graph info: \n");
	printf("The graph vertex is %d, edge is %d.\n", graph->vertex_count, graph->edge_count);
	for (int i=0; i<graph->vertex_count; ++i) {
		printf("\tThe vertex is %d.\n", graph->adjlists[i]->data);
	}
}
