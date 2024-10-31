#include "acutest/acutest.h"
#include "BST.h"
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

void setupBST() {
  BSTinit();

  BSTinsert(createTestItem(2));
  BSTinsert(createTestItem(0));
  BSTinsert(createTestItem(1));
  BSTinsert(createTestItem(3));
}

void testCreate() {
  BSTinit();

  TEST_CHECK(BSTcount() == 0);
  TEST_CHECK(BSTheight() == 0);

  BSTclear();
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
  BSTinit();

  BSTinsert(createTestItem(0));

  TEST_CHECK(strcmp(BSTselect(0)->isbn, "test isbn 0") == 0);

  BSTinsert(createTestItem(1));

  TEST_CHECK(strcmp(BSTselect(1)->isbn, "test isbn 1") == 0);

  TEST_CHECK(BSTselect(2) == NULLitem);

  BSTclear();
}

void testCount() {
  setupBST();

  TEST_CHECK(BSTcount() == 4);

  BSTclear();
}

void testSearch() {
  setupBST();

  TEST_CHECK(strcmp(BSTsearch("test isbn 3")->title, "test title 3") == 0);
  TEST_CHECK(strcmp(BSTsearch("test isbn 1")->title, "test title 1") == 0);
  TEST_CHECK(BSTsearch("test isbn 5") == NULLitem);

  BSTclear();
}

void testDelete() {
  setupBST();

  BSTdelete("test isbn 0");

  TEST_CHECK(BSTsearch("test isbn 0") == NULLitem);

  BSTclear();
}

void testHeight() {
  setupBST();

  TEST_CHECK(BSTheight() == 3);

  BSTclear();
}

void testCountLeaves() {
  setupBST();

  TEST_CHECK(BSTcountLeaves() == 2);

  BSTinsert(createTestItem(5));
  BSTinsert(createTestItem(4));
  BSTinsert(createTestItem(6));

  TEST_CHECK(BSTcountLeaves() == 3);

  BSTclear();
}

void testFloor() {
  setupBST();

  Item item = BSTfloor("test isbn 2");
  TEST_CHECK(strcmp(item->isbn, "test isbn 1") == 0);

  item = BSTfloor("test isbn 3");
  TEST_CHECK(strcmp(item->isbn, "test isbn 2") == 0);

  item = BSTfloor("test isbn 0");
  TEST_CHECK(item == NULLitem);

  BSTclear();
}

void testCeiling() {
  setupBST();

  Item item = BSTceiling("test isbn 2");
  TEST_CHECK(strcmp(item->isbn, "test isbn 3") == 0);

  item = BSTceiling("test isbn 1");
  TEST_CHECK(strcmp(item->isbn, "test isbn 2") == 0);

  item = BSTceiling("test isbn 3");
  TEST_CHECK(item == NULLitem);

  BSTclear();
}

void testCountRange() {
  setupBST();

  TEST_CHECK(BSTcountRange("test isbn 2", "test isbn 6") == 2);
  TEST_CHECK(BSTcountRange("test isbn 1", "test isbn 3") == 3);
  TEST_CHECK(BSTcountRange("test isbn 5", "test isbn 7") == 0);

  BSTclear();
}

void testIsBST() {
  setupBST();

  TEST_CHECK(isBST() == 1);

  BSTinsert(createTestItem(5));
  TEST_CHECK(isBST() == 1);

  BSTdelete("test isbn 3");
  TEST_CHECK(isBST() == 1);

  BSTclear();
}

TEST_LIST = {
  { "create", testCreate },
  { "create item", testCreateItem },
  { "item key", testItemKey },
  { "item key cmp", testItemKeyCmp },
  { "insert and select", testInsertSelect },
  { "count", testCount },
  { "search", testSearch },
  { "delete", testDelete },
  { "height", testHeight },
  { "count leaves", testCountLeaves },
  { "floor", testFloor },
  { "ceiling", testCeiling },
  { "count range", testCountRange },
  { "is BST", testIsBST},
  { NULL, NULL }
};
