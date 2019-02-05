#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int blastIntensity;
const int maxPoints = 400; //Max possible number of points
float x[maxPoints], y[maxPoints], accelX[maxPoints], accelY[maxPoints]; //Arrays with size of max possible points to track motion of each point
int timer, duration; //Used to calculate when we'll initialize for the next blast, Indicates how quickly the blast happens and the pointers disperse
double twoPi = 2.0 * M_PI;
int timerF2 = 0;

void idle() {
    glutPostRedisplay();
}

double randDouble() {
    return (1 - (-1)) * ((double) rand() / (double) RAND_MAX) + -1; //range -1 to 1
}

int randInt() {
    return rand() % 5 + 1; //Range 1 - 5, used to dictate how many fireworks will show
}

void setProperties(float startX, float startY) {
//    cout << "setProperties called!" << endl;
    blastIntensity = randDouble() * maxPoints; //Generate number of points that will show
    timer = 0; //reset timer
    duration = 500 * randDouble(); //Duration

    for (int i = 0; i < blastIntensity; i++) {
        x[i] = startX; //Sets all starting position X
        y[i] = startY; //Sets all starting position Y
        double circumference = randDouble() * twoPi; //2piR is the radius of a circle

        //Spreads out the firework over the course of duration
        accelX[i] = (cos(circumference) * randDouble()) / duration;
        accelY[i] = (sin(circumference) * randDouble()) / duration;
    }
}

void explodeF2(double x, double y, double z, int numOfLines, double red, double green, double blue) {

    for (int i = 0; i < numOfLines; i++) {
        glBegin(GL_LINES);
        glColor3f(red, green, blue);
        glVertex3f(x, y, z);
        glVertex3f(randDouble(), randDouble(), randDouble());
        glEnd();
    }
    glFlush();  // Render now
}


void initF2() {
    //Not necessary but this meets project requirements
    //Setting up properties for the F2 fireworks
    double firework2X = randDouble(); //Multiplied by randomNum to make it possible to get negative
    double firework2Y = randDouble();
    double firework2Z = randDouble();
    int minimumLines = 50;
    int maxLines = 200;
    int numOfLines = rand() % maxLines + minimumLines; //Randomly choose number of lines to draw
    double red = randDouble(); //Randomize color
    double green = randDouble();
    double blue = randDouble();
    explodeF2(firework2X, firework2Y, firework2Z, numOfLines, red, green, blue);
}

void explode(float red, float green, float blue, double light) {
    glPointSize(1.5);
    glBegin(GL_POINTS);
    glColor3f(red * light, green * light, blue * light);
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

    //Code for the F1 fireworks
    float red, green, blue; //RGB variables
    red = 0.5 + 0.5 + randDouble(); //Tried many combinations but this is the easiest on the eyes
    green = 0.5 + 0.5 + randDouble(); //RGB
    blue = 0.5 + 0.5 + randDouble(); //RGB
    double light = (duration - timer) / (double) duration;
    explode(red, green, blue, light);
    timer++;
    timerF2++;
    if (timerF2 == 50) {
        for (int i = 0; i < randInt(); i++) {
            initF2(); //This call will set the properties for F2 fireworks
        }
        timerF2 = 0;
    }

    if (timer > duration) {
        float startX = randDouble(); //Current x
        float startY = randDouble(); //Current y
        setProperties(startX, startY);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Homework 1: Fireworks");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}