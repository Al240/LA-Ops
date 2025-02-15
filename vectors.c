/* vectors.c: Vector-related operations for LA-Ops
Written by: Al240 & stereoscoped // 2/14/2025

ver.    Date        Changelog
1.1     -           [AL] Removed vector arrays, replaced w/ structure (see vectors.h)
1.0     2/14/2025   [AL] Initial code, taken from vector calculator */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vectors.h"

Vect getVector(void) { // Allows user to define a vector
    Vect v1;
    printf("Label the vector (i.e. A): ");
    scanf(" %c", &v1.label);

    char currComp = 'x';
    double comps[3];
    printf("Define the x, y, and z components of the vector %c.\n", v1.label);
    for (int i=0; i<3; i++) {
        int valInput = 0;
        while (!valInput) {
            printf("%c: ", currComp);
            valInput = scanf("%lf", &comps[i]);
            if (valInput) {
                currComp++; // x -> y, y -> z
                while ((getchar()) != '\n') {} // clear input buffer
                break;
            }
            else {
                printf("Invalid input, please try again. Component must be a real number.\n");
                while ((getchar()) != '\n') {} // clear input buffer
            }
        }
    }
    v1.x = comps[0];
    v1.y = comps[1];
    v1.z = comps[2];
    printf("Vector %c: <%.4f, %.4f, %.4f>\n\n", v1.label, v1.x, v1.y, v1.z);
    return v1;
}

int getMagUnit(Vect v1) { // Magnitude + unit vector calculation
    double vMag = sqrt((v1.x*v1.x)+(v1.y*v1.y)+(v1.z*v1.z));
    printf("Magnitude ||%c||: %.4f\n", v1.label, vMag);
    printf("Unit Vector v/||v||: <%.4f, %.4f, %.4f>\n\n", v1.x/vMag, v1.y/vMag, v1.z/vMag);
}

int vAddSub(Vect v1, Vect v2) { // Addition and subtraction, v1 +/- v2
    char opChoice;
    int inProgress = 1;
    printf("Add (+) or Subtract (-)? ");

    while (inProgress) {
        scanf(" %c%*c", &opChoice);
        switch (opChoice) {
            // Addition
            case '+' : case 'A' : case 'a' :
                printf("\nA + B = <%.4f, %.4f, %.4f>\n\n", (v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
                inProgress = 0;
                break;
            // Subtraction
            case '-' : case 'S' : case 's' :
                printf("\nA - B = <%.4f, %.4f, %.4f>\n\n", (v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z));
                inProgress = 0;
                break;

            default:
                printf("Invalid operation. Please choose + or - : "); // input validation
                while ((getchar()) != '\n') {} // clear input buffer
        }
    }
    return 0;
}


int dotProduct(Vect v1, Vect v2) { // Dot product, v1 • v2
    double dProduct = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z); // (a1b1)+(a2b2)+(a3b3)
    printf("A • B = %.4f\n\n", dProduct); // Display final dot product
    return 0;
}

int crossProduct(Vect v1, Vect v2) { // Cross product, v1 x v2
    Vect cProd;
    cProd.x = (v1.y * v2.z-v1.z * v2.y);
    cProd.y = (v1.z * v2.x-v1.x * v2.z);
    cProd.z = (v1.x * v2.y-v1.y * v2.x); 
    cProd.label = 'AxB'; // <a2b3-a3b2,a3b1-a1b3,a1b2-a2b1>

    printf("\nWork Shown:\n"); // Display 2 steps in detail
    printf("A x B = <(%.4f)(%.4f) - (%.4f)(%.4f), (%.4f)(%.4f) - (%.4f)(%.4f), (%.4f)(%.4f) - (%.4f)(%.4f)>", // 1. plug in values
        v1.y, v2.z, v1.z, v2.y, // x: (a2b3)-(a3b2)
        v1.z, v2.x, v1.x, v2.z, // y: (a3b1)-(a1b3)
        v1.x, v2.y, v1.y, v2.x); // z: (a1b2)-(a2b1)
    printf("\nA x B = <%.4f - %.4f, %.4f - %.4f, %.4f - %.4f>\n", // 2. simplify after multiplication
        v1.y * v2.z, v1.z * v2.y,
        v1.z * v2.x, v1.x * v2.z,
        v1.x * v2.y, v1.y * v2.x);
    printf("\nFinal Answer:");
    printf("\nA x B = <%.4f, %.4f, %.4f>\n\n", cProd.x, cProd.y, cProd.z);
    return 0;
}