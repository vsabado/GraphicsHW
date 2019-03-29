#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Coords.h"
#include <math.h>

using namespace std;

const double PI = 3.14;

//---------------------------------------
// Generate random values for x, y, z
//---------------------------------------
Coords generateRandomValues() {
    //Generate random values for x, y, z
    Coords temp(rand() % 20, rand() % 30, rand() % 50);
    return temp;
}

//---------------------------------------
// Translate x, y, z values
//---------------------------------------
Coords translateValues(Coords coords, Coords translateBy) {
    Coords result(coords.x + translateBy.x, coords.y + translateBy.y, coords.z + translateBy.z);
    return result;
}

void performTranslation() {
    cout
            << "=======================================    PERFORMING TRANSFORMATION FUNCTION   ========================================================="
            << endl;
    Coords coords = generateRandomValues();
    Coords translateBy = generateRandomValues();
    cout << "Coordinate values to translate: " << endl;
    coords.printValues();
    cout << "Coordinate values to translate by " << endl;
    translateBy.printValues();
    cout << "Resulting translation (x', y', z') : " << endl;
    Coords result = translateValues(coords, translateBy);
    result.printValues();
}

//---------------------------------------
// Scale x, y, z values
//---------------------------------------
Coords scaleValues(Coords coords, Coords scaleBy) {
    Coords result(coords.x * scaleBy.x, coords.y * scaleBy.y, coords.z * scaleBy.z);
    return result;
}

void performScale() {
    cout << "=======================================    PERFORMING SCALE FUNCTION   =========================================================" << endl;
    Coords coords = generateRandomValues();
    Coords scaleBy = generateRandomValues();
    cout << "Coordinate values to scale: " << endl;
    coords.printValues();
    cout << "Coordinate values to scale by " << endl;
    scaleBy.printValues();
    cout << "Resulting scale (x', y', z') : " << endl;
    Coords result = scaleValues(coords, scaleBy);
    result.printValues();
}

//---------------------------------------
// Rotate x, y, z values
//---------------------------------------
Coords rotateXAroundX(Coords coords, double theta) {
    coords.y = (cos(theta) * coords.y) - (sin(theta) * coords.z);
    coords.z = (sin(theta) * coords.y) + (cos(theta) * coords.z);
    return coords;
}

Coords rotateZAroundZ(Coords coords, double theta) {
    coords.x = (cos(theta) * coords.x) - (sin(theta) * coords.y);
    coords.y = (sin(theta) * coords.x) + (cos(theta) * coords.y);
    return coords;
}


Coords rotateYAroundY(Coords coords, double theta) {
    coords.x = (cos(theta) * coords.x) + (sin(theta) * coords.z);
    coords.z = (-sin(theta) * coords.x) + (cos(theta) * coords.z);
    return coords;
}

void performRotation() {
    cout << "=======================================    PERFORMING ROTATION FUNCTION   =========================================================" << endl;
    Coords coords = generateRandomValues();
    Coords result(0,0,0);
    double theta = (rand() % 90) * (PI/180);
    cout << "Coordinate values to rotate: " << endl;
    coords.printValues();
    cout << "Theta to rotate by " << theta << endl;
    cout << "Rotate around X-axis values: " << endl;
    result = rotateXAroundX(coords, theta);
    result.printValues();
    cout << "Rotate around Y-axis values: " << endl;
    result = rotateYAroundY(coords, theta);
    result.printValues();
    cout << "Rotate around Z-axis values: " << endl;
    result = rotateZAroundZ(coords, theta);
    result.printValues();
}

//function that takes xyz
//returns an outcode, 4 bits based on the xyz
//so i need to see if they're min, max







void performAllTranslations() {
    performTranslation();
    performScale();
    performRotation();
}

int main() {
    //Translate operations
    performAllTranslations();
    return 0;
}