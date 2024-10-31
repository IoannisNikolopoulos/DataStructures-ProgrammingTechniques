/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "deque.h"

// Typedef for a pointer to a BST node
typedef struct BSTnode* link;
typedef link BST;

// Definition of a BST node structure
struct BSTnode {
  Item item;  // Item stored in the node
  link l, r;  // Pointers to left and right children
  int N;      // Size of the subtree rooted at this node
};

static link z;  // Sentinel node for the BST

// Function to create a new BST node
link NEW(Item item, link l, link r, int N) {
  link x = malloc(sizeof *x);  // Allocate memory for the new node

  x->item = item;  // Set the item
  x->l = l;        // Set the left child
  x->r = r;        // Set the right child
  x->N = N;        // Set the size of the subtree

  return x;        // Return the new node
}

/* initialization operation */
// Function to initialize the BST
link BSTinit() {
  z = NEW(NULLitem, NULL, NULL, 0);  // Create and return the sentinel node
  return z;
}

/* count operation */
// Function to get the size of the BST
int BSTcount(BST head) {
  return head->N;
}

/* search operation */
// Recursive function to search for a key in the BST
Item searchR(link h, Key v) {
  if (h == z) return NULLitem;  // If reached sentinel node, return NULLitem
  Key t = key(h->item);         // Get the key of the current item
  if (eq(v, t)) return h->item; // If keys match, return the item
  if (less(v, t)) return searchR(h->l, v); // Recur to the left child if key is less
  else return searchR(h->r, v);            // Recur to the right child if key is greater
}

// Function to search for a key in the BST
Item BSTsearch(BST head, Key v) {
  return searchR(head, v);
}

/* recursive insert operation */
// Recursive function to insert an item into the BST
link insertR(link h, Item item) {
  if (h == z) return NEW(item, z, z, 1);  // If reached sentinel node, create a new node

  Key v = key(item);     // Get the key of the item to be inserted
  Key t = key(h->item);  // Get the key of the current item

  if (less(v, t)) h->l = insertR(h->l, item);  // Recur to the left child if key is less
  else h->r = insertR(h->r, item);             // Recur to the right child if key is greater

  (h->N)++;  // Increment the size of the subtree
  return h;  // Return the current node
}

// Function to insert an item into the BST
BST BSTinsert(BST head, Item item) {
  return insertR(head, item);
}

/* rotation auxiliary functions */
// Function to perform a right rotation
link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

// Function to perform a left rotation
link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

/* sort operation */
// Recursive function to traverse and visit nodes in sorted order
void sortR(link h, void (*visit)(Item)) {
  if (h == z) return;  // If reached sentinel node, return

  sortR(h->l, visit);  // Recur to the left child
  visit(h->item);      // Visit the current node
  sortR(h->r, visit);  // Recur to the right child
}

// Function to sort and visit nodes in the BST
void BSTsort(BST head, void (*visit)(Item)) {
  sortR(head, visit);
}

/* select operation */
// Recursive function to select the k-th smallest item
Item selectR(link h, int k) {
  if (h == z) return NULLitem;  // If reached sentinel node, return NULLitem

  int t = (h->l == z) ? 0 : h->l->N;  // Get the size of the left subtree

  if (t > k) return selectR(h->l, k);       // Recur to the left child if k is less
  if (t < k) return selectR(h->r, k - t - 1); // Recur to the right child if k is greater

  return h->item;  // Return the current node's item
}

// Function to select the k-th smallest item in the BST
Item BSTselect(BST head, int k) {
  return selectR(head, k);
}

/* partition auxiliary function */
// Recursive function to partition the tree around the k-th smallest item
link partR(link h, int k) {
  int t = h->l->N;  // Get the size of the left subtree
  if (t > k) {
    h->l = partR(h->l, k);  // Recur to the left child
    h = rotR(h);            // Perform a right rotation
  }
  if (t < k) {
    h->r = partR(h->r, k - t - 1);  // Recur to the right child
    h = rotL(h);                   // Perform a left rotation
  }
  return h;  // Return the current node
}

/* recursive deletion operation */
// Recursive function to join two subtrees
link joinLR(link a, link b) {
  if (b == z) return a;  // If the right subtree is empty, return the left subtree
  b = partR(b, 0);       // Partition the right subtree
  b->l = a;              // Set the left child of the partitioned node
  return b;              // Return the new root
}

// Recursive function to delete a node with the given key
link deleteR(link h, Key v) {
  if (h == z) return z;  // If reached sentinel node, return sentinel

  link x;
  Key t = key(h->item);  // Get the key of the current item

  if (less(v, t)) h->l = deleteR(h->l, v); // Recur to the left child if key is less
  if (less(t, v)) h->r = deleteR(h->r, v); // Recur to the right child if key is greater

  if (eq(v, t)) {  // If keys match
    x = h;
    h = joinLR(h->l, h->r);  // Join the left and right subtrees
    ITEMfree(x->item);       // Free the item
    free(x);                 // Free the node
  }

  return h;  // Return the current node
}

