/* vectors.h: Function declarations for LA-Ops (Vectors)
Written by: Al240 // 2/14/2025

ver.    Date        Changelog
1.1     -           [AL] Vectors now have their own structure
1.0     2/14/2025   [AL] Initial code, includes functions from vector calculator */

#ifndef VECTORS_H
#define VECTORS_H

typedef struct { // 3D Vector associated with a label
    double x;
    double y;
    double z;
    char label;
} Vect;

Vect getVector(void); // Allows user to define a vector
int getMagUnit(Vect v1); // Magnitude + unit vector calculation
int vAddSub(Vect v1, Vect v2); // Addition and subtraction, v1 +/- v2
int dotProduct(Vect v1, Vect v2); // Dot product, v1 • v2
int crossProduct(Vect v1, Vect v2); // Cross product, v1 x v2

#endif