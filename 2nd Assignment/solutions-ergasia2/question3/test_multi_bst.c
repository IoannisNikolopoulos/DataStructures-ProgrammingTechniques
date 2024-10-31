#include "acutest/acutest.h"
#include "multiBST.h"
#include "string.h"

Item createTestItem(int i) {
  char isbn[] = "test isbn x";
  isbn[10] = i + '0';

  char title[] = "test title x";
  title[11] = i + '0';

  char author[] = "test author x";
  author[12] = i + '0';

  return ITEMcreate(isbn, title, author, 2024);
}

BST setupBST() {
  BST bst = BSTinit();

  bst = BSTinsert(bst, createTestItem(2));
  bst = BSTinsert(bst, createTestItem(0));
  bst = BSTinsert(bst, createTestItem(1));
  bst = BSTinsert(bst, createTestItem(3));

  return bst;
}

void testCreate() {
  BST bst = BSTinit();

  TEST_CHECK(BSTcount(bst) == 0);
  TEST_CHECK(BSTheight(bst) == 0);

  BSTclear(bst);
}

void testCreateItem() {
  Item item = createTestItem(0);

  TEST_CHECK(strcmp(item->isbn, "test isbn 0") == 0);
  TEST_CHECK(strcmp(item->title, "test title 0") == 0);
  TEST_CHECK(strcmp(item->author, "test author 0") == 0);
  TEST_CHECK(item->year == 2024);
}

void testItemKey() {
  Item item = createTestItem(0);

  TEST_CHECK(strcmp(key(item), "test isbn 0") == 0);
}

void testItemKeyCmp() {
  Item item1 = createTestItem(0);
  Item item2 = createTestItem(1);

  TEST_CHECK(less(key(item1), key(item2)) == 1);
  TEST_CHECK(less(key(item2), key(item1)) == 0);

  TEST_CHECK(eq(key(item1), key(item2)) == 0);
  TEST_CHECK(eq(key(item1), key(item1)) == 1);

  TEST_CHECK(leq(key(item1), key(item2)) == 1);
  TEST_CHECK(leq(key(item1), key(item1)) == 1);
}

void testInsertSelect() {
  BST bst = BSTinit();

  bst = BSTinsert(bst, createTestItem(0));

  TEST_CHECK(strcmp(BSTselect(bst, 0)->isbn, "test isbn 0") == 0);

  bst = BSTinsert(bst, createTestItem(1));

  TEST_CHECK(strcmp(BSTselect(bst, 1)->isbn, "test isbn 1") == 0);

  TEST_CHECK(BSTselect(bst, 2) == NULLitem);

  BSTclear(bst);
}

void testCount() {
  BST bst = setupBST();

  TEST_CHECK(BSTcount(bst) == 4);

  BSTclear(bst);
}

void testSearch() {
  BST bst = setupBST();

  TEST_CHECK(strcmp(BSTsearch(bst, "test isbn 3")->title, "test title 3") == 0);
  TEST_CHECK(strcmp(BSTsearch(bst, "test isbn 1")->title, "test title 1") == 0);
  TEST_CHECK(BSTsearch(bst, "test isbn 5") == NULLitem);

  BSTclear(bst);
}

void testDelete() {
  BST bst = setupBST();

  bst = BSTdelete(bst, "test isbn 0");

  TEST_CHECK(BSTsearch(bst, "test isbn 0") == NULLitem);

  BSTclear(bst);
}

void testHeight() {
  BST bst = setupBST();

  TEST_CHECK(BSTheight(bst) == 3);

  BSTclear(bst);
}

void testCountLeaves() {
  BST bst = setupBST();

  TEST_CHECK(BSTcountLeaves(bst) == 2);

  bst = BSTinsert(bst, createTestItem(5));
  bst = BSTinsert(bst, createTestItem(4));
  bst = BSTinsert(bst, createTestItem(6));

  TEST_CHECK(BSTcountLeaves(bst) == 3);

  BSTclear(bst);
}

void testFloor() {
  BST bst = setupBST();

  Item item = BSTfloor(bst, "test isbn 2");
  TEST_CHECK(strcmp(item->isbn, "test isbn 1") == 0);

  item = BSTfloor(bst, "test isbn 3");
  TEST_CHECK(strcmp(item->isbn, "test isbn 2") == 0);

  item = BSTfloor(bst, "test isbn 0");
  TEST_CHECK(item == NULLitem);

  BSTclear(bst);
}

void testCeiling() {
  BST bst = setupBST();

  Item item = BSTceiling(bst, "test isbn 2");
  TEST_CHECK(strcmp(item->isbn, "test isbn 3") == 0);

  item = BSTceiling(bst, "test isbn 1");
  TEST_CHECK(strcmp(item->isbn, "test isbn 2") == 0);

  item = BSTceiling(bst, "test isbn 3");
  TEST_CHECK(item == NULLitem);

  BSTclear(bst);
}

void testCountRange() {
  BST bst = setupBST();

  TEST_CHECK(BSTcountRange(bst, "test isbn 2", "test isbn 6") == 2);
  TEST_CHECK(BSTcountRange(bst, "test isbn 1", "test isbn 3") == 3);
  TEST_CHECK(BSTcountRange(bst, "test isbn 5", "test isbn 7") == 0);

  BSTclear(bst);
}

void testIsBST() {
  BST bst = setupBST();

  TEST_CHECK(isBST(bst) == 1);

  bst = BSTinsert(bst, createTestItem(5));
  TEST_CHECK(isBST(bst) == 1);

  bst = BSTdelete(bst, "test isbn 3");
  TEST_CHECK(isBST(bst) == 1);

  BSTclear(bst);
}

TEST_LIST = {
  { "create", testCreate },
  { "insert and select", testInsertSelect },
  { "count", testCount },
  { "search", testSearch },
  { "delete", testDelete },
  { "height", testHeight },
  { "count leaves", testCountLeaves },
  { "floor", testFloor },
  { "ceiling", testCeiling },
  { "count range", testCountRange },
  { "is BST", testIsBST },
  { NULL, NULL }
};
