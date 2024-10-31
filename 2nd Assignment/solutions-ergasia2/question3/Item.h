/* This code is from "Algorithms in C, Third Edition, by Robert Sedgewick, Addison-Wesley, 1998. */
#ifndef ITEM_H
#define ITEM_H

struct item {
  char* isbn;
  char* title;
  char* author;
  int year;
};

typedef struct item* Item;
typedef char* Key;

#include <string.h>

#define NULLitem NULL /* NULLitem is a constant */
#define NULLkey "" /* NULLkey is a constant */
#define key(A) (A->isbn) /* A is an Item */
#define less(A, B) (strcmp(A, B) < 0) /* A and B are Keys */
#define eq(A, B) (strcmp(A, B) == 0) /* A and B are Keys */
#define leq(A, B) (strcmp(A, B) <= 0) /* A and B are Keys */

Item ITEMcreate(char* isbn, char* title, char* author, int year);
Item ITEMscan();
void ITEMshow(Item x);
void ITEMfree(Item x);

#endif // ITEM_H
