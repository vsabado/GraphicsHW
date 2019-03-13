//---------------------------------------
// Program: surface4.cpp
// Purpose: Use Phong shading to display
//          random wave surface model.
// Author:  John Gauch
// Date:    Spring 2012
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef MAC
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

// Transformation variables
#define ROTATE 1
#define Light1 2
#define Light2 3
#define Material 4
int xangle = 40;
int yangle = 0;
int zangle = 0;
int mode = ROTATE;

// Surface variables
#define SIZE 512
float Px[SIZE + 1][SIZE + 1];
float Py[SIZE + 1][SIZE + 1];
float Pz[SIZE + 1][SIZE + 1];
float Nx[SIZE + 1][SIZE + 1];
float Ny[SIZE + 1][SIZE + 1];
float Nz[SIZE + 1][SIZE + 1];
#define STEP 0.1

float Lx1 = 1.0, Ly1 = 1.0, Lz1 = 1.0;
float Lx2 = 1.0, Ly2 = 1.0, Lz2 = 1.0;
float r1 = 1.0, g1 = 1.0, b1 = 1.0;
float r2 = 1.0, g2 = 1.0, b2 = 1.0;


#include "shading.cpp"

//---------------------------------------
// Initialize surface points
//---------------------------------------
void init_surface(float Xmin, float Xmax, float Ymin, float Ymax) {
    // Initialize (x,y,z) coordinates of surface
    for (int i = 0; i <= SIZE; i++)
        for (int j = 0; j <= SIZE; j++) {
            Px[i][j] = Xmin + i * (Xmax - Xmin) / SIZE;
            Py[i][j] = Ymin + j * (Ymax - Ymin) / SIZE;
            Pz[i][j] = 0;
        }

    // Add randoms waves to surface
    for (int wave = 1; wave <= 10; wave++) {
        int rand_i = rand() % SIZE / wave;
        int rand_j = rand() % SIZE / wave;
        float length = sqrt(rand_i * rand_i + rand_j * rand_j);
        if (length >= 10)
            for (int i = 0; i <= SIZE; i++)
                for (int j = 0; j <= SIZE; j++) {
                    float angle = (rand_i * i + rand_j * j) / (length * length);
                    Pz[i][j] += 0.01 * sin(angle * 2 * M_PI);
                }
    }
}

