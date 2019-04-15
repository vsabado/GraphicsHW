//
// Created by nfura on 3/15/2019.
//

#include "Coords.h"
#include <iostream>
using namespace std;

Coords::Coords(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

float Coords::getX() const {
    return x;
}

void Coords::setX(float x) {
    Coords::x = x;
}

float Coords::getY() const {
    return y;
}

void Coords::setY(float y) {
    Coords::y = y;
}

float Coords::getZ() const {
    return z;
}

void Coords::setZ(float z) {
    Coords::z = z;
}

void Coords::printValues(){
    cout << "x: " << this->x << ", y: " << this->y << ", z: " << this->z << endl;
}