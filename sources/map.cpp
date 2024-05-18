#include <cmath>

#include "map.hpp"


void Map::stop (long long stop_time) { // приостановить игру на некоторое время
    this->stopped   = true;
    this->stop_time = stop_time;
}


void Map::update () {
    if (this->stopped) // игра остановлена
    {

        this->stop_time--;
        if (this->stop_time <= 0)
            this->stopped = false;

        return;
    }

    bird.update (tick_time);
    gen.kill_unused_pylons (bird.getXPos () - 1.2);
    gen.shift_left_all (tick_time * this->bird.getXSpeed () / 1000);

    checkHitboxes ();

    gen.generate_new_pylons (this->overcame_pylons, this->space_size);
}


void Map::draw () {
    gen.draw ();


    glLoadIdentity ();
    bird.draw ();

    glLoadIdentity ();
    if (this->isNight)
        drawNight ();
}


bool is_dot_in_square (double x_1,
double y_1,
std::pair<std::pair<double, double>, std::pair<double, double>> square) {
    return ((x_1 >= square.first.first) && (x_1 <= square.second.first)) &&
    ((y_1 >= square.first.second) && (y_1 <= square.second.second));
}


void Map::checkHitboxes () {
    double bird_pos_top = this->bird.getYPos () +
    this->bird.grid.getHeight () * this->bird.grid.getSquareSize () / 2;
    double bird_pos_bottom = this->bird.getYPos () -
    this->bird.grid.getHeight () * this->bird.grid.getSquareSize () / 2;
    double bird_pos_right = this->bird.getXPos () +
    this->bird.grid.getWidth () * this->bird.grid.getSquareSize () / 2;
    double bird_pos_left = this->bird.getXPos () -
    this->bird.grid.getWidth () * this->bird.grid.getSquareSize () / 2;

    double bird_x_pos = this->bird.getXPos ();
    double bird_y_pos = this->bird.getYPos ();

    double square_left_angle_x =
    bird_x_pos - this->bird.grid.getWidth () * this->bird.grid.getSquareSize () / 2;
    double square_left_angle_y =
    bird_y_pos - this->bird.grid.getHeight () * this->bird.grid.getSquareSize () / 2;

    if ((bird_pos_bottom <= -1 || bird_pos_top >= 1)) {
        this->bird.kill ();

        if (this->bird.lives > 0) {
            this->bird.respawn ();
            this->gen.clear ();
            this->gen.generate_new_pylons (this->overcame_pylons, this->space_size);

            this->stop (69);
        }

        return;
    }

    // проверка на столкновение с бонусами
    for (int i_ = 0; i_ < this->gen.getBonuses ().size (); ++i_) {
        Bonus bonus = this->gen.getBonuses ()[i_];

        double bonus_bottom_left_angle_x = bonus.getXPos () - bonus.getWidth () / 2;
        double bonus_bottom_left_angle_y = bonus.getYPos () - bonus.getHeight () / 2;

        double bonus_top_right_angle_x = bonus.getXPos () + bonus.getWidth () / 2;
        double bonus_top_right_angle_y = bonus.getYPos () + bonus.getHeight () / 2;

        if (!((bonus_top_right_angle_x < bird_pos_left) ||
            (bonus_bottom_left_angle_x > bird_pos_right))) {
            for (auto pair : this->bird.grid.get_grid_black ()) {
                int i = pair.first;
                int j = pair.second;


                bool flag = false;


                double center_dot_x =
                square_left_angle_x + (j + 0.5) * this->bird.grid.getSquareSize ();

                double center_dot_y =
                square_left_angle_y + (i + 0.5) * this->bird.grid.getSquareSize ();

                flag = flag |
                is_dot_in_square (center_dot_x, center_dot_y,
                std::make_pair (std::make_pair (bonus_bottom_left_angle_x, bonus_bottom_left_angle_y),
                std::make_pair (bonus_top_right_angle_x, bonus_top_right_angle_y)));

                if (flag) {
                    // использование бонуса


                    switch (bonus.getBonusType ()) {
                    case 1: this->bird.heal (); break;
                    case 2:
                        this->gen.make_space_size_bigger (this->bird.getSize () * 0.5);
                        break;
                    case 3: this->bird.make_smaller (1.2); break;
                    case 4:
                        this->gen.set_default_space_size ();
                        this->bird.set_default_size ();
                        break;
                    case 5: this->bird.make_bigger (1.2); break;
                    case 6: this->setNightFalse (); break;
                    case 7:
                        this->gen.make_space_size_smaller (
                        this->bird.getSize () * 0.5, this->bird.getSize ());
                        break;
                    case 8: this->bird.make_x_speed_bigger (1.2);
                    case 9: this->setNight (); break;

                    default: break;
                    }
                    // применение эффектов бонуса
                    this->gen.delete_bonus ();
                    break;
                }


                // удаление бонуса
            }
        }
    }

    // проверка на столкновение с колоннами
    for (int i_ = 0; i_ < this->gen.getObstacles ().size (); ++i_) {
        Pylon obstacle = gen.getObstacles ()[i_];

        double pylon_pos_center_x = obstacle.getXPos ();

        double pylon_pos_left  = pylon_pos_center_x - obstacle.width / 2;
        double pylon_pos_right = pylon_pos_center_x + obstacle.width / 2;

        double pylon_bottom_bottom = -1;
        double pylon_bottom_top    = obstacle.y_first_height;

        double pylon_top_bottom = obstacle.y_second_height;
        double pylon_top_top    = 1;


        if (!obstacle.isOvercome ()) { // если еще не преодолевали эту колонну
            if (pylon_pos_center_x <= 0) { // если преодолели ее сейчас
                obstacle.setOvercome ();
                gen.setObstacle (i_, obstacle);

                this->overcame_pylons++;
            }
        }

        // лЕгАсИ
        // if (((bird_pos_right >= pylon_pos_left && bird_pos_right <= pylon_pos_right) ||
        //     (bird_pos_left >= pylon_pos_left && bird_pos_left <= pylon_pos_right)) &&
        // (bird_pos_bottom <= pylon_bottom_top || bird_pos_top >= pylon_top_bottom)) { // проверка на наложение хитбоксов на колонну
        //     this->bird.kill ();

        //     if (this->bird.lives > 0) {
        //         this->bird.respawn ();
        //         this->gen.clear ();
        //         this->gen.generate_new_pylons (this->overcame_pylons);

        //         this->stop (69);
        //     }

        //     return;
        // }

        if (!((pylon_pos_right < bird_pos_left) || (pylon_pos_left > bird_pos_right))) {
            for (auto pair : this->bird.grid.get_grid_black ()) {
                int i = pair.first;
                int j = pair.second;

                bool flag = false;


                double center_dot_x =
                square_left_angle_x + (j + 0.5) * this->bird.grid.getSquareSize ();
                double center_dot_y =
                square_left_angle_y + (i + 0.5) * this->bird.grid.getSquareSize ();

                // std::cout << this->bird.getXPos () << " "
                //           << this->bird.getYPos () << " " << center_dot_x
                //           << " " << center_dot_y << std::endl;

                flag = flag |
                is_dot_in_square (center_dot_x, center_dot_y,
                std::make_pair (std::make_pair (pylon_pos_left, pylon_bottom_bottom),
                std::make_pair (pylon_pos_right, pylon_bottom_top)));


                flag = flag |
                is_dot_in_square (center_dot_x, center_dot_y,
                std::make_pair (std::make_pair (pylon_pos_left, pylon_top_bottom),
                std::make_pair (pylon_pos_right, pylon_top_top)));

                if (flag) {
                    this->bird.kill ();

                    this->setNightFalse ();
                    this->gen.set_default_space_size ();
                    this->bird.set_default_size ();

                    if (this->bird.lives > 0) {
                        this->bird.respawn ();


                        this->gen.clear ();
                        this->gen.generate_new_pylons (
                        this->overcame_pylons, this->space_size);

                        this->stop (69);
                    }

                    return;
                }
            }
        }
    }
}


