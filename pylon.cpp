#include "pylon.hpp"


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
}

void Pylon::draw () {

    glLoadIdentity ();

    glTranslatef (getXPos (), 0.0, 0.0);

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

    glColor3f (this->first_vertex_color[0], this->first_vertex_color[1],
    this->first_vertex_color[2]);
    glVertex3f (-1 * this->width / 2, 1.0, 0);

    glColor3f (this->second_vertex_color[0], this->second_vertex_color[1],
    this->second_vertex_color[2]);
    glVertex3f (this->width / 2, 1, 0);


    glColor3f (this->third_vertex_color[0], this->third_vertex_color[1],
    this->third_vertex_color[2]);
    glVertex3f (this->width / 2, this->y_second_height, 0);

    glColor3f (this->fourth_vertex_color[0], this->fourth_vertex_color[1],
    this->fourth_vertex_color[2]);
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
    std::vector<double> color_1 = { (double (rand () % (100)) / 100),
        (double (rand () % (100)) / 100), (double (rand () % (100)) / 100) };

    std::vector<double> color_2 = { (double (rand () % (100)) / 100),
        (double (rand () % (100)) / 100), (double (rand () % (100)) / 100) };

    std::vector<double> color_3 = { (double (rand () % (100)) / 100),
        (double (rand () % (100)) / 100), (double (rand () % (100)) / 100) };

    std::vector<double> color_4 = { (double (rand () % (100)) / 100),
        (double (rand () % (100)) / 100), (double (rand () % (100)) / 100) };

    this->setFourColors (color_1, color_2, color_3, color_4);
}