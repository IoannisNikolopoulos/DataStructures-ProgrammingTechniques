#include <stdio.h>
#include <stdlib.h>

// Helper function to generate subsets recursively
void powersethelper(int n, int prefix) {
	if (n == prefix) {  // Base case: when prefix equals n
		for (int i = 1; i <= n; i++) {  // Print each number from 1 to n
			printf("%d ", i);  // Print the number followed by a space
		}
		putchar('\n');  // Move to the next line
		return;  // Exit the function
	}

	for (int i = prefix + 1; i <= n; i++) {  // Loop from prefix+1 to n
		if (prefix != 0)  // If prefix is not 0
			printf("%d %d, ", prefix, i);  // Print the pair prefix and i followed by a comma and space
		else  // If prefix is 0
			printf("%d, ", i);  // Print i followed by a comma and space
	}

	powersethelper(n, prefix + 1);  // Recursively call powersethelper with incremented prefix
}

// Function to generate and print the powerset of numbers from 1 to n
void powerset(int n) {
	printf("0, ");  // Print the initial element 0
	powersethelper(n, 0);  // Call the helper function to generate subsets
}
