#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#include "libim/im_color.h"

using namespace std;

char **maze;
int mazeR = 0, mazeC = 0, startR = 0, startC = 0;
unsigned char *brick, *rock, *wood, *grass, *fire;
int x, y;
int xangle = -35, yangle = 0, zangle = 0, xpos = -10, ypos = -10, zpos = 10;

#define ROTATE 1
#define TRANSLATE 2
#define PLAYER 3
int mode = PLAYER;

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y) {
    // Determine if we are in ROTATE or TRANSLATE mode
    if ((key == 'r') || (key == 'R')) {
        printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
        mode = ROTATE;
    } else if ((key == 't') || (key == 'T')) {
        printf("Type x y z to decrease or X Y Z to increase TRANSLATION distance.\n");
        mode = TRANSLATE;
    } else if ((key == 'p') || (key == 'P')) {
        printf("Type w,a,s,d to move up, left, down, right.\n");
        mode = PLAYER;
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
        glutPostRedisplay();
    }

    // Handle TRANSLATE
    if (mode == TRANSLATE) {
        if (key == 'x')
            xpos -= 5;
        else if (key == 'y')
            ypos -= 5;
        else if (key == 'z')
            zpos -= 5;
        else if (key == 'X')
            xpos += 5;
        else if (key == 'Y')
            ypos += 5;
        else if (key == 'Z')
            zpos += 5;
        glutPostRedisplay();
    }

    //Handle PLAYER movement
    if (mode == PLAYER) {
        if (key == 'd') {
            if (maze[startR + 1][startC] != ' ') {
                //do nothing
            } else {
                maze[startR][startC] = ' ';
                startR++;
                maze[startR][startC] = 'p';
            }
        } else if (key == 'a') {
            if (maze[startR - 1][startC] != ' ') {
                //do nothing
            } else {
                maze[startR][startC] = ' ';
                startR--;
                maze[startR][startC] = 'p';
            }
        } else if (key == 's') {
            if (maze[startR][startC - 1] != ' ') {
                //do nothing
            } else {
                maze[startR][startC] = ' ';
                startC--;
                maze[startR][startC] = 'p';
            }
        } else if (key == 'w') {
            if (maze[startR][startC + 1] != ' ') {
                //do nothing
            } else {
                maze[startR][startC] = ' ';
                startC++;
                maze[startR][startC] = 'p';
            }
        }
    }
    glutPostRedisplay();
}

//---------------------------------------
// Function to draw 3D block
//---------------------------------------
void block(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax) {
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

// ---------------------------------------
// Display callback for OpenGL
// ---------------------------------------
void image(unsigned char *type){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, type);
}

void drawMaze() {
    for (int i = 0; i < mazeR; i++) {
        for (int j = 0; j < mazeC; j++) {
            if (maze[i][j] == ' ') {
                image(grass);
                block(i, j, 1, i + 1, j + 1, 0);
            } else if (maze[i][j] == 'b') {
                image(brick);
                block(i, j, 1, i + 1, j + 1, 2);
            } else if (maze[i][j] == 'w') {
                image(wood);
                block(i, j, 1, i + 1, j + 1, 2);
            } else if (maze[i][j] == 'p') {
                image(fire);
                block(i, j, 1, i + 1, j + 1, 2);
            } else if (maze[i][j] == 'r') {
                image(rock);
                block(i, j, 1, i + 1, j + 1, 2);
            }
        }
    }
}

void display() {
    // Incrementally rotate objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xpos, ypos, zpos);
    glRotatef(xangle, 1.0, 0.0, 0.0);
    glRotatef(yangle, 0.0, 1.0, 0.0);
    glRotatef(zangle, 0.0, 0.0, 1.0);
    drawMaze();
    glFlush();
}

//---------------------------------------
// Initialize texture image
//---------------------------------------
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim) {
    // Read jpg image
    im_color image;
    image.ReadJpg(name);
    printf("Reading image %s\n", name);
    xdim = 1;
    while (xdim < image.R.Xdim) xdim *= 2;
    xdim /= 2;
    ydim = 1;
    while (ydim < image.R.Ydim) ydim *= 2;
    ydim /= 2;
    image.Interpolate(xdim, ydim);

    // Copy image into texture array
    texture = (unsigned char *) malloc((unsigned int) (xdim * ydim * 3));
    int index = 0;
    for (int y = 0; y < ydim; y++)
        for (int x = 0; x < xdim; x++) {
            texture[index++] = (unsigned char) (image.R.Data2D[y][x]);
            texture[index++] = (unsigned char) (image.G.Data2D[y][x]);
            texture[index++] = (unsigned char) (image.B.Data2D[y][x]);
        }
}

//---------------------------------------
// Initialize the maze
//---------------------------------------
void printArray(int col, int row) {
    //Loop through the maze and print
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

void populateMaze() {
    vector<string> mazeStrings;
    ifstream file("maze.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            mazeStrings.push_back(line);
        }
    }
    file.close();
    mazeR = atoi(mazeStrings[0].substr(0, mazeStrings[0].find(' ')).c_str());
    mazeC = atoi(mazeStrings[0].substr(3, mazeStrings[0].find(' ')).c_str());
    startR = atoi(mazeStrings[1].substr(0, mazeStrings[0].find(' ')).c_str());
    startC = atoi(mazeStrings[1].substr(2, mazeStrings[0].find(' ')).c_str());

    maze = new char *[mazeC];
    for (int i = 0; i < mazeC; i++) {
        maze[i] = new char[mazeR];
    }

    mazeStrings.erase(mazeStrings.begin(), mazeStrings.begin() + 2);

    for (int i = 0; i < mazeStrings.size(); i++) {
        for (int j = 0; j < mazeStrings[i].length(); j++) {
            maze[i][j] = mazeStrings[i][j];
        }
    };
    maze[startR][startC] = 'p';

    printArray(mazeR, mazeC);
    printf("Type w,a,s,d to move up, left, down, right.\n");
}

void initialize() {
    // Init view
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12.0, 12.0, -12.0, 12.0, -12.0, 12.0);
    glEnable(GL_DEPTH_TEST);

    // Init texture
    init_texture((char *) "textures/brick.jpg", brick, x, y);
    init_texture((char *) "textures/rock.jpg", rock, x, y);
    init_texture((char *) "textures/wood.jpg", wood, x, y);
    init_texture((char *) "textures/grass.jpg", grass, x, y);
    init_texture((char *) "textures/fire.jpg", fire, x, y);
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    populateMaze();
}

int main(int argc, char *argv[]) {
    // Create OpenGL window
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Homework 5");
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}