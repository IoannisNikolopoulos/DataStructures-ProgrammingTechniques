typedef void* Stack;

Stack stackCreate(); // Creates and returns an empty stack.
void stackPush(Stack, int); // Pushes an element to the stack.
int stackPop(Stack); // Pops an element from the stack and returns its value
int stackPeek(Stack); // Returns the value of the element at the top of the stack
int stackSize(Stack); // Returns the number of elements in the stack
void destroyStack(Stack); // Destroys the stack and frees memory.

Stack sort_stack(Stack a) { // Function to sort a stack in ascending order.
    Stack b = stackCreate();     // Create a temporary stack (b) to hold sorted elements.
	
    while (stackSize(a) > 0) {     // Continue sorting until all elements from stack 'a' are moved to 'b'.
        int temp = stackPop(a);         // Pop the top element from 'a'.
        while (stackSize(b) > 0 && stackPeek(b) > temp) {         // Move elements from 'b' to 'a' until the correct position for 'temp' is found.
            stackPush(a, stackPop(b));
        }

        stackPush(b, temp);         // Move elements from 'b' to 'a' until the correct position for 'temp' is found.
    }

    destroyStack(a);     // Destroy the original stack 'a', as its elements are now in 'b'.
	
    return b;     // Return the sorted stack 'b'.
}
