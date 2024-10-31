#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <stdbool.h>

#define MAXVERTEX 20

typedef int Vertex;

struct edge_node {
	Vertex endVertex;
	struct edge_node* next;
};
typedef struct edge_node* Edge;

struct graph {
	int vertexCount;
	Edge* edges; // Array of linked lists
};

typedef struct graph* Graph;

Graph Initialize(int vertexCount);
void InsertEdge(Graph graph, Vertex start, Vertex end);
void ShowGraph(Graph graph);
void DeleteGraph(Graph graph);
void DepthFirst(Graph graph, void (*Visit)(Vertex v));
void BreadthTopSort(Graph graph);
Graph GraphReverse(Graph graph);
int* StrongComponents(Graph graph);
void PrintVertex(Vertex v);

#endif // DIRECTED_GRAPH_H