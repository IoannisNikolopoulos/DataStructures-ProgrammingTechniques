/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a structure to represent a book item
struct item {
  char* isbn;    
  char* title;   
  char* author; 
  int year;      
};

typedef struct item* Item;
typedef char* Key;

// Function to create a new book item with the given details
Item ITEMcreate(char* isbn, char* title, char* author, int year) {
  Item newItem = malloc(sizeof(*newItem));         // Allocate memory for the new item
  newItem->isbn = malloc(21 * sizeof(*(newItem->isbn)));     
  newItem->title = malloc(51 * sizeof(*(newItem->title)));   
  newItem->author = malloc(101 * sizeof(*(newItem->author))); 

  strcpy(newItem->isbn, isbn);       
  strcpy(newItem->title, title);   
  strcpy(newItem->author, author);   
  newItem->year = year;             

  return newItem;                   
}

// Function to scan and create a new book item with user input
Item ITEMscan() {
  Item newItem = malloc(sizeof(struct item));       
  newItem->isbn = malloc(21 * sizeof(*(newItem->isbn)));    
  newItem->title = malloc(51 * sizeof(*(newItem->title)));   
  newItem->author = malloc(101 * sizeof(*(newItem->author))); 

  puts("Insert new book");           // Prompt user for new book details
  printf("isbn: ");
  scanf("%20s", newItem->isbn);    
  printf("title: ");
  scanf("%50s", newItem->title);     
  printf("author: ");
  scanf("%100s", newItem->author);   
  printf("year: ");
  scanf("%d", &(newItem->year));     

  return newItem;                   
}

// Function to display the details of a book item
void ITEMshow(Item x) {
  printf("%s\n%s\n%s\n%d\n", x->isbn, x->title, x->author, x->year);  // Print ISBN, title, author, and year
}

// Function to free the memory allocated for a book item
void ITEMfree(Item x) {
  free(x->isbn);    
  free(x->title);   
  free(x->author);  
  free(x);          
}

