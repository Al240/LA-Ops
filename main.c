/* Linear Algebra Operations: Performs basic operations used in Linear Algebra 
By: Al240 // 2/13/2025

ver.    Date        Changelog
1.1     2/14/2025   Menus written, implemented vector stuff
1.0     2/13/2025   Initial commit, combines matrix.c and vectorProduct.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"
#include "matrix.h"

void MainMenu(void) {
    printf("\n-------------------------\n");
    printf("\nLINEAR ALGEBRA OPERATIONS\n");
    printf("v1.0\n\n");
    printf("(V)ectors only\n");
    printf("(M)atrices\n");
    printf("(Q)uit Program");
    printf("Choose an option: ");
}

void VectorMenu(void) {
    printf("\nVECTOR OPERATIONS MENU\n");
    printf("(A)ddition and Subtraction\n");
    printf("(D)ot Product\n");
    printf("(C)ross Product\n");
    printf("(M)agnitude & Unit Vector\n");
    printf("(R)eturn to main menu\n");
    printf("Choose an option: ");
}

void MatrixMenu(void) {
    printf("\nMATRIX OPERATIONS MENU\n");
    printf("(D)eterminant, Dimension & Rank\n");
    printf("(A)ddition and Subtraction\n");
    printf("(M)ultiplication\n");
    printf("(N)ull Space\n");
    printf("(S)olver, Linear System Augmented\n");
    printf("(E)igenvalue/vector finder\n");
    printf("(R)eturn to main menu\n");
    printf("Choose an option: ");
}

int main(void) {
    char userChoice, vecChoice, matChoice;
    int running, runVec, runMat;
    running = 1;
    while (running) {
        MainMenu();
        scanf(" %c", &userChoice);
        switch (userChoice) {
            // Vectors
            case 'V': case 'v':
                runVec = 1;
                while (runVec) {
                    VectorMenu();
                    scanf(" %c", &vecChoice);
                    switch (vecChoice) {
                        case 'A': case 'a':
                            Vect vecA = getVector();
                            Vect vecB = getVector();
                            addSub(vecA, vecB);
                            break;
                        // Dot Product
                        case 'D': case 'd':
                            Vect vecA = getVector();
                            Vect vecB = getVector();
                            dotProduct(vecA, vecB);
                            break;
                        // Cross Product
                        case 'C': case 'c':
                            Vect vecA = getVector();
                            Vect vecB = getVector();
                            crossProduct(vecA, vecB);
                            break;
                        // Magnitude and Unit Vector
                        case 'M': case 'm':
                            Vect vecA = getVector();
                            getMagUnit(vecA);
                            break;
                        // Return to main menu
                        case 'R': case 'r':
                            runVec = 0;
                            break;
                    }
                }
            
            // Matrices
            //case 'M': case 'm':
            //    MatrixMenu();

            // Quit Program
            case 'Q': case 'q':
            printf("Quitting Program...\n");
            running = 0;
            break;

            default:
                printf("Invalid option. Try again.\n"); // input validation
                while ((getchar()) != '\n') {} // clear input buffer
        }
    }
}