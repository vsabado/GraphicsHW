#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Cube.h"

using namespace std;

//Important globals
GLenum mode = GL_LINE_LOOP;
int xangle = 10;
int yangle = 15;
float playerX = 0;
float playerY = 0;
float playerZ = 0;
float positiveBoundary = 0.58;
float negativeBoundary = -0.58;
float positiveFixed = 0.57;
float negativeFixed = -0.57;
bool fly = true;
float movementSpeed = 0.03;
vector<Cube> cubes;


//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    Cube bigCube (0.0, 0.0, 0.0, mode, 1.2);
    cubes.push_back(bigCube);

//    glRotatef(30.0, 1.0, 1.0, 1.0); //this is why the cube is slanted
}

void drawPlayer() {
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);

    //Prevents the player from leaving the box
    if (playerX < negativeBoundary) {
        playerX = negativeFixed;
    } else if (playerX > positiveBoundary) {
        playerX = positiveFixed;
    } else if (playerY > positiveBoundary) {
        playerY = positiveFixed;
    } else if (playerY < negativeBoundary) {
        playerY = negativeFixed;
    } else if (playerZ > positiveBoundary) {
        playerZ = positiveFixed;
    } else if (playerZ < negativeBoundary) {
        playerZ = negativeFixed;
    }

    glVertex3f(playerX, playerY, playerZ);
    glEnd();
}


//---------------------------------------
// Function to draw 3D cube
//---------------------------------------
//void cube(float midx, float midy, float midz, float size) {
//    // Define 8 vertices
//    float ax = midx - size / 2;
//    float ay = midy - size / 2;
//    float az = midz + size / 2;
//    float bx = midx + size / 2;
//    float by = midy - size / 2;
//    float bz = midz + size / 2;
//    float cx = midx + size / 2;
//    float cy = midy + size / 2;
//    float cz = midz + size / 2;
//    float dx = midx - size / 2;
//    float dy = midy + size / 2;
//    float dz = midz + size / 2;
//    float ex = midx - size / 2;
//    float ey = midy - size / 2;
//    float ez = midz - size / 2;
//    float fx = midx + size / 2;
//    float fy = midy - size / 2;
//    float fz = midz - size / 2;
//    float gx = midx + size / 2;
//    float gy = midy + size / 2;
//    float gz = midz - size / 2;
//    float hx = midx - size / 2;
//    float hy = midy + size / 2;
//    float hz = midz - size / 2;
//
//
//    // Draw 6 faces
//    glBegin(mode);
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex3f(ax, ay, az);
//    glVertex3f(bx, by, bz);
//    glVertex3f(cx, cy, cz);
//    glVertex3f(dx, dy, dz);
//    glEnd();
//
//    glBegin(mode);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(ax, ay, az);
//    glVertex3f(dx, dy, dz);
//    glVertex3f(hx, hy, hz);
//    glVertex3f(ex, ey, ez);
//    glEnd();
//
//    glBegin(mode);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(ax, ay, az);
//    glVertex3f(ex, ey, ez);
//    glVertex3f(fx, fy, fz);
//    glVertex3f(bx, by, bz);
//    glEnd();
//
//    glBegin(mode);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(gx, gy, gz);
//    glVertex3f(fx, fy, fz);
//    glVertex3f(ex, ey, ez);
//    glVertex3f(hx, hy, hz);
//    glEnd();
//
//    glBegin(mode);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(gx, gy, gz);
//    glVertex3f(cx, cy, cz);
//    glVertex3f(bx, by, bz);
//    glVertex3f(fx, fy, fz);
//    glEnd();
//
//    glBegin(mode);
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(gx, gy, gz);
//    glVertex3f(hx, hy, hz);
//    glVertex3f(dx, dy, dz);
//    glVertex3f(cx, cy, cz);
//    glEnd();
//}

void spawnCube() {
    Cube temp(playerX, playerY, playerZ, mode, 0.2);
    cubes.push_back(temp);
}


//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display() {
    // Incrementally rotate objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xangle, 1.0, 0.0, 0.0);
    glRotatef(yangle, 0.0, 1.0, 0.0);
    for (Cube c: cubes){
        c.draw();
    }
    drawPlayer();
//    glutSwapBuffers();
    glFlush();
}


//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y) {
    // Update angles

    if (key == 'F' || key == 'f') {
        fly = true;
        cout << "Fly mode toggled" << endl;
    } else if (key == 'R' || key == 'r') {
        fly = false;
        cout << "Rotate mode toggled" << endl;
    }

    if (fly == false) {
        if (key == 'x')
            xangle -= 5;
        else if (key == 'y')
            yangle -= 5;
        else if (key == 'X')
            xangle += 5;
        else if (key == 'Y')
            yangle += 5;
    }

    if (fly == true) {

        if (key == 'x')
            playerX -= movementSpeed;
        else if (key == 'X')
            playerX += movementSpeed;
        else if (key == 'y')
            playerY -= movementSpeed;
        else if (key == 'Y')
            playerY += movementSpeed;
        else if (key == 'Z')
            playerZ += movementSpeed;
        else if (key == 'z')
            playerZ -= movementSpeed;
        else if (key == 'v')
            spawnCube();
        else if (key == 'V')
            cubes.pop_back();
    }

    // Redraw objects
    glutPostRedisplay();
}


//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Homework 2: Cube");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    printf("Keyboard commands:\n");
    printf("   'F' - go into fly mode\n");
    printf("   'R' - go into rotate mode\n");
    printf("   Press x, X, y, Y, z, Z  to rotate or move depending on mode \n");

    glutMainLoop();
    return 0;
}