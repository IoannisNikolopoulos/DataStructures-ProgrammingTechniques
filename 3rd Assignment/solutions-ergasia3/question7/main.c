#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "undirected_graph.h"
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char* argv[]){

    Graph g;
    if (argc > 1 && strcmp(argv[1], "-") == 0) {
        int i = 0;
        char c = '\0';
        int start = 0, end = 0, weight = 0;
        int write = 0;

        while (c = getchar(), c != EOF) {
            if (isdigit(c)) {
                if (i == 0) g = Initialize(c - '0');
                else if (write == 1) end = c - '0';
                else if (write == 2) weight = c - '0';
                else start = c - '0';
            }

            if (c == '-') {
                write += 1;
            }

            if (c == '\n' && write != 0) {
                write = 0;
                InsertEdge(g, start, end, weight);
            }

            i++;
        }
    }
    else {
        g = Initialize(9); // Create a graph with 5 vertices
        InsertEdge(g, 0, 1, 4);
        InsertEdge(g, 0, 7, 8);
        InsertEdge(g, 1, 7, 11);
        InsertEdge(g, 1, 2, 8);
        InsertEdge(g, 7, 8, 7);
        InsertEdge(g, 7, 6, 1);
        InsertEdge(g, 6, 8, 6);
        InsertEdge(g, 8, 2, 2);
        InsertEdge(g, 2, 3, 7);
        InsertEdge(g, 2, 5, 4);
        InsertEdge(g, 3, 5, 14);
        InsertEdge(g, 3, 4, 9);
        InsertEdge(g, 5, 4, 10);
        InsertEdge(g, 5, 6, 2);
    }

    puts("Show graph");
    ShowGraph(g);
    putchar('\n');

    Graph mst = MinimumSpanningTree(g);


    puts("Show mst");
    ShowGraph(mst);
    putchar('\n');

    DeleteGraph(g);

    return 0;
}
