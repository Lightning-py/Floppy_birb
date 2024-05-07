#include "pylon.hpp"
#include "randomUtils.hpp"

double Pylon::getXPos () {
    return this->x_pos;
}

void Pylon::loadDefaultColor () {
    std::vector<double> color = { 1.0f, 1.0f, 0 };
    first_vertex_color        = color;
    second_vertex_color       = color;
    third_vertex_color        = color;
    fourth_vertex_color       = color;
}

void Pylon::setOneColor (std::vector<double>& color) // применяет один цвет ко всем вершинам
{
    this->first_vertex_color  = color;
    this->second_vertex_color = color;
    this->third_vertex_color  = color;
    this->fourth_vertex_color = color;
}

void Pylon::setFourColors (std::vector<double>& first,
std::vector<double>& second,
std::vector<double>& third,
std::vector<double>& fourth) // применяет цвета к конкретным вершинам
{
    this->first_vertex_color  = first;
    this->second_vertex_color = second;
    this->third_vertex_color  = third;
    this->fourth_vertex_color = fourth;

    this->fith_vertex_color    = first;
    this->sixth_vertex_color   = second;
    this->seventh_vertex_color = third;
    this->eighth_vertex_color  = fourth;
}


void Pylon::setEightColors (std::vector<double>& first,
std::vector<double>& second,
std::vector<double>& third,
std::vector<double>& fourth,
std::vector<double>& fith,
std::vector<double>& sixth,
std::vector<double>& seventh,
std::vector<double>& eighth) {
    this->first_vertex_color  = first;
    this->second_vertex_color = second;
    this->third_vertex_color  = third;
    this->fourth_vertex_color = fourth;

    this->fith_vertex_color    = fith;
    this->sixth_vertex_color   = sixth;
    this->seventh_vertex_color = seventh;
    this->eighth_vertex_color  = eighth;
}

void Pylon::draw () {

    glLoadIdentity ();


    glTranslatef (this->x_pos, 0, 0); // перемещение в точку расположения нижней колонны


    // отрисовка нижней колонны
    glBegin (GL_QUADS);

    glColor3f (this->first_vertex_color[0], this->first_vertex_color[1],
    this->first_vertex_color[2]);
    glVertex3f (-1 * this->width / 2, this->y_first_height, 0);

    glColor3f (this->second_vertex_color[0], this->second_vertex_color[1],
    this->second_vertex_color[2]);
    glVertex3f (this->width / 2, this->y_first_height, 0);


    glColor3f (this->third_vertex_color[0], this->third_vertex_color[1],
    this->third_vertex_color[2]);
    glVertex3f (this->width / 2, -1, 0);

    glColor3f (this->fourth_vertex_color[0], this->fourth_vertex_color[1],
    this->fourth_vertex_color[2]);
    glVertex3f (-1 * this->width / 2, -1, 0);

    glEnd ();


    // отрисовка верхней части колонны
    glBegin (GL_QUADS);

    glColor3f (this->fith_vertex_color[0], this->fith_vertex_color[1],
    this->fith_vertex_color[2]);
    glVertex3f (-1 * this->width / 2, 1.0, 0);

    glColor3f (this->sixth_vertex_color[0], this->sixth_vertex_color[1],
    this->sixth_vertex_color[2]);
    glVertex3f (this->width / 2, 1, 0);


    glColor3f (this->seventh_vertex_color[0], this->seventh_vertex_color[1],
    this->seventh_vertex_color[2]);
    glVertex3f (this->width / 2, this->y_second_height, 0);

    glColor3f (this->eighth_vertex_color[0], this->eighth_vertex_color[1],
    this->eighth_vertex_color[2]);
    glVertex3f (-1 * this->width / 2, this->y_second_height, 0);

    glEnd ();
}

void Pylon::shift_left (double pos) {
    this->x_pos -= pos;
}


bool Pylon::isOvercome () {
    return this->overcome;
}

void Pylon::setOvercome () {
    this->overcome = true;
}


void Pylon::setRandomColors () {
    std::vector<double> color_1 = randColord ();

    std::vector<double> color_2 = randColord ();

    std::vector<double> color_3 = randColord ();

    std::vector<double> color_4 = randColord ();

    std::vector<double> color_5 = randColord ();

    std::vector<double> color_6 = randColord ();

    std::vector<double> color_7 = randColord ();

    std::vector<double> color_8 = randColord ();

    this->setEightColors (
    color_1, color_2, color_3, color_4, color_5, color_6, color_7, color_8);
}