#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdbool.h>

typedef struct Point {
	float x, y;
	char* name; // City name
} Point;

typedef struct QuadTreeNode {
	Point* point;
	float x, y;
	float width, height;
	struct QuadTreeNode *nw, *ne, *sw, *se;
} QuadTreeNode;

typedef struct QuadTree {
	QuadTreeNode* root;
} QuadTree;

Point* initPoint(float x, float y, char* name);
QuadTreeNode* initNode(float x, float y, float width, float height);
QuadTree* initQuadTree(float width, float height);

bool QuadTreeInsert(QuadTreeNode* node, Point* point);
Point* QuadTreeSearchPoint(QuadTreeNode* node, float x, float y);
void QuadTreeSearchWithinRadius(QuadTreeNode* node, float centerX, float centerY, float radius, Point* points[], int* count, int maxPoints);

void QuadTreePrint(QuadTreeNode* node);

void destroyPoint(Point* point);
void destroyNode(QuadTreeNode* node);
void destroyQuadTree(QuadTree* tree);

#endif // QUADTREE_H
