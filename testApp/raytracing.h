//----------------------------------------------
//program: ray tracing.h
//Author: Tomas Stevens
//Date: 5/01/19
//----------------------------------------------

#include <iostream>
#include <cmath>
using namespace std;

#ifndef _CLASSES_
#define _CLASSES_

//----------------------------------------------
class ColorRGB
{
public:
    float R, G, B;

    void set(float r, float g, float b);
    string print();
    void mult(float c);
    void mult(ColorRGB c);
    void add(ColorRGB c);
    void sub(ColorRGB c);
    void clamp();
};

//----------------------------------------------
class Point3D
{
public:
    float px, py, pz;

    void set(float x, float y, float z);
    string print();
    float distance(Point3D p);
};

//----------------------------------------------
class Vector3D
{
public:
    float vx, vy, vz;

    void set(float x, float y, float z);
    string print();
    void normalize();
    float dot(Vector3D v);
    void mult(float c);
    void add(Vector3D v);
    void sub(Vector3D v);
};

//----------------------------------------------
class Ray3D
{
public:
    Point3D point;
    Vector3D dir;

    void set(Point3D p, Vector3D d);
    void set(Point3D p1, Point3D p2);
    string print();
    Point3D get_sample(float t);
};

//----------------------------------------------
class Sphere3D
{
public:
    Point3D center;
    float radius;

    void set(Point3D p, float r);
    string print();
    bool get_intersection(Ray3D ray, Point3D &point, Vector3D &normal);
};

#endif