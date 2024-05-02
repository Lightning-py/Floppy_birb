#include <algorithm>
#include <iostream>

#include "generator.hpp"
#include "randomUtils.hpp"

void Generator::generate_new_pylons (unsigned int pylons_overcame) {
    double x_start_pos = 0.7;
    double interval    = 0.3;

    if (this->obstacles.size () > 0) {
        x_start_pos = this->obstacles.back ().getXPos () + interval;
    }

    int pylons_to_gen = 20 - this->obstacles.size ();

    for (int i = 0; i < pylons_to_gen; ++i) {
        double space_size =
        0.6; // пока что так, потом можно изменять в зависимости от количества пройденных препятствий

        double first  = randDouble (space_size - 1, 1 - space_size, 100);
        double second = 0.0;

        if (first + space_size >= 1.8) {
            second = first - space_size;
            std::swap (first, second);
        } else
            second = first + space_size;

        Pylon obstacle{ x_start_pos + i * interval, first, second, 0.1, space_size };

        obstacle.setRandomColors ();

        obstacles.push_back (obstacle);
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


std::deque<Pylon> Generator::getObstacles () {
    return this->obstacles;
}


void Generator::setObstacle (int pos, Pylon& pylon) {
    this->obstacles[pos] = pylon;
}