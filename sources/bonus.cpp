#include <GL/glut.h>
#include <vector>

#include "bonus.hpp"

double Bonus::getXPos () {
    return this->x_pos;
}

void Bonus::draw () {
    glLoadIdentity ();

    glTranslatef (getXPos (), getYPos (), 0.0);

    glColor3f (color[0], color[1], color[2]);

    glBegin (GL_QUADS);

    glVertex3d (-1 * width / 2, -1 * height / 2, 0.0);
    glVertex3d (-1 * width / 2, height / 2, 0.0);
    glVertex3d (width / 2, height / 2, 0.0);
    glVertex3d (width / 2, -1 * height / 2, 0.0);

    glEnd ();
}

unsigned int Bonus::getBonusType () {
    return this->bonus_type;
}

void Bonus::shift_left (double pos) {
    this->x_pos -= pos;
}

double Bonus::getYPos () {
    return this->y_pos;
}
