#include "acutest/acutest.h"
#include <stdio.h>
#include <stdlib.h>
#include "directed_graph.h"

void testInitialize(){
    Graph graph = Initialize(5);
    TEST_CHECK(graph != NULL);
    TEST_CHECK(graph->vertexCount == 5);
    TEST_CHECK(graph->edges != NULL);
    TEST_CHECK(graph->edges[4] == NULL);
    DeleteGraph(graph);
}

void testInsertEdge(){
    Graph graph = Initialize(5);
    InsertEdge(graph, 0, 2);
    TEST_CHECK(graph->edges[0] != NULL);
    TEST_CHECK(graph->edges[0]->endVertex == 2);
    InsertEdge(graph, 0, 4);
    TEST_CHECK(graph->edges[0]->next != NULL);
    TEST_CHECK(graph->edges[0]->next->endVertex == 4);
    InsertEdge(graph, 0, 3);
    TEST_CHECK(graph->edges[0]->next != NULL);
    TEST_CHECK(graph->edges[0]->next->endVertex == 3);
    TEST_CHECK(graph->edges[0]->next->next != NULL);
    TEST_CHECK(graph->edges[0]->next->next->endVertex == 4);
    InsertEdge(graph, 0, 1);
    TEST_CHECK(graph->edges[0]->endVertex == 1);
    TEST_CHECK(graph->edges[0]->next->endVertex == 2);
    InsertEdge(graph, 1, 2);
    TEST_CHECK(graph->edges[1] != NULL);
    TEST_CHECK(graph->edges[1]->endVertex == 2);
}

char* readFile(const char* filename) {
    // Read the output from the file
    FILE *fp = fopen("test_output.txt", "r");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *output = (char *)malloc(fsize + 1);
    fread(output, 1, fsize, fp);
    output[fsize] = '\0';
    fclose(fp);

    return output;
}

void testShowGraph() {
    Graph graph = Initialize(5);
    InsertEdge(graph, 0, 1);
    InsertEdge(graph, 0, 4);
    InsertEdge(graph, 1, 2);
    InsertEdge(graph, 2, 3);
    InsertEdge(graph, 3, 4);

    // Redirect stdout to a buffer
    FILE *fp = freopen("test_output.txt", "w", stdout);
    ShowGraph(graph);
    fclose(fp);

#ifdef _WIN32
    freopen("CON", "w", stdout);
#elif defined __unix__
    freopen("/dev/tty", "w", stdout);
#endif

    char *output = readFile("test_output.txt");

    // Expected output
    const char *expected_output = "0: 1 4\n1: 2\n2: 3\n3: 4\n4:\n";
    TEST_CHECK(strcmp(output, expected_output) == 0);

    // Clean up
    free(output);
    DeleteGraph(graph);
}

Vertex visitOrder[5];
int currentIndex = 0;

void RecordVisitOrder(Vertex v) {
    visitOrder[currentIndex++] = v;
}

void testDepthFirst(){
    Graph graph = Initialize(5);
    InsertEdge(graph, 0, 1);
    InsertEdge(graph, 0, 4);
    InsertEdge(graph, 1, 2);
    InsertEdge(graph, 2, 3);
    InsertEdge(graph, 3, 4);

    DepthFirst(graph, RecordVisitOrder);

    // Expected DFS order
    int expectedOrder[] = {0, 1, 2, 3, 4};

    TEST_CHECK(currentIndex == 5);
    TEST_CHECK(memcmp(visitOrder, expectedOrder, sizeof(expectedOrder)) == 0);

    DeleteGraph(graph);
}

void testBreadthTopSort() {
    Graph graph = Initialize(5);
    InsertEdge(graph, 0, 1);
    InsertEdge(graph, 0, 2);
    InsertEdge(graph, 0, 3);
    InsertEdge(graph, 0, 4);
    InsertEdge(graph, 1, 3);
    InsertEdge(graph, 2, 4);
    InsertEdge(graph, 3, 4);

    // Redirect stdout to a file
    FILE *fp = freopen("test_output.txt", "w", stdout);
    BreadthTopSort(graph);
    fclose(fp);

#ifdef _WIN32
    freopen("CON", "w", stdout);
#elif defined __unix__
    freopen("/dev/tty", "w", stdout);
#endif

    char *output = readFile("test_output.txt");

    // Expected output
    const char *expected_output =
        "Vertex: 0\n"
        "Vertex: 2\n"
        "Vertex: 1\n"
        "Vertex: 3\n"
        "Vertex: 4\n";

    TEST_CHECK(strcmp(output, expected_output) == 0);

    // Clean up
    free(output);
    DeleteGraph(graph);
}

void testGraphReverse() {
    Graph graph = Initialize(6);
    InsertEdge(graph, 0, 1);
    InsertEdge(graph, 0, 2);
    InsertEdge(graph, 1, 3);
    InsertEdge(graph, 1, 4);
    InsertEdge(graph, 2, 4);
    InsertEdge(graph, 3, 5);
    InsertEdge(graph, 4, 5);

    Graph reversedGraph = GraphReverse(graph);

    // Check the reversed edges
    TEST_CHECK(reversedGraph->edges[1]->endVertex == 0);
    TEST_CHECK(reversedGraph->edges[2]->endVertex == 0);
    TEST_CHECK(reversedGraph->edges[3]->endVertex == 1);
    TEST_CHECK(reversedGraph->edges[4]->endVertex == 1);
    TEST_CHECK(reversedGraph->edges[4]->next->endVertex == 2);
    TEST_CHECK(reversedGraph->edges[5]->endVertex == 3);
    TEST_CHECK(reversedGraph->edges[5]->next->endVertex == 4);

    // Clean up
    DeleteGraph(graph);
    DeleteGraph(reversedGraph);
}

void testStrongComponents() {
    Graph g = Initialize(5);
    InsertEdge(g, 0, 1);
    InsertEdge(g, 0, 2);
    InsertEdge(g, 1, 2);
    InsertEdge(g, 1, 3);
    InsertEdge(g, 1, 4);
    InsertEdge(g, 2, 3);
    InsertEdge(g, 4, 0);

    int* sc = StrongComponents(g);

    TEST_CHECK(sc[0] == 1);
    TEST_CHECK(sc[1] == 1);
    TEST_CHECK(sc[2] == 2);
    TEST_CHECK(sc[3] == 3);
    TEST_CHECK(sc[4] == 1);
}

TEST_LIST = {
    { "initialize", testInitialize },
    { "insert edge", testInsertEdge },
    { "show graph", testShowGraph },
    { "depth first search", testDepthFirst },
    { "breadth top sort", testBreadthTopSort },
    { "reverse graph", testGraphReverse },
    { "strong components", testStrongComponents },
    { NULL, NULL }
};
