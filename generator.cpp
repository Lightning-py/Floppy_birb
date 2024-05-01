#include "generator.hpp"

void Generator::generate_new_pylons () {
    double x_start_pos = 0.7;
    double interval    = 0.3;

    if (this->obstacles.size () > 0) {
        x_start_pos = this->obstacles.back ().getXPos () + interval;
    }


    int pylons_to_gen = 20 - this->obstacles.size ();

    for (int i = 0; i < pylons_to_gen; ++i) {
        obstacles.push_back (Pylon{ x_start_pos + i * interval, -0.1, 0.8, 0.1 });
    }
}

void Generator::kill_unused_pylons (double left_x_pos) {
    if (this->obstacles.size () == 0)
        return;

    while (this->obstacles.front ().getXPos () < left_x_pos) {
        obstacles.pop_front ();
    }
}

void Generator::clear () {
    this->obstacles.clear ();
}

void Generator::draw () {
    for (Pylon obstacle : this->obstacles) {
        obstacle.draw ();
    }
}

void Generator::shift_left_all (double pos) {
    for (int i = 0; i < this->obstacles.size (); ++i)
        obstacles[i].shift_left (pos);
}


std::deque<Pylon> Generator::getObstacles () { return this->obstacles; }