// Function to delete a node with the given key in the BST
BST BSTdelete(BST head, Key v) {
  return deleteR(head, v);
}

// Recursive function to compute the height of the BST
int heightR(link h) {
  if (h == z) return 0;  // If reached sentinel node, return 0

  int leftHeight = heightR(h->l);   // Get the height of the left subtree
  int rightHeight = heightR(h->r);  // Get the height of the right subtree

  int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight; // Get the maximum height

  return maxHeight + 1;  // Return the height of the current node
}

// Function to compute the height of the BST
int BSTheight(BST head) {
  return heightR(head);
}

// Recursive function to clear the BST
void clearR(link h) {
  if (h == z) return;  // If reached sentinel node, return

  clearR(h->l);  // Recur to the left child
  clearR(h->r);  // Recur to the right child

  ITEMfree(h->item);  // Free the item
  free(h);            // Free the node
}

// Function to clear the BST
void BSTclear(BST head) {
  clearR(head);
}

// Recursive function to count the leaves in the BST
int countLeavesR(link h) {
  if (h == z) return 0;  // If reached sentinel node, return 0
  if (h->N == 1) return 1;  // If the node is a leaf, return 1

  int leftLeaves = countLeavesR(h->l);  // Count the leaves in the left subtree
  int rightLeaves = countLeavesR(h->r); // Count the leaves in the right subtree

  return leftLeaves + rightLeaves;  // Return the total count
}

// Function to count the leaves in the BST
int BSTcountLeaves(BST head) {
  return countLeavesR(head);
}

// Function to perform a level order traversal of the BST
void BSTlevelOrder(BST head) {
  Deque q = createDeque();
  dequeEnque(q, head);

  while (!dequeIsEmpty(q)) {
    link node = dequeDequeue(q);
    printf("%s ", key(node->item));

    if (node->l != z) dequeEnque(q, node->l);
    if (node->r != z) dequeEnque(q, node->r);
  }
}

// Function to find the floor (greatest item less than or equal to the given key)
Item BSTfloor(BST head, Key key) {
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
    } else {
      current = current->l;
    }
  }

  return maxItem;
}

// Function to find the ceiling (smallest item greater than or equal to the given key)
Item BSTceiling(BST head, Key key) {
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
    } else {
      current = current->r;
    }
  }

  return minItem;
}

// Recursive function to perform a range search in the BST
void rangeSearchR(link h, Key low, Key high) {
  if (h == z) return;  // If reached sentinel node, return

  rangeSearchR(h->l, low, high);  // Recur to the left child

  Key nodeKey = key(h->item);
  if (leq(low, nodeKey) && leq(nodeKey, high)) {  // Check if the current node's key is within the range
    ITEMshow(h->item);  // Show the item
  }

  rangeSearchR(h->r, low, high);  // Recur to the right child
}

// Function to perform a range search in the BST
void BSTrangeSearch(BST head, Key low, Key high) {
  rangeSearchR(head, low, high);
}

// Recursive function to count the items in a given range
int countRangeR(link h, Key low, Key high) {
  if (h == z) return 0;  // If reached sentinel node, return 0

  int count = 0;
  count += countRangeR(h->l, low, high);  // Count the items in the left subtree
  count += countRangeR(h->r, low, high);  // Count the items in the right subtree

  Key nodeKey = key(h->item);
  if (leq(low, nodeKey) && leq(nodeKey, high)) {  // Check if the current node's key is within the range
    count++;  // Increment the count
  }

  return count;  // Return the total count
}

// Function to count the items in a given range in the BST
int BSTcountRange(BST head, Key low, Key high) {
  return countRangeR(head, low, high);
}

// Recursive function to check if the tree is a valid BST
int isBSTR(link h) {
  if (h == z) return 1;  // If reached sentinel node, return true

  int leftBST = isBSTR(h->l);   // Check if the left subtree is a BST
  int rightBST = isBSTR(h->r);  // Check if the right subtree is a BST

  if (leftBST == 0 || rightBST == 0) return 0;  // If either subtree is not a BST, return false

  Key leftKey = NULLkey;
  if (h->l != z) {
    leftKey = key(h->l->item);
  }

  Key rightKey = NULLkey;
  if (h->r != z) {
    rightKey = key(h->r->item);
  }

  // Check if the current node's key is greater than the left child's key and less than the right child's key
  if ((eq(leftKey, NULLkey) || less(leftKey, key(h->item))) &&
      (eq(rightKey, NULLkey) || less(key(h->item), rightKey))) {
    return 1;  // Return true
  }

  return 0;  // Return false
}

// Function to check if the tree is a valid BST
int isBST(BST head) {
  return isBSTR(head);
}

