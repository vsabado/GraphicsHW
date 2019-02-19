//
// Created by vladpc on 2/17/19.
//

#include "Cube.h"



Cube::Cube(float x, float y, float z, GLenum mode, float size) {
    this->midx = x;
    this->midy = y;
    this->midz = z;
    this->mode = mode;
    this->size = size;
}

void Cube::draw() {
    // Define 8 vertices
    float ax = midx - size / 2;
    float ay = midy - size / 2;
    float az = midz + size / 2;
    float bx = midx + size / 2;
    float by = midy - size / 2;
    float bz = midz + size / 2;
    float cx = midx + size / 2;
    float cy = midy + size / 2;
    float cz = midz + size / 2;
    float dx = midx - size / 2;
    float dy = midy + size / 2;
    float dz = midz + size / 2;
    float ex = midx - size / 2;
    float ey = midy - size / 2;
    float ez = midz - size / 2;
    float fx = midx + size / 2;
    float fy = midy - size / 2;
    float fz = midz - size / 2;
    float gx = midx + size / 2;
    float gy = midy + size / 2;
    float gz = midz - size / 2;
    float hx = midx - size / 2;
    float hy = midy + size / 2;
    float hz = midz - size / 2;


    // Draw 6 faces
    glBegin(mode);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(ax, ay, az);
    glVertex3f(bx, by, bz);
    glVertex3f(cx, cy, cz);
    glVertex3f(dx, dy, dz);
    glEnd();

    glBegin(mode);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(ax, ay, az);
    glVertex3f(dx, dy, dz);
    glVertex3f(hx, hy, hz);
    glVertex3f(ex, ey, ez);
    glEnd();

    glBegin(mode);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(ax, ay, az);
    glVertex3f(ex, ey, ez);
    glVertex3f(fx, fy, fz);
    glVertex3f(bx, by, bz);
    glEnd();

    glBegin(mode);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(fx, fy, fz);
    glVertex3f(ex, ey, ez);
    glVertex3f(hx, hy, hz);
    glEnd();

    glBegin(mode);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(cx, cy, cz);
    glVertex3f(bx, by, bz);
    glVertex3f(fx, fy, fz);
    glEnd();

    glBegin(mode);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(hx, hy, hz);
    glVertex3f(dx, dy, dz);
    glVertex3f(cx, cy, cz);
    glEnd();
}

bool Cube::isEqual(float x, float y, float z) {
    float delta = 0.0000001; //Since the difference is 2.98023e-08, this delta value must be greater
//    printf("Mid value (%f,%f,%f), Values (%f,%f,%f) \n", midx,midy,midz, x,y,z);
    return fabs(this->midx - x) < delta && fabs(this->midy - y ) < delta && fabs(this->midz - z) < delta;
}