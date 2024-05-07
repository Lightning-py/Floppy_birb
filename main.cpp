#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "bird.hpp"
#include "generator.hpp"
#include "map.hpp"

#define FPS 69
#define TICK_TIME (1000 / FPS)

bool tapped  = false;
bool pause   = false;
bool restart = false;


double fallingConstant = 6;
double vertSpeed       = 2;


Bird mainBird (0, 0, 0, fallingConstant, vertSpeed, 0, 0.3, 0.01, 0.01);
Generator gen;
Map map (mainBird, gen, TICK_TIME);

void keyboardHandler (unsigned char key, int x, int y);
void display ();


void keyboardHandler (unsigned char key, int x, int y) {
    if (!map.bird.isAlive () && key == 'r')
        restart = true;
    else if (key == 'p') {
        pause = !pause;
    } else
        tapped = true;
}


void update (int lol) {
    if (restart) {
        map.overcame_pylons = 0;
        map.bird            = Bird (0, 0, 0, 6, 2, 0, 0.3, 0.01, 0.01);
        map.gen.clear ();
        restart = false;
    }


    if (map.bird.isAlive ()) {

        if (!pause) {
            if (tapped) {
                map.bird.jump ();
                tapped = false;
            }
            map.update ();
        }
    }

    display ();

    glutTimerFunc (TICK_TIME, update, 0);
}

void display () {
    glClearColor (1, 1, 1, 1);
    glClear (GL_COLOR_BUFFER_BIT);

    glLoadIdentity ();

    map.draw ();

    glutSwapBuffers ();
}

int main (int argc, char** argv) {
    srand (time (0));

    glutInit (&argc, argv);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (800, 800);
    glutInitDisplayMode (GLUT_RGB);

    glutCreateWindow ("Floppy birb");

    glutDisplayFunc (display);
    glutKeyboardUpFunc (keyboardHandler);
    glutTimerFunc (TICK_TIME, update, 0);

    glutMainLoop ();

    return 0;
}
