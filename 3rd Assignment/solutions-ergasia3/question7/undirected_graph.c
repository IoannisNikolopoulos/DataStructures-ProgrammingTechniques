#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "undirected_graph.h"

Graph Initialize(int vertexCount) {
	Graph graph = malloc(sizeof(*graph));
	graph->vertexCount = vertexCount;
	graph->edges = calloc(vertexCount, sizeof(Edge));
	return graph;
}

Edge createEdge(Vertex vertex, int weight) {
	Edge edge = malloc(sizeof(*edge));
	edge->endVertex = vertex;
	edge->next = NULL;
	edge->weight = weight;
	return edge;
}

void insertEdgeInternal(Graph graph, Vertex start, Vertex end, int weight) {
	assert(graph != NULL);
	assert(start < graph->vertexCount);
	assert(end < graph->vertexCount);

	Edge newEdge = createEdge(end, weight);

	if (graph->edges[start] == NULL || end < graph->edges[start]->endVertex) {
		newEdge->next = graph->edges[start];
		graph->edges[start] = newEdge;
		return;
	}

	Edge cursor = graph->edges[start];
	while (cursor->next != NULL && end > cursor->next->endVertex) {
		cursor = cursor->next;
	}

	newEdge->next = cursor->next;
	cursor->next = newEdge;
}

void InsertEdge(Graph graph, Vertex start, Vertex end, int weight) {
	insertEdgeInternal(graph, start, end, weight);
	insertEdgeInternal(graph, end, start, weight);
}

void ShowGraph(Graph graph) {
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("%d:", i);
        Edge edge = graph->edges[i];
        while (edge != NULL) {
            printf(" (end: %d, weight: %d)", edge->endVertex, edge->weight);
            edge = edge->next;
        }
        printf("\n");
    }
}

void DeleteGraph(Graph graph){
	for (int i = 0; i < graph->vertexCount; i++){
		Edge edge = graph->edges[i];
		while (edge != NULL){
			Edge temp = edge;
			edge = edge->next;
			free(temp);
		}
	}
	free(graph->edges);
	free(graph);
}

void TraverseDFS(Graph graph, Vertex v, void (*Visit)(Vertex v), bool* visited, Vertex end) {
	visited[v] = true;
	Visit(v);

	if (v == end) return;

	Edge currentEdge = graph->edges[v];
	while (currentEdge != NULL) {
		Vertex endVertex = currentEdge->endVertex;
		if (!visited[endVertex]) TraverseDFS(graph, endVertex, Visit, visited, end);
		currentEdge = currentEdge->next;
	}
}

bool mstFull(bool* inMST, int count) {
	for (int i = 0; i < count; i++) {
		if (!inMST[i]) return false;
	}
	return true;
}

void findBestEdge(Graph graph, bool* inMST, Vertex* start, Vertex* end, int* weight) {
	for (int i = 0; i < graph->vertexCount; i++) {
		if (!inMST[i]) continue;

		for (Edge currentEdge = graph->edges[i]; currentEdge != NULL; currentEdge = currentEdge->next) {
			if (inMST[currentEdge->endVertex]) continue;

			if (currentEdge->weight < *weight) {
				*start = i;
				*end = currentEdge->endVertex;
				*weight = currentEdge->weight;
			}
		}
	}
}

Graph MinimumSpanningTree(Graph graph) {
	Graph mst = Initialize(graph->vertexCount);

	bool* inMST = calloc(graph->vertexCount, sizeof(bool));
	inMST[0] = true;

	while (!mstFull(inMST, graph->vertexCount)) {
		Vertex start = 0, end = 0;
		int weight = INT_MAX;

		findBestEdge(graph, inMST, &start, &end, &weight);

		InsertEdge(mst, start, end, weight);
		inMST[end] = true;
	}

	return mst;
}
