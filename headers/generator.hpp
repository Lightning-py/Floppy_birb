#ifndef GENERATOR_CLASS
#define GENERATOR_CLASS

#include <deque>

#include "bonus.hpp"
#include "pylon.hpp"

class Generator {
    private:
    std::deque<Pylon> obstacles; // структура с колоннами
    std::deque<Bonus> bonuses;   // структура с бонусами

    double default_space;


    public:
    Generator () {
    }

    Generator (double default_size) {
        this->default_space = default_size;
    }

    void generate_new_bonuses ();
    void generate_new_pylons (unsigned int pylons_overcame, double space_size); // генератор новых колонн
    void kill_unused_pylons (double left_x_pos); // устранение колонн, которые находятся за областью видимости
    void setObstacle (int pos, Pylon& pylon);
    void draw ();  // отрисовка
    void clear (); // очищение списка колонн
    void shift_left_all (double pos); // смещение всех колонн на некоторое значение
    std::deque<Pylon> getObstacles (); // метод для получение поля obstacles
    std::deque<Bonus> getBonuses (); // метод для получения списка бонусов
    void delete_bonus ();

    void make_space_size_bigger (double space_change);
    void make_space_size_smaller (double space_change, double bird_size);

    void set_default_space_size ();
};

#endif