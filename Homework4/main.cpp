#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Coords.h"

using namespace std;

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
    cout << "=======================================    PERFORMING TRANSFORMATION FUNCTION   =========================================================" << endl;
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


int main() {
    //Translate operations
    performTranslation();
    performScale();
    return 0;
}