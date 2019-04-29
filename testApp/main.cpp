//----------------------------------------------
//Program: main.cpp
//Purpose: To implement all the classes functions into
//a running and operating program
//
//Author: Tomas Stevens
//Date: 5/01/19
//----------------------------------------------
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Include ray tracing and phong shading code
#include "raytracing.h"
#include "phong.h"

// Global variables
#define XDIM 1000
#define YDIM 800
unsigned char Object[YDIM][XDIM][3];

Point3D intersect, temp1, temp2, cam, point, center[10];
ColorRGB color, shade, obj[10];
Vector3D dir, normal, vec;
Phong ps[4];
Sphere3D spheres[10];
Ray3D ray, shadow;

float r, g, b, x, y, z, a[4], d[4], s[4], p[4];

//----------------------------------------------
//Reading the test file to form the spheres from coordinates provided
//----------------------------------------------
int read()
{
	ifstream din;
	din.open("test.txt");

	string input;
	int num = 0;

	while (din >> input)
	{
		if (input == "Camera")
		{
			din >> x >> y >> z;
			cam.set(x, y, -8000);
			for (int i = 0; i < 4; i++)
			{
				ps[i].SetCamera(cam);
			}
		}
		else if (input == "Light")
		{
			din >> r >> g >> b >> x >> y >> z;
			color.set(r, b, g);
			dir.set(x, y, z);
			for (int i = 0; i < 4; i++)
			{
				ps[i].SetLight(color, dir);
			}
		}
		else if (input == "Object")
		{
			if( num < 10){
				din >> r >> g >> b >> a[num] >> d[num] >> s[num] >> p[num];
				obj[num].set(r, g, b);
				num++;				// number of spheres in file capped at 10 for screen clarity
			}
		}

	}
	return num;
}

//----------------------------------------------
//randomly setting the spheres placements
//----------------------------------------------
void setSpheres(int bob)
{
	srand ( time(NULL) );
	for(int i = 0; i < bob; i++) {
		int randNumx = rand()% 400 + (-200);
		int randNumy = rand()% 400 + (-200);
		int randNumz = rand()% 400 + (-200);
		cout << randNumx << randNumy << randNumz << endl;
		center[i].set(randNumx,randNumy,randNumz);

		int randNumcent = rand()%(100 - 70) + 70;
		spheres[i].set(center[i], randNumcent);

	}
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
	// Initialize OpenGL
	glClearColor(0.0, 0.0, 0.0, 1.0);
//	int bobby = 0;
//	bobby = read();
//
//	setSpheres(bobby);
	// Print command menu
	cout << "Program commands:\n"
		<< "   'q' - exit program\n";
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------


void display()
{

    Point3D intersect, temp1, temp2, cam, point, center[10];
    ColorRGB color, shade, obj[10];
    Vector3D dir, normal, vec;
    Phong ps[4];
    Sphere3D spheres[10];
    Ray3D ray, shadow;

    float r, g, b, x, y, z, a[4], d[4], s[4], p[4];

	for (int i = 0; i < YDIM; i++)
	{
		for (int z = 0; z < XDIM; z++)
		{


			bool intersected = false;
			for (int f = 0; f < 4; f++)
			{
				point.set(z - XDIM / 2, i - YDIM / 2, 0);
				ray.set(cam, point);

				if (spheres[f].get_intersection(ray, intersect, normal))
				{
					temp1 = spheres[f].center;

					if (cam.distance(temp1) > cam.distance(intersect) || intersected == false)
					{
						shadow.set(intersect, dir);
						ps[f].SetObject(obj[f], a[f], d[f], s[f], p[f]);

						for (int y = 0; y < 4; y++)
						{
							if (spheres[y].get_intersection(shadow, temp2, vec) && y != f)
							{
								ps[f].SetObject(obj[f], a[f], 0, 0, p[f]);
							}
						}

						ps[f].GetShade(intersect, normal, shade);

						Object[i][z][0] = shade.R;
						Object[i][z][1] = shade.G;
						Object[i][z][2] = shade.B;

						temp1.set(intersect.px, intersect.py, intersect.pz);
						intersected = true;
					}
				}
			}

		}
	}

	// Display Object
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(XDIM, YDIM, GL_RGB, GL_UNSIGNED_BYTE, Object);
	glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	// Ends the program
	if (key == 'q')
		exit(0);
	if (key =='r') {
		int bobby = 0;
		bobby = read();				//testing purposes do not use
		setSpheres(bobby);
	}
	// Display Object

	glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
	// Create OpenGL window
	glutInit(&argc, argv);
	glutInitWindowSize(XDIM, YDIM);
	glutInitWindowPosition(200, 15);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("everybody loves Ray Tracing");
	init();

	// Specify callback function
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}