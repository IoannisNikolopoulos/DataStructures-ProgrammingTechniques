/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#ifndef BST_H
#define BST_H

#include "Item.h"

void BSTinit();
 int BSTcount();
void BSTinsert(Item);
Item BSTsearch(Key);
void BSTdelete(Key);
Item BSTselect(int);
void BSTsort(void (*visit)(Item));
 int BSTheight();
void BSTclear();
 int BSTcountLeaves();
void BSTlevelOrder();
Item BSTfloor(Key key);
Item BSTceiling(Key key);
void BSTrangeSearch(Key low, Key high);
 int BSTcountRange(Key low, Key high);
 int isBST();

#endif // BST_H
