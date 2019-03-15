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


int main() {
    //Translate operations
    performTranslation();
    return 0;
}