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
PROGRAM = demo
TEST = test_directed_graph

OBJS = directed_graph.o main.o deque.o

TEST_OBJS = directed_graph.o test_directed_graph.o deque.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

$(TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LDFLAGS) -o $(TEST)

run: $(PROGRAM)
	./$(PROGRAM)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(PROGRAM) $(OBJS) $(TEST) $(TEST_OBJS) test_output.txt
