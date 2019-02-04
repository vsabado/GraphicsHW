//Using http://www.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html as a guide
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int blastIntensity;
const int maxPoints = 300; //Max possible number of points
float x[maxPoints], y[maxPoints], z[maxPoints], accelX[maxPoints], accelY[maxPoints]; //Arrays with size of max possible points to track motion of each point
int timer, duration; //Used to calculate when we'll initialize for the next blast, Indicates how quickly the blast happens and the pointers disperse
float twoPi = 2.0 * M_PI;

void idle() {
    glutPostRedisplay();
}

double randDouble() {
    return (rand() % 100) / 100.0;
}


void setProperties(float startX, float startY) {
    cout << "setProperties called!" << endl;
    double circumference;
    blastIntensity = randDouble() * maxPoints; //Generate number of points that will show
    timer = 0; //reset timer
    duration = 300 * randDouble(); //Duration

    for (int i = 0; i < blastIntensity; i++) {
        x[i] = startX; //Sets all starting position X
        y[i] = startY; //Sets all starting position Y
        circumference = randDouble() * twoPi; //2piR is the radius of a circle
        accelX[i] =
                (cos(circumference) * randDouble()) / duration; //Spreads out the firework over the course of duration
        accelY[i] = (sin(circumference) * randDouble()) / duration;
    }
}

void explode(float red, float green, float blue, double light) {
    cout << "Explode called!" << endl;
    glPointSize(1.5);
    glColor3f(red * light, green * light, blue * light);
    glBegin(GL_POINTS);
    for (int i = 0; i < blastIntensity; i++) {
        x[i] += accelX[i];
        y[i] += accelY[i];
        glVertex2f(x[i], y[i]);
    }
    glEnd();
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
}


//Allowing the display function to determine the RGB properties causes a situation
//in which the color changes multiple times throughout the explosion
//Allowing the function to dictate x,y also results in the fireworks moving around quickly and seemingly random
//Unless it is delayed via a timer
void display() {
    cout << "Display called!" << endl;
    float red, green, blue; //RGB variables
    red = 0.5 + 0.5 + randDouble(); //Tried many combinations but this is the easiest on the eyes
    green = 0.5 + 0.5 + randDouble(); //RGB
    blue = 0.5 + 0.5 + randDouble(); //RGB
    double light = (duration - timer) / (double) duration;
    explode(red, green, blue, light);
    timer++;
    if (timer > duration) {
        float startX = randDouble(); //Current x
        float startY = randDouble(); //Current y
        setProperties(startX, startY);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Homework 1: Fireworks");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}