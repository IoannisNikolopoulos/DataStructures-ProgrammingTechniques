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
        int start = 0, end = 0;
        bool writeEnd = false;

        while (c = getchar(), c != EOF) {
            if (isdigit(c)) {
                if (i == 0) g = Initialize(c - '0');
                else if (writeEnd) end = c - '0';
                else start = c - '0';
            }

            if (c == '-') {
                writeEnd = true;
            }

            if (c == '\n' && writeEnd == true) {
                writeEnd = false;
                InsertEdge(g, start, end);
            }

            i++;
        }
    }
    else {
        g = Initialize(6); // Create a graph with 5 vertices
        InsertEdge(g, 0, 1);
        InsertEdge(g, 0, 2);
        InsertEdge(g, 1, 2);
        InsertEdge(g, 1, 3);
        InsertEdge(g, 1, 4);
        InsertEdge(g, 2, 3);
        InsertEdge(g, 4, 0);
    }

    puts("Show graph");
    ShowGraph(g);
    putchar('\n');

    printf("Find path from 0 to 3\n");
    Vertex* path = SimplePathCheck(g, 0, 3);
    if (path != NULL) {
        printf("Path: ");
        for (int i = 0; path[i] != -1 && i < g->vertexCount; i++) {
            printf("%d ", path[i]);
        }
        putchar('\n');
        free(path);
    }
    else {
        puts("No path found");
    }

    putchar('\n');
    printf("Find path from 4 to 5\n");
    path = SimplePathCheck(g, 4, 5);
    if (path != NULL) {
        printf("Path: ");
        for (int i = 0; path[i] != -1 && i < g->vertexCount; i++) {
            printf("%d ", path[i]);
        }
        putchar('\n');
        free(path);
    }
    else {
        puts("No path found");
    }

    DeleteGraph(g);

    return 0;
}
