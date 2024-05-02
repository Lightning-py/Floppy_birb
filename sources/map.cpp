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

    gen.generate_new_pylons (this->overcame_pylons);
}


void Map::draw () {
    gen.draw ();

    glLoadIdentity ();
    bird.draw ();
}


void Map::checkHitboxes () {
    double bird_pos_right = this->bird.getXPos () + this->bird.x_hibox;
    double bird_pos_left  = this->bird.getXPos () - this->bird.x_hibox;


    double bird_pos_top    = this->bird.getYPos () + this->bird.y_hitbox;
    double bird_pos_bottom = this->bird.getYPos () - this->bird.y_hitbox;

    if ((bird_pos_bottom <= -1 || bird_pos_top >= 1)) {
        this->bird.kill ();

        if (this->bird.lives > 0) {
            this->bird.respawn ();
            this->gen.clear ();
            this->gen.generate_new_pylons (this->overcame_pylons);

            this->stop (69);
        }

        return;
    }

    for (int i = 0; i < this->gen.getObstacles ().size (); ++i) {
        Pylon obstacle = gen.getObstacles ()[i];

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
                gen.setObstacle (i, obstacle);

                this->overcame_pylons++;
            }
        }

        if (((bird_pos_right >= pylon_pos_left && bird_pos_right <= pylon_pos_right) ||
            (bird_pos_left >= pylon_pos_left && bird_pos_left <= pylon_pos_right)) &&
        (bird_pos_bottom <= pylon_bottom_top || bird_pos_top >= pylon_top_bottom)) { // проверка на наложение хитбоксов на колонну
            this->bird.kill ();

            if (this->bird.lives > 0) {
                this->bird.respawn ();
                this->gen.clear ();
                this->gen.generate_new_pylons (this->overcame_pylons);

                this->stop (69);
            }

            return;
        }
    }
}
