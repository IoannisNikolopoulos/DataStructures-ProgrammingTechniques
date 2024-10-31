# compile with gcc
CC=gcc

# Compiler options:
#
# -pg is used for profiling (gprof)
CFLAGS = -g

# Linker options:
#
# -lm: link with the math library
LDFLAGS += -lm

# set the name of the executable file to compile here
BST = bst
BST_TEST = test-bst

MULTI_BST = multi-bst
MULTI_BST_TEST = multi-bst-test

BST_OBJS = bst-implementation.o item-implementation.o deque.o demo.o
BST_TEST_OBJS = bst-implementation.o item-implementation.o deque.o test_bst.o

MULTI_BST_OBJS = multi-bst-implementation.o item-implementation.o deque.o mutli_demo.o
MULTI_BST_TEST_OBJS = multi-bst-implementation.o item-implementation.o deque.o test_multi_bst.o

$(BST): $(BST_OBJS)
	$(CC) $(CFLAGS) $(BST_OBJS) $(LDFLAGS) -o $(BST)

$(BST_TEST): $(BST_TEST_OBJS)
	$(CC) $(CFLAGS) $(BST_TEST_OBJS) $(LDFLAGS) -o $(BST_TEST)

$(MULTI_BST): $(MULTI_BST_OBJS)
	$(CC) $(CFLAGS) $(MULTI_BST_OBJS) $(LDFLAGS) -o $(MULTI_BST)

$(MULTI_BST_TEST): $(MULTI_BST_TEST_OBJS)
	$(CC) $(CFLAGS) $(MULTI_BST_TEST_OBJS) $(LDFLAGS) -o $(MULTI_BST_TEST)

PRIORITY_QUEUE = priority-queue
PRIORITY_QUEUE_TEST = priority-queue-test

# Object files needed for the test
PRIORITY_QUEUE_OBJS = priority_queue.o demo.o
PRIORITY_QUEUE_TEST_OBJS = test_priority_queue.o priority_queue.o

# Compile the test executable
$(PRIORITY_QUEUE): $(PRIORITY_QUEUE_OBJS)
	$(CC) $(CFLAGS) $(PRIORITY_QUEUE_OBJS) $(LDFLAGS) -o $(PRIORITY_QUEUE)
$(PRIORITY_QUEUE_TEST): $(PRIORITY_QUEUE_TEST_OBJS)
	$(CC) $(CFLAGS) $(PRIORITY_QUEUE_TEST_OBJS) $(LDFLAGS) -o $(PRIORITY_QUEUE_TEST)

test: $(BST_TEST)
	./$(BST_TEST)

priority_test: $(PRIORITY_QUEUE_TEST)
	./$(PRIORITY_QUEUE_TEST)
	
multitest: $(MULTI_BST_TEST)
	./$(MULTI_BST_TEST)

clean:
	rm -f $(BST) $(BST_TEST) $(MULTI_BST) $(MULTI_BST_TEST) $(BST_OBJS) $(BST_TEST_OBJS) $(MULTI_BST_OBJS) $(MULTI_BST_TEST_OBJS) $(PRIORITY_QUEUE) $(PRIORITY_QUEUE_TEST) $(PRIORITY_QUEUE_OBJS) $(PRIORITY_QUEUE_TEST_OBJS)

