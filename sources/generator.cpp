#include <algorithm>
#include <iostream>
#include <vector>

#include "generator.hpp"
#include "randomUtils.hpp"

std::vector<double> chooseColor (int bonus_type) {
    switch (bonus_type) {
    case 1: return std::vector<double>{ 1.0, 0.0, 0.0 }; break;
    case 2: return std::vector<double>{ 0.0, 1.0, 0.0 }; break;
    case 3: return std::vector<double>{ 0.0, 0.0, 1.0 }; break;
    case 4: return std::vector<double>{ 1.0, 1.0, 0.0 }; break;
    case 5: return std::vector<double>{ 0.0, 1.0, 1.0 }; break;
    case 6: return std::vector<double>{ 1.0, 0.0, 1.0 }; break;
    case 7: return std::vector<double>{ 0.5, 0.5, 0.5 }; break;
    case 8: return std::vector<double>{ 0.0, 0.0, 0.0 }; break;
    case 9: return std::vector<double>{ 0.5, 0.0, 0.5 }; break;
    default: break;
    }
}

void Generator::generate_new_pylons (unsigned int pylons_overcame, double space_size) {
    double x_start_pos = 0.7;
    double interval    = 0.6;

    if (this->obstacles.size () > 0) {
        x_start_pos = this->obstacles.back ().getXPos () + interval;
    }

    int pylons_to_gen = 20 - this->obstacles.size ();

    for (int i = 0; i < pylons_to_gen; ++i) {
        double pylon_x_pos = x_start_pos + i * interval;

        // double space_size =
        // 0.6; // пока что так, потом можно изменять в зависимости от количества пройденных препятствий

        double first  = randDouble (space_size - 1, 1 - space_size, 100);
        double second = 0.0;

        if (first + space_size >= 1.8) {
            second = first - space_size;
            std::swap (first, second);
        } else
            second = first + space_size;

        Pylon obstacle{ pylon_x_pos, first, second, 0.1, space_size };

        // int chance = randomChoice (2, std::vector<int>{ 70, 30 });
        int chance = 1; // для тестирования

        if (chance == 1) {
            int bonus_type = randInt (0, 10);

            double height = 0.1, width = 0.1;

            double bonusYPos = (first + second) / 2;


            this->bonuses.push_back (Bonus (pylon_x_pos, bonusYPos, width,
            height, chooseColor (bonus_type), bonus_type));
        }

        obstacle.loadDefaultColor ();
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


std::deque<Bonus> Generator::getBonuses () {
    return this->bonuses;
}


void Generator::delete_bonus () {
    this->bonuses.pop_front ();
}


void Generator::make_space_size_bigger (double space_change) {
    for (int i = 0; i < this->getObstacles ().size (); ++i) {
        Pylon obstacle = this->obstacles[i];

        obstacle.make_space_bigger (space_change);

        this->obstacles[i] = obstacle;
    }
}


void Generator::make_space_size_smaller (double space_change, double bird_size) {
    for (int i = 0; i < this->getObstacles ().size (); ++i) {
        Pylon obstacle = this->obstacles[i];

        obstacle.make_space_smaller (space_change, bird_size);

        this->obstacles[i] = obstacle;
    }
}


void Generator::set_default_space_size () {
    for (int i = 0; i < this->getObstacles ().size (); ++i) {
        Pylon obstacle = this->obstacles[i];

        obstacle.set_default_space_size (this->default_space);

        this->obstacles[i] = obstacle;
    }
}
