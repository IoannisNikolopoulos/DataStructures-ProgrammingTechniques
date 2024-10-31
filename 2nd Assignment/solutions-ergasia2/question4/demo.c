#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"

int main() {
	printf("Creating QuadTree...");
	QuadTree* tree = initQuadTree(100, 100);
	printf("done\n");
	putchar('\n');

	printf("Inserting point Ioannina at (39.66486, 20.85189)\n");
	QuadTreeInsert(tree->root, initPoint(39.66486, 20.85189, "Ioannina"));
	printf("Inserting point Athens at (37.98376, 23.72784)\n");
	QuadTreeInsert(tree->root, initPoint(37.98376, 23.72784, "Athens"));
	printf("Inserting point Thesaloniki at (40.64361, 22.93086)\n");
	QuadTreeInsert(tree->root, initPoint(40.64361, 22.93086, "Thesaloniki"));
	printf("Inserting point Volos at (39.36103, 22.94248)\n");
	QuadTreeInsert(tree->root, initPoint(39.36103, 22.94248, "Volos"));
	printf("Inserting point Patra at (38.24444, 21.73444)\n");
	QuadTreeInsert(tree->root, initPoint(38.24444, 21.73444, "Patra"));
	printf("Inserting point Rethymno at (35.36555, 24.48232)\n");
	QuadTreeInsert(tree->root, initPoint(35.36555, 24.48232, "Rethymno"));
	printf("Inserting point Kalamata at (37.03913, 22.11265)\n");
	QuadTreeInsert(tree->root, initPoint(37.03913, 22.11265, "Kalamata"));
	printf("Inserting point Alexandroupoli at (40.84995, 25.87644)\n");
	QuadTreeInsert(tree->root, initPoint(40.84995, 25.87644, "Alexandroupoli"));
	printf("Inserting point Corfu at (39.62441, 19.92016)\n");
	QuadTreeInsert(tree->root, initPoint(39.62441, 19.92016, "Corfu"));
	printf("Inserting point Heraklion at (35.32787, 25.14341)\n");
	QuadTreeInsert(tree->root, initPoint(35.32787, 25.14341, "Heraklion"));
	printf("Inserting point Larisa at (39.63689, 22.41761)\n");
	QuadTreeInsert(tree->root, initPoint(39.63689, 22.41761, "Larisa"));
	printf("Inserting point Serres at (41.08499, 23.54757)\n");
	QuadTreeInsert(tree->root, initPoint(41.08499, 23.54757, "Serres"));

	putchar('\n');
	printf("Points in QuadTree:\n");
	QuadTreePrint(tree->root);

	Point* foundPoint;

	putchar('\n');
	printf("Searching for point at (39.36103, 22.94248)\n");
	foundPoint = QuadTreeSearchPoint(tree->root, 39.36103, 22.94248);
	if (foundPoint != NULL) {
		printf("Found point: %s\n", foundPoint->name);
	} else {
		printf("Point not found\n");
	}

	putchar('\n');
	printf("Searching for point at (35.32787, 25.14341)\n");
	foundPoint = QuadTreeSearchPoint(tree->root, 35.32787, 25.14341);
	if (foundPoint != NULL) {
		printf("Found point: %s\n", foundPoint->name);
	} else {
		printf("Point not found\n");
	}

	putchar('\n');
	printf("Searching for point at (50.98376, 50.72784)\n");
	foundPoint = QuadTreeSearchPoint(tree->root, 50.98376, 50.72784);
	if (foundPoint != NULL) {
		printf("Found point: %s\n", foundPoint->name);
	} else {
		printf("Point not found\n");
	}

	putchar('\n');

	float centerX = 39.36103, centerY = 22.94248, radius = 1.6;
	int maxPoints = 20, count = 0;
	printf("Searching points within radius of %.2f grid units from (%.5f, %.5f):\n", radius, centerX, centerY);

	Point** points = malloc(maxPoints * sizeof(Point*));
	QuadTreeSearchWithinRadius(tree->root, centerX, centerY, radius, points, &count, maxPoints);

	printf("Found %d points\n", count);
	for (int i = 0; i < count; i++) {
		printf("%s at (%.5f, %.5f)\n", points[i]->name, points[i]->x, points[i]->y);
	}

	free(points);

	destroyQuadTree(tree);

	return 0;
}
