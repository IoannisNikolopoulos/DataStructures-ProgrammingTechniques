#include "directed_graph.h"

int main(int argc, char* argv[]){

    Graph g = Initialize(6);

    InsertWeightedEdge(g, 0, 1, 3);
    InsertWeightedEdge(g, 0, 3, 5);
    InsertWeightedEdge(g, 1, 2, 7);
    InsertWeightedEdge(g, 1, 5, 4);
    InsertWeightedEdge(g, 2, 5, -1);
    InsertWeightedEdge(g, 2, 4, 1);
    InsertWeightedEdge(g, 3, 1, 2);
    InsertWeightedEdge(g, 3, 2, 6);
    InsertWeightedEdge(g, 5, 4, -2);

    ShortestPaths(g, 3);

    DeleteGraph(g);

    return 0;
}
