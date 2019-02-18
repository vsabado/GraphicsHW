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
float positiveBoundary = 0.6;
float negativeBoundary = -0.6;
float positiveFixed = 0.6;
float negativeFixed = -0.6;
bool fly = true;
float movementSpeed = 0.2;
vector<Cube> cubes;
//bool freeMode = false;

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
    Cube bigCube(0.0, 0.0, 0.0, mode, 1.4);
    cubes.push_back(bigCube);

//    glRotatef(30.0, 1.0, 1.0, 1.0); //this is why the cube is slanted
}

void drawPlayer() {
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
//    if (playerX + movementSpeed + 0.05 > positiveBoundary)
//        movementSpeed = 0;
//    else if (playerX - movementSpeed  - 0.055< negativeBoundary)
//        movementSpeed = 0;
//    else if (playerY + movementSpeed + 0.055> positiveBoundary)
//        movementSpeed = 0;
//    else if (playerY - movementSpeed - 0.055< negativeBoundary)
//        movementSpeed = 0;
//    else if (playerZ + movementSpeed + 0.055> positiveBoundary)
//        movementSpeed = 0;
//    else if (playerZ - movementSpeed -0.055 < negativeBoundary)
//        movementSpeed = 0;
//    else
//        movementSpeed = 0.2;


    glVertex3f(playerX, playerY, playerZ);
    glEnd();
}


void spawnCube() {
    Cube temp(playerX, playerY, playerZ, GL_POLYGON, 0.2);
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
    for (Cube c: cubes) {
        c.draw();
    }
    drawPlayer();
    glFlush();
}


void playerBound(){
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
}


//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y) {

    //Free mode disabled for now
//    if (key == 'q') {
//        freeMode = true;
//        cout << "Movement speed set to 0.03" << endl;
//    } else if (key == 'Q') {
//        freeMode = false;
//        cout << "Movement speed set to 0.2" << endl;
//    }

//    if (freeMode) {
//        movementSpeed = 0.03;
//    } else
//        movementSpeed = 0.2;

    //Switch between rotate and fly modes
    if (key == 'F' || key == 'f') {
        fly = true;
        cout << "Fly mode toggled" << endl;
    } else if (key == 'R' || key == 'r') {
        fly = false;
        cout << "Rotate mode toggled" << endl;
    }

    // Update angles
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

    //Update player position
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
    }

    playerBound();

    if (key == '+')
        spawnCube();
    else if (key == '-' && cubes.size() != 1) {
        for (int i = 1; i < cubes.size(); i++) {
            if (cubes[i].isEqual(playerX, playerY, playerZ)) {
                cout << "Found one!" << endl;
//                cubes.erase(cubes.begin() + i);
                cubes[i] = cubes.back();
                cubes.pop_back();
            }
        }
    }
//        cubes.pop_back();

    cout << "PlayerX: " << playerX << endl;
    cout << "PlayerY: " << playerY << endl;
    cout << "PlayerZ: " << playerZ << endl;


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
    printf("   Press F/f - go into fly mode\n");
    printf("   Press R/r - go into rotate mode\n");
    printf("   Fly mode: Press x/X for left/right, y/Y for up/down, z/Z for forward/background \n");
    printf("   Rotate mode: Press x/X, y/Y, z/Z \n");
    printf("   Press + to place box and - to remove box \n");
//    printf("   Press q/Q to go toggle movement speed 0.03/0.2 \n");


    glutMainLoop();
    return 0;
}