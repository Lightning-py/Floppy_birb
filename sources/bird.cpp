#include "bird.hpp"
#include "glUtils.hpp"
#include <algorithm>


double Bird::getXSpeed () {
    return this->x_speed;
}

void Bird::make_x_speed_bigger (double multiplier) {
    this->x_speed *= multiplier;
}


double Bird::getSpeed () {
    return this->speed;
}

void Bird::setSpeed (double speed) {
    this->speed = speed;
}

double Bird::getFallingConstant () {
    return this->fallingConstant;
}

void Bird::setFallingConstant (double fallingConstant) {
    this->fallingConstant = fallingConstant;
}

double Bird::getXPos () {
    return this->x_pos;
}

void Bird::setXPos (double x_pos) {
    this->x_pos = x_pos;
}

void Bird::setRotation (int rotation) {
    this->rotation = rotation;
}

double Bird::getYPos () {
    return this->y_pos;
}

void Bird::setYPos (double y_pos) {
    this->y_pos = y_pos;
}

bool Bird::isAlive () {
    return this->alive;
}

void Bird::update (double tick_time) {
    if (!isAlive ())
        return;

    // Y
    setYPos (getYPos () + getSpeed () * tick_time / 1000);
    setSpeed (getSpeed () - getFallingConstant () * tick_time / 1000);
    updateRotation ();

    // X

    // setXPos (getXPos () + getXSpeed () * tick_time / 1000);
}

void Bird::updateRotation () {
    if (speed >= 0) {
        this->rotation = getSpeed () * 60 / this->vertSpeed;
    } else {
        this->rotation = std::max (getSpeed () * 60 / this->vertSpeed, -60.0);
    }
}

void Bird::jump () {
    this->speed = this->vertSpeed;
}

void Bird::draw () {
    // glTranslated (0.0, getYPos (), 0);
    // glRotated (this->rotation, 0.0, 0.0, 1.0);

    // drawLowerHalfCircle (0, 0, 0.05, 1.0, 1.0, 0.0);
    // drawLowerHalfCircle (0, 0, 0.02, 0.0, 1.0, 0.0);
    // drawRightHalfCircle (0.03, 0.03, 0.03, 1.0, 1.0, 0.0);
    this->grid.drawInPosition (std::make_pair (this->getXPos (), this->getYPos ()));
}

void Bird::kill () {
    this->lives--;
    if (this->lives < 1) {
        this->alive = false;
    }
}

void Bird::respawn () {
    this->setRotation (0);
    this->setSpeed (0.0);
    this->setYPos (0.0);
    this->setXPos (0.0);
}

void Bird::make_smaller (double multiplier) {
    this->grid.setSquareSize (this->grid.getSquareSize () / multiplier);
}

void Bird::make_bigger (double multiplier) {
    this->grid.setSquareSize (this->grid.getSquareSize () * multiplier);
}

void Bird::set_default_size () {
    this->grid.setSquareSize (this->default_size);
}

void Bird::heal () {
    if (this->lives < 6)
        this->lives++;
}

double Bird::getSize () {
    return this->grid.getWidth () * this->grid.getSquareSize ();
}


double Bird::getDefaultSize () {
    return this->default_size * this->grid.getWidth ();
}