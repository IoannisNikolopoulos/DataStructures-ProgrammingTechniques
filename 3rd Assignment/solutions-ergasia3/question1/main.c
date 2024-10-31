#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directed_graph.h"
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char* argv[]){

    Graph g1;
    if (argc > 1 && strcmp(argv[1], "-") == 0) {
        int i = 0;
        char c = '\0';
        int start = 0, end = 0;
        bool writeEnd = false;

        while (c = getchar(), c != EOF) {
            if (isdigit(c)) {
                if (i == 0) g1 = Initialize(c - '0');
                else if (writeEnd) end = c - '0';
                else start = c - '0';
            }

            if (c == '-') {
                writeEnd = true;
            }

            if (c == '\n' && writeEnd == true) {
                writeEnd = false;
                InsertEdge(g1, start, end);
            }

            i++;
        }
    }
    else {
        g1 = Initialize(5); // Create a graph with 5 vertices
        InsertEdge(g1, 0, 1);
        InsertEdge(g1, 0, 2);
        InsertEdge(g1, 1, 2);
        InsertEdge(g1, 1, 3);
        InsertEdge(g1, 1, 4);
        InsertEdge(g1, 2, 3);
        InsertEdge(g1, 4, 0);
    }

    puts("Show graph");
    ShowGraph(g1);
    putchar('\n');

    puts("DFS");
    DepthFirst(g1, PrintVertex);
    putchar('\n');

    puts("Breadth Top Sort");
    BreadthTopSort(g1);
    putchar('\n');

    puts("Show reverse graph");
    Graph g2 = GraphReverse(g1);
    ShowGraph(g2);
    putchar('\n');

    int* sc = StrongComponents(g1);

    puts("Strong Components");
    for (int i = 0; i < g1->vertexCount; i++) {
        printf("Vertex %d -> Strong Component %d\n", i, sc[i]);
    }

    free(sc);
    DeleteGraph(g1);
    DeleteGraph(g2);

    return 0;
}
