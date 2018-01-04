#include "graph.h"

// define graph init func
void GraphInit(Graph *graph) {
	graph->vertex_count = 0;
	graph->edge_count = 0;
	// graph->adjlists = (Adjlist *)calloc(MAX_VERTEX, sizeof(Adjlist));	
}

// define graph insert vertex func
bool GraphInsertVertex(Graph *graph, int data) {
	if (GraphSearchVertex(graph, data)>=0) return false;
	Adjlist *new_adjlist = (Adjlist *)malloc(sizeof(Adjlist));
	new_adjlist->data = data;
	SetInit(&new_adjlist->adjcent);		
	graph->adjlists[graph->vertex_count] = new_adjlist;
	graph->vertex_count++;
	return true;
}

// define graph search vertex func
int GraphSearchVertex(Graph *graph, int data) {
	if (graph->vertex_count == 0) return -1;
	for (int i=0; i<graph->vertex_count; ++i) {
		if (graph->adjlists[i]->data == data) return i;
	}	
#ifdef DEBUG
	printf("The data not found!!!\n");
#endif
	return -1;
}

// define graph insert edge func
bool GraphInsertEdge(Graph *graph, int data1, int data2) {
	int index = GraphSearchVertex(graph, data1);	
	if (index < 0) {
#ifdef DEBUG
		printf("The data not found!!!\n");
#endif
		return false;
	}
	if (SetInsert(&graph->adjlists[index]->adjcent, data2)) {
		graph->edge_count++;
		return true;
	}
	return false;
}

// define vertex isadjcent func
bool VertexIsAdjcent(Graph *graph, const int data1, const int data2) {
	int index = GraphSearchVertex(graph, data1);
	if (index < 0) {
#ifdef DEBUG
		printf("The data not found!!!\n"); 
#endif
		return false;
	}
	if (SetIsMember(&graph->adjlists[index]->adjcent, data2) >= 0) return true;	
	return false;
}

// define graph show func
void GraphShow(Graph *graph) {
	printf("Show the graph info: \n");
	printf("The graph vertex is %d, edge is %d.\n", graph->vertex_count, graph->edge_count);
	for (int i=0; i<graph->vertex_count; ++i) {
		printf("\tThe vertex is %d, ", graph->adjlists[i]->data);
		SetShow(&graph->adjlists[i]->adjcent);
		printf("\n");
	}
}
