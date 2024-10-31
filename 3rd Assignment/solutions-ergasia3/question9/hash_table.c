#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include <stdio.h>

Key getKey(Item a) {
	return a;
}

// return <0 if a < b, >0 if a > b, 0 if a == b
int compareKey(Key a, Key b) {
	return strcmp(a, b);
}

unsigned int hash(HashTable ht, Key key) {
	unsigned int hash = 5381;
	unsigned int c;

	while ((c = *key++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % ht->size ;
}

HashTable htInitialize(int size) {
	HashTable ht = malloc(sizeof(struct hash_table));
	ht->size = size;
	ht->elements = 0;
	ht->array = calloc(size, sizeof(Node));
	return ht;
}

Node createNode(Item item) {
	Node newNode = malloc(sizeof(struct node));
	newNode->data = malloc(sizeof(char) * strlen(item));
	strcpy(newNode->data, item);
	newNode->next = NULL;
	return newNode;
}

Node linkedListInsert(Node head, Item item) {
	Node newNode = createNode(item);

	if (head == NULL) return newNode;

	Node cursor = head;
	while ( cursor->next != NULL) {
		cursor = cursor->next;
	}

	cursor->next = newNode;
	return head;
}

int loadFactor(HashTable ht) {
	return ht->elements / ht->size;
}

HashTable htRehash(HashTable ht) {
	HashTable newHt = htInitialize(ht->size * 2);

	for (int i = 0; i < ht->size; i++) {
		Node cursor = ht->array[i];
		while (cursor != NULL) {
			newHt = htInsert(newHt, cursor->data);

			cursor = cursor->next;
		}
	}

	htDestroy(ht);

	puts("Rehashed hash table");

	return newHt;
}

HashTable htInsert(HashTable ht, Item item) {
	Key key = getKey(item);
	unsigned int index = hash(ht, key);

	ht->array[index] = linkedListInsert(ht->array[index], item);
	ht->elements++;

	if (loadFactor(ht) > MAX_LOAD_FACTOR) return htRehash(ht);

	return ht;
}

Item linkedListSearch(Node head, Key key) {
	for (Node cursor = head; cursor != NULL; cursor = cursor->next) {
		if (compareKey(getKey(cursor->data), key) == 0) return cursor->data;
	}

	return NULL;
}

Item htSearch(HashTable ht, Key key) {
	unsigned int index = hash(ht, key);

	Item item = linkedListSearch(ht->array[index], key);

	return item;
}

void destroyNode(Node node) {
	free(node->data);
	free(node);
}

void destroyLinkedList(Node head) {
	Node cursor = head;
	while (cursor != NULL) {
		Node temp = cursor->next;
		destroyNode(cursor);
		cursor = temp;
	}
}

void htDestroy(HashTable ht) {
	for (int i = 0; i < ht->size; i++) {
		destroyLinkedList(ht->array[i]);
	}
	free(ht->array);
	free(ht);
}
