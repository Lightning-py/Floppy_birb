#include <GL/glut.h> /* glut graphics library */
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


#define TICK_TIME 10

double vertSpeed       = 6;
double speed           = 0;
double y_pos           = 0.0;
double fallingConstant = 20;

bool tapped = false;

void keyboardHandler (unsigned char key, int x, int y);
void updatePosition (int lol);
void display ();


void keyboardHandler (unsigned char key, int x, int y) {
    tapped = true;
}

void updatePosition (int lol) {
    if (tapped) {
        tapped = false;
        speed  = vertSpeed;
    }
    y_pos += speed * TICK_TIME / 1000;
    speed -= fallingConstant * TICK_TIME / 1000;


    display ();

    glutTimerFunc (TICK_TIME, updatePosition, 0);
}

void display () {
    glClearColor (1, 1, 1, 1);
    glClear (GL_COLOR_BUFFER_BIT);

    glLoadIdentity ();

    glTranslatef (0, y_pos, 0);

    glColor3f (1.0, 1.0, 0.0);

    glBegin (GL_QUADS);
    glVertex3f (-0.05, -0.05, 0);
    glVertex3f (-0.05, 0.05, 0);
    glVertex3f (0.05, 0.05, 0);
    glVertex3f (0.05, -0.05, 0);
    glEnd ();

    glutSwapBuffers ();
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (800, 800);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow ("Floppy birb");

    glutDisplayFunc (display);
    glutKeyboardUpFunc (keyboardHandler);
    glutTimerFunc (TICK_TIME, updatePosition, 0);

    glutMainLoop ();

    return 0;
}
