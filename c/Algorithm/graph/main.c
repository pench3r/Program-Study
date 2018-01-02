#include "graph.h"

int main(int argc, char *argv[]) {
	Graph graph_t;
	GraphInit(&graph_t);
	GraphInsertVertex(&graph_t, 10);
	GraphShow(&graph_t);
	return 0;
}
