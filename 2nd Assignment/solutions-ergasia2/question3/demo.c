/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "BST.h"

int main(int argc, char *argv[]) {
   // Initialize the BST
   BSTinit();

   // Insert some items into the BST
   BSTinsert(ITEMcreate("123456789", "Book1", "Author1", 2000));
   BSTinsert(ITEMcreate("234567890", "Book2", "Author2", 2005));
   BSTinsert(ITEMcreate("345678901", "Book3", "Author3", 2010));
   BSTinsert(ITEMcreate("456789012", "Book4", "Author4", 2015));
   BSTinsert(ITEMcreate("567890123", "Book5", "Author5", 2020));

   // Display the number of items in the BST
   printf("Number of items in the BST: %d\n", BSTcount());

   // Select the item with the fourth smallest key
   Item i=BSTselect(3);
   puts("The item with the fourth smallest key is:");
   ITEMshow(i);

   // Delete the item with the fourth smallest key
   BSTdelete(key(i));
   printf("After the one deletion the keys in sorted order are: ");
   BSTsort(ITEMshow);

   // Perform a search
   char* search_key = "345678901";
   Item found_item = BSTsearch(search_key);
   if (found_item != NULLitem) {
       printf("Item with ISBN %s found: \n", search_key);
       ITEMshow(found_item);
   } else {
       printf("Item with ISBN %s not found.\n", search_key);
   }

   // Display the items in sorted order
   printf("Items in sorted order: \n");
   BSTsort(ITEMshow);

   // Display the height of the BST
   printf("Height of the BST: %d\n", BSTheight());

   // Display the number of leaf nodes in the BST
   printf("Number of leaf nodes in the BST: %d\n", BSTcountLeaves());

   // Perform range search
   printf("Items between ISBN '200000000' and '400000000': \n");
   BSTrangeSearch("200000000", "400000000");

   // Delete an item
   char* delete_key = "234567890";
   BSTdelete(delete_key);
   printf("Deleted item with ISBN %s.\n", delete_key);

   // Display the items in sorted order after deletion
   printf("Items in sorted order after deletion: \n");
   BSTsort(ITEMshow);

   // Clear the BST
   BSTclear();
   printf("BST cleared.\n");

   return 0;
}
