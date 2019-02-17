//
// Created by vladpc on 2/17/19.
//

#include <GL/glut.h>
#ifndef PROJECT_CUBE_H
#define PROJECT_CUBE_H

#endif //PROJECT_CUBE_H

class Cube{
public:
    float midx;
    float midy;
    float midz;
    float size;
    GLenum mode;
    Cube(float x, float y, float z, GLenum mode, float size);
    void draw();
};