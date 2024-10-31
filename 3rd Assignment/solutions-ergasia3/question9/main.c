#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "hash_table.h"

int main() {
    HashTable ht = htInitialize(5);

    puts("Adding items to hash table");
    ht = htInsert(ht, "mpampis");
    ht = htInsert(ht, "takis");
    ht = htInsert(ht, "nontas");
    ht = htInsert(ht, "stathis");
    ht = htInsert(ht, "mitsos");
    ht = htInsert(ht, "dionysis");
    ht = htInsert(ht, "thomas");
    ht = htInsert(ht, "agisilaos");

    printf("Search  : In hash table\n");
    printf("%s : %s\n", "mpampis", htSearch(ht, "mpampis"));
    printf("%s  : %s\n", "mitsos", htSearch(ht, "mitsos"));
    printf("%s  : %s\n", "thomas", htSearch(ht, "thomas"));

    printf("%s : %s\n", "ektoras", htSearch(ht, "ektoras"));

    htDestroy(ht);

    return 0;
}
