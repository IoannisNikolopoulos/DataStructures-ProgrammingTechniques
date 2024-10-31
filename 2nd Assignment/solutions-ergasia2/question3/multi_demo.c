/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include "Item.h"
#include "multiBST.h"

int main(int argc, char *argv[]) {
   // Initialize the binary search tree (BST) for books
   BST books = BSTinit();

   puts("Creating new books");

   // Loop to insert 5 items into the BST
   for (int i = 0; i < 5; i++) {
      // Read a new item
      Item newItem = ITEMscan();

      // Check if the item already exists in the BST
      if (BSTsearch(books, key(newItem)) != NULLitem) continue;

      // Insert the new item into the BST
      books = BSTinsert(books, newItem);
   }

   puts("Sorted items");

   // Print the items in the BST in sorted order
   BSTsort(books, ITEMshow);

   // Print the number of distinct keys in the BST
   printf("The BST has %d distinct keys\n", BSTcount(books));

   // Select the item with the fourth smallest key
   Item i = BSTselect(books, 3);
   puts("The item with the fourth smallest key is:");

   // Display the selected item
   ITEMshow(i);

   // Delete the selected item from the BST
   BSTdelete(books, key(i));

   // Print the items in the BST in sorted order after deletion
   printf("After the one deletion the keys in sorted order are: ");
   BSTsort(books, ITEMshow);

   return 0;
}
