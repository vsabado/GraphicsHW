//
// Created by nfura on 3/15/2019.
//


#ifndef HOMEWORK4_RESULT_H
#define HOMEWORK4_RESULT_H



class Coords {
public:
    Coords(float x, float y, float z);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    void printValues();

    float x;
    float y;
    float z;
};


#endif //HOMEWORK4_RESULT_H