//---------------------------------------
// Initialize surface normals
//---------------------------------------
void init_normals() {
    // Initialize surface normals
    for (int i = 0; i <= SIZE; i++)
        for (int j = 0; j <= SIZE; j++) {
            // Get tangents S and T
            float Sx = (i < SIZE) ? Px[i + 1][j] - Px[i][j] : Px[i][j] - Px[i - 1][j];
            float Sy = (i < SIZE) ? Py[i + 1][j] - Py[i][j] : Py[i][j] - Py[i - 1][j];
            float Sz = (i < SIZE) ? Pz[i + 1][j] - Pz[i][j] : Pz[i][j] - Pz[i - 1][j];
            float Tx = (j < SIZE) ? Px[i][j + 1] - Px[i][j] : Px[i][j] - Px[i][j - 1];
            float Ty = (j < SIZE) ? Py[i][j + 1] - Py[i][j] : Py[i][j] - Py[i][j - 1];
            float Tz = (j < SIZE) ? Pz[i][j + 1] - Pz[i][j] : Pz[i][j] - Pz[i][j - 1];

            // Calculate N = S cross T
            float Slength = sqrt(Sx * Sx + Sy * Sy + Sz * Sz);
            float Tlength = sqrt(Tx * Tx + Ty * Ty + Tz * Tz);
            if ((Slength * Tlength) > 0) {
                Nx[i][j] = (Sy * Tz - Sz * Ty) / (Slength * Tlength);
                Ny[i][j] = (Sz * Tx - Sx * Tz) / (Slength * Tlength);
                Nz[i][j] = (Sx * Ty - Sy * Tx) / (Slength * Tlength);
            }
        }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init() {
    // Initialize OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float radius = 1.2;
    glOrtho(-radius, radius, -radius, radius, -radius, radius);
    glEnable(GL_DEPTH_TEST);


    // Initialize surface
    init_surface(-1.0, 1.0, -1.0, 1.0);
    init_normals();
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

    // Initialize material properties
    init_material(Ka, Kd, Ks, 100 * Kp, 0.3, 0.3, 0.8);

    // Initialize smooth shading
    glShadeModel(GL_SMOOTH);
    init_light(GL_LIGHT1, Lx1, Ly1, Lz1, r1, g1, b1);
    init_light(GL_LIGHT2, Lx2, Ly2, Lz2, r2, g2, b2);

    // Draw the surface
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
            // glBegin(GL_LINE_LOOP);
            glBegin(GL_POLYGON);
            glNormal3f(Nx[i][j], Ny[i][j], Nz[i][j]);
            glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
            glNormal3f(Nx[i + 1][j], Ny[i + 1][j], Nz[i + 1][j]);
            glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);
            glNormal3f(Nx[i + 1][j + 1], Ny[i + 1][j + 1], Nz[i + 1][j + 1]);
            glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);
            glNormal3f(Nx[i][j + 1], Ny[i][j + 1], Nz[i][j + 1]);
            glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
            glEnd();
        }
    glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y) {
    // Initialize random surface
    if (key == 'i') {
        init_surface(-1.0, 1.0, -1.0, 1.0);
        init_normals();
    }

    // Determine if we are in ROTATE or TRANSLATE mode
    if ((key == 'm') || (key == 'M')) {
        printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
        mode = ROTATE;
    } else if (key == '1') {
        printf("Type x y z to decrease or X Y Z to increase light position for light 1 or p to reset position.\n");
        mode = Light1;
    } else if (key == '2') {
        printf("Type x y z to decrease or X Y Z to increase light position for light 2 or p to reset position.\n");
        mode = Light2;
    } else if (key == '3') {
        printf("Type a, A, s, S, d, D, P to manipulate material properties.\n");
        mode = Material;
    }

    // Handle ROTATE
    if (mode == ROTATE) {
        if (key == 'x')
            xangle -= 5;
        else if (key == 'y')
            yangle -= 5;
        else if (key == 'z')
            zangle -= 5;
        else if (key == 'X')
            xangle += 5;
        else if (key == 'Y')
            yangle += 5;
        else if (key == 'Z')
            zangle += 5;
    }

    //Handle Light1 translations
    if (mode == Light1) {
        if (key == 'x')
            Lx1 -= 5;
        else if (key == 'y')
            Ly1 -= 5;
        else if (key == 'z')
            Lz1 -= 5;
        else if (key == 'X')
            Lx1 += 5;
        else if (key == 'Y')
            Ly1 += 5;
        else if (key == 'Z')
            Lz1 += 5;
        if (key == 'r')
            r1 -= 1;
        else if (key == 'g')
            g1 -= 1;
        else if (key == 'b')
            b1 -= 1;
        else if (key == 'R')
            r1 += 1;
        else if (key == 'G')
            g1 += 1;
        else if (key == 'B')
            b1 += 1;
        else if (key == 'p') {
            Lx1 = 1;
            Lz1 = 1;
            Ly1 = 1;
            r1 = 1;
            g1 = 1;
            b1 = 1;
        }
    }

    //Handle Light1 translations
    if (mode == Light2) {
        if (key == 'x')
            Lx2 -= 5;
        else if (key == 'y')
            Ly2 -= 5;
        else if (key == 'z')
            Lz2 -= 5;
        else if (key == 'X')
            Lx2 += 5;
        else if (key == 'Y')
            Ly2 += 5;
        else if (key == 'Z')
            Lz2 += 5;
        if (key == 'r')
            r2 -= 1;
        else if (key == 'g')
            g2 -= 1;
        else if (key == 'b')
            b2 -= 1;
        else if (key == 'R')
            r2 += 1;
        else if (key == 'G')
            g2 += 1;
        else if (key == 'B')
            b2 += 1;
        else if (key == 'p') {
            Lx2 = 1;
            Lz2 = 1;
            Ly2 = 1;
            r2 = 1;
            b2 = 1;
            g2 = 1;
        }
    }


    if (mode == Material) {
        // Handle material properties
        if (key == 'a')
            Ka -= STEP;
        if (key == 'd')
            Kd -= STEP;
        if (key == 's')
            Ks -= STEP;
        if (key == 'p')
            Kp -= STEP;
        if (key == 'A')
            Ka += STEP;
        if (key == 'D')
            Kd += STEP;
        if (key == 'S')
            Ks += STEP;
        if (key == 'P')
            Kp += STEP;
        if (Ka < 0)
            Ka = 0;
        if (Kd < 0)
            Kd = 0;
        if (Ks < 0)
            Ks = 0;
        if (Kp < STEP)
            Kp = STEP;
    }

    glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[]) {
    // Create OpenGL window
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 400);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Surface");
    init();
    printf("Type r to enter ROTATE mode.\n");

    // Specify callback function
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}