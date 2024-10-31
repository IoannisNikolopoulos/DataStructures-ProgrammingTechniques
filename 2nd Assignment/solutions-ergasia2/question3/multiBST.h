/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#ifndef MULTI_BST_H
#define MULTI_BST_H

#include "Item.h"

typedef struct BSTnode* BST;

BST BSTinit();
 int BSTcount(BST);
 BST BSTinsert(BST, Item);
Item BSTsearch(BST, Key);
 BST BSTdelete(BST, Key);
Item BSTselect(BST, int);
void BSTsort(BST, void (*visit)(Item));
 int BSTheight(BST);
void BSTclear(BST);
 int BSTcountLeaves(BST);
void BSTlevelOrder(BST);
Item BSTfloor(BST, Key);
Item BSTceiling(BST, Key);
void BSTrangeSearch(BST, Key low, Key high);
 int BSTcountRange(BST, Key low, Key high);
 int isBST(BST);

#endif // MULTI_BST_H
