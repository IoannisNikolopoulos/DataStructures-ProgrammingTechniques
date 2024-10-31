#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "quadtree.h"

Point* initPoint(float x, float y, char* name) {
	Point* newPoint = malloc(sizeof(*newPoint));
	newPoint->x = x;
	newPoint->y = y;
	newPoint->name = calloc(100 ,sizeof(char));
	strcpy(newPoint->name, name);
	return newPoint;
}

QuadTreeNode* initNode(float x, float y, float width, float height) {
	QuadTreeNode* newNode = malloc(sizeof(*newNode));

	newNode->x = x;
	newNode->y = y;
	newNode->width = width;
	newNode->height = height;
	newNode->point = NULL;
	newNode->ne = NULL;
	newNode->nw = NULL;
	newNode->se = NULL;
	newNode->sw = NULL;

	return newNode;
}

QuadTree* initQuadTree(float width, float height) {
	QuadTree* newTree = malloc(sizeof(*newTree));
	newTree->root = initNode(0, 0, width, height);
	return newTree;
}

// Return in which quadrant the point (x, y) is compared to (originX, originY)
int getQuadrant(float originX, float originY, float x, float y) {
	if (x >= originX) {
		if (y >= originY) {
			return 0;
		} else return 3;
	} else {
		if (y >= originY) {
			return 1;
		} else return 2;
	}
}

bool QuadTreeInsert(QuadTreeNode* node, Point* point) {
	// Check if space defined by node is empty
	if (node->point == NULL) {
		// Populate empty space
		node->point = point;

		// Create sub-spaces
		node->ne = initNode(point->x, point->y, node->width - (point->x - node->x), node->height - (point->y - node->y));
		node->nw = initNode(node->x, point->y, point->x - node->x, node->height - (point->y - node->y));
		node->sw = initNode(node->x, node->y, point->x - node->x, point->y - node->y);
		node->se = initNode(point->x, node->y, node->width - (point->x - node->x), point->y - node->y);

		return true;
	}

	// If space has point insert new point in one of the sub-spaces
	int quadrant = getQuadrant(node->point->x, node->point->y, point->x, point->y);
	switch (quadrant) {
		case 0:
			return QuadTreeInsert(node->ne, point);
		case 1:
			return QuadTreeInsert(node->nw, point);
		case 2:
			return QuadTreeInsert(node->sw, point);
		case 3:
			return QuadTreeInsert(node->se, point);
	}

	return false; // will never hit
}

Point* QuadTreeSearchPoint(QuadTreeNode* node, float x, float y) {
	if (node->point == NULL) {
		return NULL;
	}

	if (fabs(node->point->x - x) <= 0.00001 && fabs(node->point->y - y) <= 0.00001) {
		return node->point;
	}

	int quadrant = getQuadrant(node->point->x, node->point->y, x, y);

	switch (quadrant) {
		case 0:
			return QuadTreeSearchPoint(node->ne, x, y);
		case 1:
			return QuadTreeSearchPoint(node->nw, x, y);
		case 2:
			return QuadTreeSearchPoint(node->sw, x, y);
		case 3:
			return QuadTreeSearchPoint(node->se, x, y);
	}

	return NULL; // will never hit
}

int radiusInnerSearch(float cx, float cy, float r, float x, float y) {
	float distance = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
	if (distance <= r) return 13;

	int quadrant = getQuadrant(cx, cy, x, y);
	switch (quadrant) {
		case 0:
			return 10;
		case 1:
			return 9;
		case 2:
			return 11;
		case 3:
			return 12;
	}

	return 0; // will never hit
}

int radiusSearch(float cx, float cy, float r, float x, float y) {
	int column, row;

	if (x <= cx - r) column = 0;
	else if (x > cx - r && x <= cx + r) column = 1;
	else column = 2;

	if (y <= cy - r) row = 0;
	else if (y > cy - r && y <= cy + r) row = 1;
	else row = 2;

	if (row == 0) {
		if (column == 0) return 6;
		if (column == 1) return 7;
		if (column == 2) return 8;
	}
	if (row == 1) {
		if (column == 0) return 4;
		if (column == 1) return radiusInnerSearch(cx, cy, r, x, y);
		if (column == 2) return 5;
	}
	if (row == 2) {
		if (column == 0) return 1;
		if (column == 1) return 2;
		if (column == 2) return 3;
	}

	return 0; // will never hit
}

void QuadTreeSearchWithinRadius(
	QuadTreeNode* node,
	float centerX,
	float centerY,
	float radius,
	Point* points[],
	int* count,
	int maxPoints
) {
	if (node->point == NULL) {
		return;
	}

	int quadrant = radiusSearch(centerX, centerY, radius, node->point->x, node->point->y);

	switch (quadrant) {
		case 1:
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 2:
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 3:
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 4:
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 5:
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 6:
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 7:
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 8:
			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 9:
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 10:
			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 11:
			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 12:
			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			break;
		case 13:
			if (*count < maxPoints) {
				points[(*count)++] = node->point;
			}
			else return;

			QuadTreeSearchWithinRadius(node->nw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->sw, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->ne, centerX, centerY, radius, points, count, maxPoints);
			QuadTreeSearchWithinRadius(node->se, centerX, centerY, radius, points, count, maxPoints);
			break;
	}
}

void QuadTreePrint(QuadTreeNode* node) {
	if (node->point != NULL) {
		printf("%s (%f, %f)\n", node->point->name, node->point->x, node->point->y);
	}

	if (node->ne != NULL) {
		QuadTreePrint(node->ne);
	}
	if (node->nw != NULL) {
		QuadTreePrint(node->nw);
	}
	if (node->sw != NULL) {
		QuadTreePrint(node->sw);
	}
	if (node->se != NULL) {
		QuadTreePrint(node->se);
	}
}

void destroyPoint(Point* point) {
	free(point->name);
	free(point);
}

void destroyNode(QuadTreeNode *node) {
	if (node->point != NULL) {
		destroyPoint(node->point);
	}

	if (node->ne != NULL) {
		destroyNode(node->ne);
	}
	if (node->nw != NULL) {
		destroyNode(node->nw);
	}
	if (node->sw != NULL) {
		destroyNode(node->sw);
	}
	if (node->se != NULL) {
		destroyNode(node->se);
	}

	free(node);
}

void destroyQuadTree(QuadTree* tree) {
	destroyNode(tree->root);
	free(tree);
}
