#include "acutest/acutest.h"
#include "string.h"
#include "priority_queue.h"


void testCreate(void) {
    PQPointer pq = QUEUEinit(5);
    TEST_CHECK(pq != NULL);
    TEST_CHECK(pq->Count == 5);
    TEST_CHECK(QUEUEempty(pq) == 1);
    free(pq->ItemArray);
    free(pq);
}

void testEmpty(void) {
    PQPointer pq = QUEUEinit(5);
    TEST_CHECK(QUEUEempty(pq) == 1);
    QUEUEput(pq, 10);
    TEST_CHECK(QUEUEempty(pq) == 0);
    free(pq->ItemArray);
    free(pq);
}

void testPut(void) {
    PQPointer pq = QUEUEinit(2);
    QUEUEput(pq, 10);
    TEST_CHECK(pq->ItemArray[1] == 10);
    QUEUEput(pq, 20);
    TEST_CHECK(pq->ItemArray[1] == 20 && pq->ItemArray[2] == 10);
    QUEUEput(pq, 5); // Causes resize
    TEST_CHECK(pq->Count == 4);
    TEST_CHECK(pq->ItemArray[3] == 5 && pq->ItemArray[1] == 20 && pq->ItemArray[2] == 10);
    free(pq->ItemArray);
    free(pq);
}

void testGet(void) {
    PQPointer pq = QUEUEinit(5);
    QUEUEput(pq, 10);
    QUEUEput(pq, 20);
    QUEUEput(pq, 5);
    TEST_CHECK(QUEUEget(pq) == 20);
    TEST_CHECK(QUEUEget(pq) == 10);
    TEST_CHECK(QUEUEget(pq) == 5);
    TEST_CHECK(QUEUEempty(pq) == 1);
    free(pq->ItemArray);
    free(pq);
}

TEST_LIST = {
  { "create", testCreate },
  { "empty", testEmpty },
  { "put", testPut },
  { "get", testGet },
  { NULL, NULL }
};
