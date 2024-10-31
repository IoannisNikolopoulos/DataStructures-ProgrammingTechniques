#include "acutest/acutest.h"

#include "hash_table.h"

void test_initialize() {
	HashTable ht = htInitialize(10);

	TEST_CHECK(ht->size == 10);
	TEST_CHECK(ht->elements == 0);
	TEST_CHECK(ht->array != NULL);

	htDestroy(ht);
}

void test_insert_search() {
	HashTable ht = htInitialize(10);

	ht = htInsert(ht, "hello");
	ht = htInsert(ht, "world");
	ht = htInsert(ht, "goodbye");

	TEST_CHECK(ht->elements == 3);

	TEST_CHECK(strcmp(htSearch(ht, "hello"), "hello") == 0);
	TEST_CHECK(strcmp(htSearch(ht, "world"), "world") == 0);
	TEST_CHECK(strcmp(htSearch(ht, "goodbye"), "goodbye") == 0);

	TEST_CHECK(htSearch(ht, "home") == NULL);

	htDestroy(ht);
}

TEST_LIST = {
	{"initialize", test_initialize},
	{"insert", test_insert_search},
	{NULL, NULL}
};
