#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "directed_graph.h"
#include "deque.h"

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

void InsertEdge(Graph graph, Vertex start, Vertex end) {
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

void TraverseDFS(Graph graph, Vertex v, void (*Visit)(Vertex v), bool* visited) {
	visited[v] = true;
	Visit(v);

	Edge currentEdge = graph->edges[v];
	while (currentEdge != NULL) {
		Vertex endVertex = currentEdge->endVertex;
		if (!visited[endVertex]) TraverseDFS(graph, endVertex, Visit, visited);
		currentEdge = currentEdge->next;
	}
}

void PrintVertex(Vertex v) {
	printf("%d\n", v);
}

void DepthFirst(Graph graph, void (*Visit)(Vertex v)) {
	bool* visited = calloc(graph->vertexCount, sizeof(bool));

	for (int i = 0; i < graph->vertexCount; i++) {
		if (!visited[i]) TraverseDFS(graph, i, Visit, visited);
	}
	free(visited);
}

void BFS(Graph graph, void (*Visit)(Vertex v)) {
	bool* visited = calloc(graph->vertexCount, sizeof(bool));
	Deque deque = createDeque();

	for (Vertex startVertex = 0; startVertex < graph->vertexCount; startVertex++) {
		if (visited[startVertex]) continue;

		dequeEnque(deque, startVertex);

		while(!dequeIsEmpty(deque)) {
			Vertex v = dequeDequeue(deque);
			if (visited[v]) continue;

			visited[v] = true;
			Visit(v);

			Edge currentEdge = graph->edges[v];
			while (currentEdge != NULL) {
				if (!visited[currentEdge->endVertex]) dequeEnque(deque, currentEdge->endVertex);
				currentEdge = currentEdge->next;
			}
		}
	}

	dequeDelete(deque);
	free(visited);
}

void BreadthTopSort(Graph graph) {
	int* inDegree = calloc(graph->vertexCount, sizeof(int));

	for (Vertex v = 0; v < graph->vertexCount; v++) {
		Edge currentEdge = graph->edges[v];
		while (currentEdge != NULL) {
			inDegree[currentEdge->endVertex]++;
			currentEdge = currentEdge->next;
		}
	}

	Deque deque = createDeque();

	for (Vertex v = 0; v < graph->vertexCount; v++) {
		if (inDegree[v] == 0) dequeEnque(deque, v);
	}

	while(!dequeIsEmpty(deque)) {
		Vertex v = dequeDequeue(deque);

		printf("Vertex: %d\n", v);

		Edge currentEdge = graph->edges[v];
		while (currentEdge != NULL) {
			inDegree[currentEdge->endVertex]--;
			if (inDegree[currentEdge->endVertex] == 0) dequeEnque(deque, currentEdge->endVertex);
			currentEdge = currentEdge->next;
		}
	}

	dequeDelete(deque);
	free(inDegree);
}

Graph GraphReverse(Graph graph) {
	Graph newGraph = Initialize(graph->vertexCount);

	for (int i = 0; i < graph->vertexCount; i++) {
		Edge currentEdge = graph->edges[i];
		while (currentEdge != NULL) {
			InsertEdge(newGraph, currentEdge->endVertex, i);
			currentEdge = currentEdge->next;
		}
	}

	return newGraph;
}

static int vertexOrderIndex;
static Vertex* vertexOrder;

void NumberVertices(Vertex vertex) {
	assert(vertexOrderIndex >= 0);
	vertexOrder[vertexOrderIndex++] = vertex;
}

static int* sc;
static int scIndex;

void assignSC(Vertex vertex) {
	sc[vertex] = scIndex;
}

int* StrongComponents(Graph graph) {
	vertexOrder = malloc(graph->vertexCount * sizeof(*vertexOrder));
	vertexOrderIndex = 0;

	DepthFirst(graph, NumberVertices);

	Graph reverse = GraphReverse(graph);

	sc = calloc(graph->vertexCount, sizeof(int));
	bool* visited = calloc(graph->vertexCount, sizeof(bool));

	scIndex = 1;
	for (int i = 0; i < graph->vertexCount; i++) {
		Vertex v = vertexOrder[i];
		if (!visited[v]) {
			TraverseDFS(reverse, v, assignSC, visited);
			scIndex++;
		}
	}

	free(vertexOrder);
	free(visited);
	DeleteGraph(reverse);

	return sc;
}
