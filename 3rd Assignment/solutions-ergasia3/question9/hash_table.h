#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_LOAD_FACTOR 0.75

typedef char* Key;
typedef char* Item;

struct node {
	Item data;
	struct node* next;
};

typedef struct node* Node;

struct hash_table {
	int elements;
	int size;
	Node* array;
};

typedef struct hash_table* HashTable;

HashTable htInitialize(int size);
HashTable htInsert(HashTable ht, Item item);
Item htSearch(HashTable ht, Key key);
void htDestroy(HashTable ht);

#endif // HASH_TABLE_H
