#include <algorithm>
#include <iostream>

#include "generator.hpp"
#include "randomUtils.hpp"

void Generator::generate_new_pylons (unsigned int pylons_overcame) {
    double x_start_pos = 0.7;
    double interval    = 0.6;

    if (this->obstacles.size () > 0) {
        x_start_pos = this->obstacles.back ().getXPos () + interval;
    }

    int pylons_to_gen = 20 - this->obstacles.size ();

    for (int i = 0; i < pylons_to_gen; ++i) {
        double pylon_x_pos = x_start_pos + i * interval;

        double space_size =
        0.6; // пока что так, потом можно изменять в зависимости от количества пройденных препятствий

        double first  = randDouble (space_size - 1, 1 - space_size, 100);
        double second = 0.0;

        if (first + space_size >= 1.8) {
            second = first - space_size;
            std::swap (first, second);
        } else
            second = first + space_size;

        Pylon obstacle{ pylon_x_pos, first, second, 0.1, space_size };

        int chance = randomChoice (2, std::vector<int>{ 70, 30 });

        if (chance == 1) {
            int anti_or_not = randomChoice (2, std::vector<int>{ 50, 50 });

            double height = 0.1, width = 0.1;

            double bonusYPos = (first + second) / 2;


            this->bonuses.push_back (Bonus (pylon_x_pos, bonusYPos, width,
            height, std::vector<double>{ 0.0, 0.0, 1.0 }, 1));
        }

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
    this->bonuses.clear ();
}

void Generator::draw () {
    for (Pylon obstacle : this->obstacles) {
        obstacle.draw ();
    }

    for (Bonus bonus : this->bonuses) {
        bonus.draw ();
    }
}

void Generator::shift_left_all (double pos) {
    for (int i = 0; i < this->obstacles.size (); ++i)
        obstacles[i].shift_left (pos);

    for (int i = 0; i < this->bonuses.size (); ++i)
        bonuses[i].shift_left (pos);
}


std::deque<Pylon> Generator::getObstacles () {
    return this->obstacles;
}


void Generator::setObstacle (int pos, Pylon& pylon) {
    this->obstacles[pos] = pylon;
}