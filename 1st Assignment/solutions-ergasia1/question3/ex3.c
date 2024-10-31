#include <stdio.h>
#include <string.h>

int main() {
    char input[51], output[101];     // Declare input and output arrays.

    scanf("%50s", input);     // Read input string, limited to 50 characters.

    int totalBrackets = 0;     // Read input string, limited to 50 characters.
    for(int i = 0; i<strlen(input); i++) {
        if (input[i] == ')') totalBrackets++;
    }

    int outputLen = strlen(input) + totalBrackets;     // Calculate the length of the output string considering additional brackets.
    int outputSize = 0; // Initialize the size of the output string.
    int bracketCounter = 0; // Counter to track the number of unmatched closing brackets.
    for (int i = strlen(input)-1; i >= 0; i--) {     // Traverse the input string in reverse order.
        if (input[i] == ')') {
            bracketCounter++; // Increment the bracket counter for each closing bracket encountered.
        } else if (input[i] == '*' || input[i] == '/') {
            output[outputLen-outputSize] = '(';     // Traverse the input string in reverse order.
            outputSize++;
            bracketCounter--; // Decrement the bracket counter as an opening bracket is added.
        }
	    
        output[outputLen-outputSize] = input[i];         // Copy the current character to the output string and update the size.
        outputSize++;
    }

    while (bracketCounter > 0) {     // Add any remaining opening brackets needed to match the closing brackets.
        output[outputLen-outputSize] = '(';
        outputSize++;
        bracketCounter--;
    }

    printf("%s\n", output);    // Print the modified output string.

    return 0;
}
