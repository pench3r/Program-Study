#include "graph.h"

int main(int argc, char *argv[]) {
	Graph graph_t;
	GraphInit(&graph_t);
	GraphInsertVertex(&graph_t, 10);
	GraphInsertVertex(&graph_t, 20);
	GraphInsertVertex(&graph_t, 30);
	GraphInsertEdge(&graph_t, 10, 30);
	GraphInsertEdge(&graph_t, 10, 20);
	GraphInsertEdge(&graph_t, 30, 20);
	GraphInsertEdge(&graph_t, 30, 20);
	printf("is adjcent %d.\n", VertexIsAdjcent(&graph_t, 10, 30));
	GraphShow(&graph_t);
	return 0;
}
