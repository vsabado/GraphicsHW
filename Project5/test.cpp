//---------------------------------------
// Program: hw.cpp
// Purpose: Terrain creation
// Author:  Chandra Sekhar Hari
// Date:    March 2019
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"

// Transformation variables
#define ROTATE 1
int xangle = 10;
int yangle = 15;
int zangle = 10;
#define MAXCHAR 2048

int mode = ROTATE;
int NR = 0;
int NC = 0;
int SR = 0;
int SC = 0;

char** maze;
unsigned char *texturer;
unsigned char *textureb;
unsigned char *texturew;
int xdimr, ydimr;
int xdimb, ydimb;
int xdimw, ydimw;

//---------------------------------------
// Initialize texture image
//---------------------------------------
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   printf("Interpolating to %d by %d\n", xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}

//---------------------------------------
// Initialize surface
//---------------------------------------
void init_surface()
  {
    for(int i=0; i < NR; i++) {
      for (int j=0; j<NC; j++) {
        maze[i][j]=-1;
      }
    }
}

void readSize(char* str, int* r, int* c){
  int i=0;
  bool isFirstRead = false;
  while(str[i] != '\n'){
    if(str[i] == ' '){
      isFirstRead = true;
      i++;
    }
    if(!isFirstRead){
      *r = *r * 10 + str[i] - '0';
    }
    else{
      *c = *c * 10 + str[i] - '0';
    }
    i++;
  }
}

//---------------------------------------
// Read Maze.txt
//---------------------------------------
void readFile() {
  FILE *fp;
  int index = 0;
  char str[MAXCHAR];
  bool isFirstLineRead = false, isSecondLineRead = false;
  char* filename = (char *)"maze.txt";
  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("Could not open file %s",filename);
  }
  while (fgets(str, MAXCHAR, fp) != NULL){
    if(!isFirstLineRead){
      readSize(str, &NR, &NC);
      maze = new char*[NR];
      isFirstLineRead = true;
    }
    else if(!isSecondLineRead){
      readSize(str, &SR, &SC);
      isSecondLineRead = true;
    }
    else{
      maze[index] = new char[NC];
      for(int i=0;i<NC; i++){
        maze[index][i] = str[i];
      }
      index++;
    }
  }
  fclose(fp);
}
//---------------------------------------
// Function to draw 3D block
//---------------------------------------
void block(char type, float xmin, float ymin, float zmin,
	       float xmax, float ymax, float zmax)
{
  if(type == 'b'){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdimb, ydimb, 0, GL_RGB, GL_UNSIGNED_BYTE, textureb);
  }
  else if(type == 'r'){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdimr, ydimr, 0, GL_RGB, GL_UNSIGNED_BYTE, texturer);
  }
  else if(type == 'w'){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdimw, ydimw, 0, GL_RGB, GL_UNSIGNED_BYTE, texturew);
  }
   // Define 8 vertices
   float ax = xmin, ay = ymin, az = zmax;
   float bx = xmax, by = ymin, bz = zmax;
   float cx = xmax, cy = ymax, cz = zmax;
   float dx = xmin, dy = ymax, dz = zmax;
   float ex = xmin, ey = ymin, ez = zmin;
   float fx = xmax, fy = ymin, fz = zmin;
   float gx = xmax, gy = ymax, gz = zmin;
   float hx = xmin, hy = ymax, hz = zmin;

   // Draw 6 faces
   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(2.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(2.0, 2.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(0.0, 2.0);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(hx, hy, hz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(GL_POLYGON);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(hx, hy, hz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(cx, cy, cz);
   glEnd();
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
  glEnable(GL_DEPTH_TEST);

  // Init texture
  init_texture((char *)"textures/brick.jpg", textureb, xdimb, ydimb);
  init_texture((char *)"textures/rock.jpg", texturer, xdimr, ydimr);
  init_texture((char *)"textures/wood.jpg", texturew, xdimw, ydimw);
  glEnable(GL_TEXTURE_2D);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, textureb);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texturer);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texturew);

  readFile();
}

// ---------------------------------------
// Display callback for OpenGL
// ---------------------------------------
void display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   // glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);
   // block(-1, -1, -1, 1, 1, 1);
   for(int i=0; i<NR; i++){
     for(int j=0; j<NC; j++){
       if(maze[i][j] == ' '){
         continue;
       }
       block(maze[i][j], i, j, 0, i+1, j+1, 2);
     }
   }

   // Draw all walls
   // for (int i=0; i<=count; i++)
   //    if ((point[i][0] != point[i][2]) || (point[i][1] != point[i][3]))
   //       wall(point[i][0], point[i][1], point[i][2], point[i][3]);
   glFlush();



}

// ---------------------------------------
// Keyboard callback for OpenGL
// ---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Determine if we are in ROTATE or TRANSLATE mode
   if ((key == 'o') || (key == 'O'))
   {
      mode = ROTATE;
      printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
   }

   // Handle ROTATE
   if (mode == ROTATE)
   {
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
   printf("%d %d %d", xangle, yangle, zangle);

   glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Maze World");
   init();
   for(int i=0; i<NR;i++){
     for(int j = 0; j<NC; j++){
       printf("%c", maze[i][j]);
     }
     printf("\n");
   }
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
