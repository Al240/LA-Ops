/***
Matrix Multiplication Calculator

Simple C program that calculates the product of 2 matrices.
Note: Program currently rounds each entry down to the nearest integer.

Written by Al240
Originally for EECS 22 (Winter '25)

ver.    Date        Changes
-------------------------------------
1.0     1/9/2025    Initial code
1.01    1/9/2025    Added input validation, revised comments
***/

#include <stdio.h>
#define MATRIX_SIZE 4

int main(void) {
    // Initialize 2x2 matrices A and B
    int matrA[MATRIX_SIZE];
    int matrB[MATRIX_SIZE];
    char currInput[4] = "a11\0"; // Label for each matrix entry/element, initialized to start w/ a11

    // Prompt for input (matrix A)
    printf("Enter the first matrix(a) that will be multiplied:\n");
    for (int i=0; i<MATRIX_SIZE; i++) {
        while(1) {
            int numIn; // Dummy variable to store raw input
            printf("%s = ", currInput); // display current element label
            int numVerify = scanf(" %d", &numIn); // Get matrix entry

            if (numVerify) { // Input validation: valid input
                matrA[i] = numIn; // Store inputted value in matrix A
                break; // Continue to next entry
            }
            else {
                printf("ERROR: Invalid input. Please enter numbers only!\n"); // Invalid input
                while ((getchar()) != '\n') {} // Clear remaining chars in buffer
            }
        }
        
        if (currInput[2] == '2') { // Check if first row finished
            currInput[1] = '2'; // Increment label to begin next row
            currInput[2] = '1';
        }
        else currInput[2] = '2'; // Increment label to indicate next element
    }

    currInput[0] = 'b'; // Prepare label for matrix B input (start w/ b11)
    currInput[1] = '1';
    currInput[2] = '1';

    // Prompt for input (matrix B)
    printf("\nEnter the second matrix(a) that will be multiplied:\n");
    for (int i=0; i<MATRIX_SIZE; i++) {
        while(1) {
            int numIn; // Dummy variable to store raw input
            printf("%s = ", currInput); // display current element label
            int numVerify = scanf(" %d", &numIn); // Get matrix entry

            if (numVerify) { // Input validation: valid input
                matrB[i] = numIn; // Store inputted value in matrix B
                break; // Continue to next entry
            }
            else {
                printf("ERROR: Invalid input. Please enter numbers only!\n"); // Invalid input
                while ((getchar()) != '\n') {} // Clear remaining chars in buffer
            }
        }
        if (currInput[2] == '2') { // Check if first row finished
            currInput[1] = '2'; // Increment label to begin next row
            currInput[2] = '1';
        }
        else currInput[2] = '2'; // Increment label to indicate next element
    }

    // Calculate product and store in matrix C (C=A*B)
    int matrC[MATRIX_SIZE] = {((matrA[0] * matrB[0]) + (matrA[1] * matrB[2])), // c11
    ((matrA[0] * matrB[1]) + (matrA[1] * matrB[3])), // c12
    ((matrA[2] * matrB[0]) + (matrA[3] * matrB[2])), // c21
    ((matrA[2] * matrB[1]) + (matrA[3] * matrB[3]))};// c22

    // Display final product
    printf("\nResult:\n");
    printf("%d %d\n%d %d", matrC[0], matrC[1], matrC[2], matrC[3]);
}