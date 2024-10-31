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

Edge createEdge(Vertex vertex) {
	Edge edge = malloc(sizeof(*edge));
	edge->endVertex = vertex;
	edge->next = NULL;
	return edge;
}

void insertEdgeInternal(Graph graph, Vertex start, Vertex end) {
	assert(graph != NULL);
	assert(start < graph->vertexCount);
	assert(end < graph->vertexCount);

	Edge newEdge = createEdge(end);

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

void InsertEdge(Graph graph, Vertex start, Vertex end) {
	insertEdgeInternal(graph, start, end);
	insertEdgeInternal(graph, end, start);
}

void ShowGraph(Graph graph) {
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("%d:", i);
        Edge edge = graph->edges[i];
        while (edge != NULL) {
            printf(" %d", edge->endVertex);
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

static Vertex* path;
static int pathIndex;
void addToPath(Vertex v) {
	path[pathIndex++] = v;
}

Vertex* SimplePathCheck(Graph graph, Vertex start, Vertex end) {
	bool* visited = calloc(graph->vertexCount, sizeof(bool));

	path = malloc(graph->vertexCount * sizeof(Vertex));
	pathIndex = 0;
	for (int i = 0; i < graph->vertexCount; i++) {
		path[i] = -1;
	}

	TraverseDFS(graph, start, addToPath, visited, end);

	for (int i = 0; i < pathIndex; i++) {
		if (path[i] == end) {
			if (i + 1 < pathIndex) path[i + 1] = -1;
			free(visited);
			return path;
		}
	}

	free(visited);
	return NULL;
}
