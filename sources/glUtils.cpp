#pragma once

#include <GL/glut.h>
#include <cmath>


// рисует круг заданного радиуса
void drawCircle (double center_x, double center_y, double radius) {
    glColor3f (0.0f, 1.0f, 0.0f);
    double theta;
    double pi   = 3.14;
    double step = 0.5f;

    glBegin (GL_TRIANGLE_FAN);
    for (GLfloat a = 0.0f; a < 180.0f; a += step) {
        theta = 2.0f * pi * a / 180.0f;
        glColor4f (a / 360.0f, 1.0f, 1.0f - a / 360.0f, 1.0f);
        glVertex3f (center_x + radius * cos (theta), center_y + radius * sin (theta), 0.0f);
    }

    glEnd ();
}

// рисует нижнюю половину круга заданного радиуса с дополнительными параметрами
void drawLowerHalfCircle (double center_x, double center_y, double radius, double red, double green, double blue) {
    glColor3f (red, green, blue);

    double theta;
    double pi   = 3.14;
    double step = 0.5f;

    glBegin (GL_TRIANGLE_FAN);
    for (GLfloat a = 0.0f; a < 90.0f; a += step) {
        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (center_x + radius * cos (theta), center_y + radius * sin (theta), 0.0f);
    }

    glEnd ();
}

// рисует верхнюю половину круга заданного радиуса с дополнительными параметрами
void drawRightHalfCircle (double center_x, double center_y, double radius, double red, double green, double blue) {
    glColor3f (red, green, blue);

    double theta;
    double pi   = 3.14;
    double step = 0.5f;

    glBegin (GL_TRIANGLE_FAN);
    for (GLfloat a = -45.0f; a < 45.0f; a += step) {
        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (center_x + radius * cos (theta), center_y + radius * sin (theta), 0.0f);
    }

    glEnd ();
}

// рисует левую половину круга заданного радиуса с дополнительными параметрами
void drawLeftHalfCircle (double center_x, double center_y, double radius, double red, double green, double blue) {
    glColor3f (red, green, blue);

    double theta;
    double pi   = 3.14;
    double step = 0.5f;

    glBegin (GL_TRIANGLE_FAN);
    for (GLfloat a = 45.0f; a < 135.0f; a += step) {
        theta = 2.0f * pi * a / 180.0f;
        glVertex3f (center_x + radius * cos (theta), center_y + radius * sin (theta), 0.0f);
    }

    glEnd ();
}