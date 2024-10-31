/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "deque.h"

typedef struct BSTnode* link;

// Definition of the binary search tree node structure
struct BSTnode {
  Item item; // The item stored in the node
  link l, r; // Pointers to the left and right children
  int N;     // Size of the subtree rooted at this node
};

static link head, z;

// Function to create a new node
link NEW(Item item, link l, link r, int N) {
  link x = malloc(sizeof *x);
  x->item = item;
  x->l = l;
  x->r = r;
  x->N = N;
  return x;
}

// Initialization of the BST
void BSTinit() {
  z = NEW(NULLitem, NULL, NULL, 0); // Create a sentinel node
  head = z; // Set the head to the sentinel node
}

// Return the number of nodes in the BST
int BSTcount() { return head->N; }

// Recursive search function
Item searchR(link h, Key v) {
  if (h == z) return NULLitem; // Base case: reached the sentinel node
  Key t = key(h->item);
  if eq(v, t) return h->item; // Key found
  if less(v, t) return searchR(h->l, v); // Search in the left subtree
  else return searchR(h->r, v); // Search in the right subtree
}

// Search function
Item BSTsearch(Key v) {
  return searchR(head, v);
}

// Recursive insertion function
link insertR(link h, Item item) {
  if (h == z) return NEW(item, z, z, 1); // Insert a new node

  Key v = key(item);
  Key t = key(h->item);

  if (less(v, t)) h->l = insertR(h->l, item); // Insert in the left subtree
  else h->r = insertR(h->r, item); // Insert in the right subtree

  (h->N)++; // Update the size of the subtree
  return h;
}

// Insertion function
void BSTinsert(Item item) { head = insertR(head, item); }

// Right rotation function
link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

// Left rotation function
link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

// Recursive sort function
void sortR(link h, void (*visit)(Item)) {
  if (h == z) return; // Base case: reached the sentinel node

  sortR(h->l, visit); // Visit left subtree
  visit(h->item); // Visit current node
  sortR(h->r, visit); // Visit right subtree
}

// Sort function
void BSTsort(void (*visit)(Item)) { sortR(head, visit); }

// Recursive select function
Item selectR(link h, int k) {
  if (h == z) return NULLitem; // Base case: reached the sentinel node

  int t = (h->l == z) ? 0 : h->l->N;

  if (t > k) return selectR(h->l, k); // Select in the left subtree
  if (t < k) return selectR(h->r, k-t-1); // Select in the right subtree

  return h->item; // Node found
}

// Select function
Item BSTselect(int k) { return selectR(head, k); }

// Partition function
link partR(link h, int k) {
  int t = h->l->N;
  if (t > k) {
    h->l = partR(h->l, k);
    h = rotR(h);
  }
  if (t < k) {
    h->r = partR(h->r, k-t-1);
    h = rotL(h);
  }
  return h;
}

// Join left and right subtrees
link joinLR(link a, link b) {
  if (b == z) return a;
  b = partR(b, 0);
  b->l = a;
  return b;
}

// Recursive deletion function
link deleteR(link h, Key v) {
  if (h == z) return z; // Base case: reached the sentinel node

  link x;
  Key t = key(h->item);

  if (less(v, t)) h->l = deleteR(h->l, v); // Delete in the left subtree
  if (less(t, v)) h->r = deleteR(h->r, v); // Delete in the right subtree

  if (eq(v, t)) {
    x = h;
    h = joinLR(h->l, h->r); // Join the left and right subtrees
    ITEMfree(x->item);
    free(x);
  }

  return h;
}

// Delete function
void BSTdelete(Key v) { head = deleteR(head, v); }

// Recursive height calculation function
int heightR(link h) {
  if (h == z) return 0; // Base case: reached the sentinel node

  int leftHeight = heightR(h->l);
  int rightHeight = heightR(h->r);

  int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;

  return maxHeight + 1;
}

// Height function
int BSTheight() { return heightR(head); }

// Recursive clear function
void clearR(link h) {
  if (h == z) return; // Base case: reached the sentinel node

  clearR(h->l);
  clearR(h->r);

  ITEMfree(h->item);
  free(h);
}

// Clear function
void BSTclear() { clearR(head); }

// Recursive leaf count function
int countLeavesR(link h) {
  if (h == z) return 0; // Base case: reached the sentinel node
  if (h->N == 1) return 1; // Leaf node

  int leftLeaves = countLeavesR(h->l);
  int rightLeaves = countLeavesR(h->r);

  return leftLeaves + rightLeaves;
}

// Leaf count function
int BSTcountLeaves() { return countLeavesR(head); }

// Level-order traversal function
void BSTlevelOrder() {
  Deque q = createDeque();
  dequeEnque(q, head);

  while (!dequeIsEmpty(q)) {
    link node = dequeDequeue(q);
    printf("%s ", key(node->item));

    if (node->l != z) dequeEnque(q, node->l);
    if (node->r != z) dequeEnque(q, node->r);
  }
}

// Find the largest item less than or equal to the given key
Item BSTfloor(Key key) {
  Key maxKey = NULLkey;
  Item maxItem = NULLitem;

  link current = head;
  while (current != z) {
    if (less(key(current->item), key)) {
      if (less(maxKey, key(current->item))) {
        maxKey = key(current->item);
        maxItem = current->item;
      }
      current = current->r;
    } else current = current->l;
  }

  return maxItem;
}

// Find the smallest item greater than or equal to the given key
Item BSTceiling(Key key) {
  Key minKey = NULLkey;
  Item minItem = NULLitem;

  link current = head;
  while (current != z) {
    if (less(key, key(current->item))) {
      if (eq(minKey, NULLkey) || less(key(current->item), minKey)) {
        minKey = key(current->item);
        minItem = current->item;
      }
      current = current->l;
    } else current = current->r;
  }

  return minItem;
}

// Recursive range search function
void rangeSearchR(link h, Key low, Key high) {
  if (h == z) return; // Base case: reached the sentinel node

  rangeSearchR(h->l, low, high); // Visit left subtree

  Key nodeKey = key(h->item);
  if (leq(low, nodeKey) && leq(nodeKey, high)) {
    ITEMshow(h->item); // Visit current node if within range
  }

  rangeSearchR(h->r, low, high); // Visit right subtree
}

// Range search function
void BSTrangeSearch(Key low, Key high) { rangeSearchR(head, low, high); }

// Recursive count of items within range
int countRangeR(link h, Key low, Key high) {
  if (h == z) return 0; // Base case: reached the sentinel node

  int count = 0;
  count += countRangeR(h->l, low, high);
  count += countRangeR(h->r, low, high);

  Key nodeKey = key(h->item);
  if (leq(low, nodeKey) && leq(nodeKey, high)) {
    count++;
  }

  return count;
}

// Count of items within range function
int BSTcountRange(Key low, Key high) { return countRangeR(head, low, high); }

// Check if the tree is a BST (helper function)
int isBSTR(link h) {
  if (h == z) return 1; // Base case: reached the sentinel node

  int leftBST = isBSTR(h->l);
  int rightBST = isBSTR(h->r);

  if (leftBST == 0 || rightBST == 0) return 0;

  Key leftKey = NULLkey;
  if (h->l != z) {
    leftKey = key(h->l->item);
  }

  Key rightKey = NULLkey;
  if (h->r != z) {
    rightKey = key(h->r->item);
  }

  if (
    (eq(leftKey, NULLkey) || less(leftKey, key(h->item))) &&
    (eq(rightKey, NULLkey) || less(key(h->item), rightKey))
  ) return 1;

  return 0;
}

// Check if the tree is a BST function
int isBST() { return isBSTR(head); }
