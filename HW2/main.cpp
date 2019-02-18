//
// Created by vladpc on 2/17/19.
//

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Cube.h"

using namespace std;

//Important globals
GLenum mode = GL_LINE_LOOP;
int xangle = 10;
int yangle = 15;
int zangle = 0;
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
}


//---------------------------------------
// Draw the player
//---------------------------------------

void drawPlayer() {
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(playerX, playerY, playerZ);
    glEnd();
}

//---------------------------------------
// Spawn the cube when the key is pressed
//---------------------------------------
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
    glRotatef(zangle, 0.0, 0.0, 1.0);
    for (Cube c: cubes) {
        c.draw();
    }
    drawPlayer();
    glFlush();
}

//---------------------------------------
// Restarts all values to default but keeps the boxes
//---------------------------------------
void restart() {
    zangle = 0;
    xangle = 10;
    yangle = 15;
    playerX = 0;
    playerY = 0;
    playerZ = 0;
}

//---------------------------------------
// Restarts all values to default and removes all the cubes
//---------------------------------------
void fullRestart() {
    zangle = 0;
    xangle = 10;
    yangle = 15;
    playerX = 0;
    playerY = 0;
    playerZ = 0;
    cubes.erase(cubes.begin() + 1, cubes.end());
}

//---------------------------------------
// Shows one dimensional view for debugging
//---------------------------------------
void oneDimensionView(){
    zangle = 0;
    xangle = 0;
    yangle = 0;
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y) {
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
        else if (key == 'z')
            zangle -= 5;
        else if (key == 'Z')
            zangle += 5;
    }

    //Update player position
    if (fly == true) {
        if (key == 'x') {
            playerX -= movementSpeed;
            if (playerX < negativeBoundary)
                playerX = negativeFixed;
        } else if (key == 'X') {
            playerX += movementSpeed;
            if (playerX > positiveBoundary)
                playerX = positiveFixed;
        } else if (key == 'y') {
            playerY -= movementSpeed;
            if (playerY < negativeBoundary)
                playerY = negativeFixed;
        } else if (key == 'Y') {
            playerY += movementSpeed;
            if (playerY > positiveBoundary)
                playerY = positiveFixed;
        } else if (key == 'Z') {
            playerZ += movementSpeed;
            if (playerZ > positiveBoundary)
                playerZ = positiveFixed;
        } else if (key == 'z') {
            playerZ -= movementSpeed;
            if (playerZ < negativeBoundary)
                playerZ = negativeFixed;
        }
    }

    //Spawn and remove boxes
    if (key == '+')
        spawnCube();
    else if (key == '-' && cubes.size() != 1) {
        for (int i = 1; i < cubes.size(); i++) {
            if (cubes[i].isEqual(playerX, playerY, playerZ)) {
                cout << "Found one!" << endl;

                //Approach one: remove the index at its current position
//                cubes.erase(cubes.begin() + i);

                //Approach two: moves the index to the end and call pop_back()
                cubes[i] = cubes.back();
                cubes.pop_back();
            }
        }
    }

    //Restart the world
    if (key == 'd')
        restart();
    else if (key == 'D')
        fullRestart();
    else if (key == '`')
        oneDimensionView();

//    cout << "PlayerX: " << playerX << endl;
//    cout << "PlayerY: " << playerY << endl;
//    cout << "PlayerZ: " << playerZ << endl;

    // Redraw objects
    glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(1100, 1100);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Homework 2: BlockWorld");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();

    printf("Keyboard commands:\n");
    printf("   Currently in fly mode \n");
    printf("   Press F/f - go into fly mode\n");
    printf("   Press R/r - go into rotate mode\n");
    printf("   Fly mode: Press x/X for left/right, y/Y for up/down, z/Z for forward/background \n");
    printf("   Rotate mode: Press x/X, y/Y, z/Z \n");
    printf("   Press + to place box and - to remove box \n");
    printf("   Press d to restart position and maintain cubes, D to restart position and remove cubes \n");
    printf("   Press ` for one dimensional view \n");
//    printf("   Press q/Q to go toggle movement speed 0.03/0.2 \n");
    glutMainLoop();
    return 0;
}