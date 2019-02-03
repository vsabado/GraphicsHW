//Using http://www.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html as a guide
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int blastIntensity;
const int maxPoints = 4000; //Max possible number of points
float startX, startY; //Starting x,y
float x[maxPoints], y[maxPoints]; //Create arrays with size of max possible points
float accelX[maxPoints], accelY[maxPoints]; //Arrays with size of max possible points to track motion of each point
float red, green, blue; //RGB variables
int timer; //Used to calculate when we'll initialize for the next blast
int duration; //Indicates how quickly the blast happens and the pointers disperse
float twoPi = 2.0 * M_PI;

void idle() {
    glutPostRedisplay();
}

double randDouble(){
    return (rand() % 100) / 100.0;
}


void setProperties() {
cout << "setProperties called!" << endl;
    double temp, temp2;
    blastIntensity = randDouble() * maxPoints; //Number of points
    startX = randDouble(); //Current x
    startY = randDouble(); //Current y
    red = 0.5 + 0.5 * randDouble(); //RGB
    green = 0.5 + 0.5 * randDouble(); //RGB
    blue = 0.5 + 0.5 * randDouble(); //RGB
    timer = 0;
    duration = 200 * randDouble(); //Duration


/* initialize the blast */
    for (int j = 0; j < blastIntensity; j++) {
        x[j] = startX;
        y[j] = startY;
        temp = randDouble();
        temp2 = randDouble() * twoPi; //2piR is the radius of a circle
        accelX[j] = (cos(temp2) * temp) / duration;
        accelY[j] = (sin(temp2) * temp) / duration;
    }

}

void explode() {
    glPointSize(1.5);
    double glow = (duration - timer) / (double) duration;
    glColor3f(red * glow, green * glow, blue * glow);
    glBegin(GL_POINTS);
    for (int i = 0; i < blastIntensity; i++) {
        x[i] += accelX[i];
        y[i] += accelY[i];
        glVertex2f(x[i], y[i]);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}


//Allowing the display function to determine the RGB properties causes a situation
//in which the color changes multiple times throughout the explosion
//Allowing the function to dictate x,y also results in the fireworks moving around quickly and seemingly random
//Hence it cannot be in this function
void display() {
 cout << "Display called!" << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    explode();
    timer++;
    if (timer > duration) setProperties();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Homework 1: Fireworks");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}