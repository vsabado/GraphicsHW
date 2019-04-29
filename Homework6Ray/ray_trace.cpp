//---------------------------------------
// Program: ray_trace.cpp
// Purpose: Demonstrate ray tracing.
// Author:  John Gauch
// Date:    Spring 2019
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>

// Include ray tracing and phong shading code
#include "ray_classes.h"

// Global variables
#define XDIM 800
#define YDIM 800
unsigned char image[YDIM][XDIM][3];
float position = 2;
string mode = "phong";
vector<Sphere3D> spheres;


float genRandomRadius() {
    float random = ((float) rand()) / (float) RAND_MAX;
    // generate (in your case) a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    float range = static_cast<float>(1.0 - 0.2);
    return static_cast<float>((random * range) + 0.2);
}

Sphere3D getRandProperties() {
    //To make the rand() generator random
    Point3D point;
    Sphere3D sphere;
    point.set(rand() % 3 + 0, rand() % 3 + 0, rand() % 5 + 2);
    sphere.set(point, genRandomRadius());
    return sphere;
}

ColorRGB genColor() {
    ColorRGB color;
    color.set(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
    return color;

}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void ray_trace() {
    // Define Phong shader
    Phong shader;

    // Define camera point
    Point3D camera;
    camera.set(0, 0, -position);
    shader.SetCamera(camera);

    // Define light source
    ColorRGB color;
    color.set(200, 200, 200);
    Vector3D dir;
    dir.set(-1, -1, -1);
    dir.normalize();
    shader.SetLight(color, dir);

    // Perform ray tracing
    for (int y = 0; y < YDIM; y++)
        for (int x = 0; x < XDIM; x++) {

            // Clear image
            image[y][x][0] = 0;
            image[y][x][1] = 0;
            image[y][x][2] = 0;


            for (int i = 0; i < spheres.size(); i++) {
                // Define sample point on image plane
                float xpos = (x - XDIM / 2) * 2.0 / XDIM;
                float ypos = (y - YDIM / 2) * 2.0 / YDIM;
                Point3D point;
                point.set(xpos, ypos, 0);

                // Define ray from camera through image
                Ray3D ray;
                ray.set(camera, point);

                // Perform sphere intersection
                Point3D p;
                Vector3D n;

                if (spheres[i].get_intersection(ray, p, n)) {
                    Ray3D shadow;
                    shadow.set(p, point);

                    if (camera.distance(spheres[i].center) > camera.distance(p)) {
                        shadow.set(p, dir);
                        color.set(spheres[i].color.R, spheres[i].color.G, spheres[i].color.B);
                        shader.SetObject(color, 0.3, 0.4, 0.4, 5);

                        for (int k = 0; k < spheres.size(); k++) {
                            if (spheres[k].get_intersection(shadow, p, n) && k != i) {
                                color.set(spheres[i].color.R, spheres[i].color.G, spheres[i].color.B);
                                shader.SetObject(color, 0.3, 0, 0, 5);
                            }
                        }

                    }

                    // Display surface normal
                    if (mode == "normal") {
                        image[y][x][0] = 127 + n.vx * 127;
                        image[y][x][1] = 127 + n.vy * 127;
                        image[y][x][2] = 127 + n.vz * 127;
                    }

                    // Calculate Phong shade
                    if (mode == "phong") {
                        shader.GetShade(p, n, color);
                        image[y][x][0] = color.R;
                        image[y][x][1] = color.G;
                        image[y][x][2] = color.B;
                    }
                }
            }
        }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init() {
    // Initialize OpenGL
    glClearColor(0, 0.0, 0.0, 1.0);

    // Print command menu
    cout << "Program commands:\n"
         << "   '+' - increase camera distance\n"
         << "   '-' - decrease camera distance\n"
         << "   'p' - show Phong shading\n"
         << "   'n' - show surface normals\n"
         << "   'q' - quit program\n"
         << "   's' - populate spheres\n";

    spheres.clear();
    //Define test sphere
    for (int i = 0; i < rand() % 3 + 2; i++) {
        Sphere3D temp = getRandProperties();
        temp.color = genColor();
        spheres.push_back(temp);
    }

//testing purpose
//    Point3D point1;
//    Sphere3D sphere1;
//    point1.set(0, 0, 2);
//    sphere1.set(point1, 0.7);
//    sphere1.color = genColor();
//    spheres.push_back(sphere1);
//
//    Point3D point2;
//    Sphere3D sphere2;
//    point2.set(-1, -1, 2);
//    sphere2.set(point2, 0.4);
//    sphere2.color = genColor();
//    spheres.push_back(sphere2);
//    cout << spheres.size() << endl;


    // Perform ray tracing
    ray_trace();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display() {
    // Display image
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, image);
    glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y) {
    // End program
    if (key == 'q')
        exit(0);

        // Move camera position
    else if (key == '+' && position < 5)
        position = position * 1.1;
    else if (key == '-' && position > 1)
        position = position / 1.1;

        // Change display mode
    else if (key == 'n')
        mode = "normal";
    else if (key == 'p')
        mode = "phong";
    else if (key == 's'){
        spheres.clear();
        //Define test sphere
        for (int i = 0; i < rand() % 3 + 2; i++) {
            Sphere3D temp = getRandProperties();
            temp.color = genColor();
            spheres.push_back(temp);
        }
    }

    // Perform ray tracing
    ray_trace();
    glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[]) {
    //Reset the seed
    srand(time(NULL));

    // Create OpenGL window
    glutInit(&argc, argv);
    glutInitWindowSize(XDIM, YDIM);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Ray Trace");
    init();

    // Specify callback function
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}