void Map::setNight () {
    this->isNight = true;
}

void Map::setNightFalse () {
    this->isNight = false;
}

void Map::drawNight () {

    glColor3f (0.0, 0.0, 0.0);

    // glVertex3f (-1.0, 0.0, 0.0);
    // glVertex3f (-1.0, 1.0, 0.0);
    // glVertex3f (1.0, 1.0, 0.0);
    // glVertex3f (1.0, 0.0, 0.0);

    // полукруг

    double theta;
    double pi   = 3.14;
    double step = 0.5f;

    double radius = this->bird.getSize () * 4.5;


    for (GLfloat a = -45.0f; a < 45.0f; a += step) {
        glBegin (GL_POLYGON);

        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (1.0, radius * sin (theta), 0.0);
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);

        a += step;
        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);
        glVertex3f (1.0, radius * sin (theta), 0.0);

        glEnd ();
    }

    for (GLfloat a = -45.0f + step; a < 45.0f; a += step) {
        glBegin (GL_POLYGON);

        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (1.0, radius * sin (theta), 0.0);
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);

        a += step;
        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);
        glVertex3f (1.0, radius * sin (theta), 0.0);

        glEnd ();
    }
    // glVertex3f (-1.0, 0.0, 0.0);
    for (GLfloat a = 45.0f; a < 135.0f; a += step) {
        glBegin (GL_POLYGON);

        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (-1.0, radius * sin (theta), 0.0);
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);

        a += step;
        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);
        glVertex3f (-1.0, radius * sin (theta), 0.0);

        glEnd ();
    }

    for (GLfloat a = 45.0f + step; a < 135.0f; a += step) {
        glBegin (GL_POLYGON);

        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (-1.0, radius * sin (theta), 0.0);
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);

        a += step;
        theta = -2.0f * pi * a / 180.0f;
        glVertex3f (radius * cos (theta), radius * sin (theta), 0.0f);
        glVertex3f (-1.0, radius * sin (theta), 0.0);

        glEnd ();
    }

    glBegin (GL_QUADS);

    glVertex3f (-1.0, radius, 0.0);
    glVertex3f (-1.0, 1.0, 0.0);
    glVertex3f (1.0, 1.0, 0.0);
    glVertex3f (1.0, radius, 0.0);

    glEnd ();

    glBegin (GL_QUADS);

    glVertex3f (-1.0, -radius, 0.0);
    glVertex3f (-1.0, -1.0, 0.0);
    glVertex3f (1.0, -1.0, 0.0);
    glVertex3f (1.0, -radius, 0.0);

    glEnd ();
}
