//----------------------------------------------
// program: phong shading.h
//Author: Tomas Stevens
//Date: 5/01/19
//----------------------------------------------
#include <iostream>
#include <cmath>
using namespace std;

#ifndef _PHONG_
#define _PHONG_

class Phong
{
public:
    // Constructors
    Phong();
    ~Phong();

    // Set methods
    void SetCamera(Point3D pos);
    void SetLight(ColorRGB color, Vector3D dir);
    void SetObject(ColorRGB color, float ka, float kd, float ks, float kp);

    // Get method
    void GetShade(Point3D point, Vector3D normal, ColorRGB & color);

private:
    // Camera
    Point3D CameraPos;

    // Light
    ColorRGB LightColor;
    Vector3D LightDir;

    // Object
    ColorRGB ObjectColor;
    float Ka, Kd, Ks, Kp;
};

#endif