#pragma once

#include <deque>

#include "bonus.hpp"
#include "pylon.hpp"

class Generator {
    private:
    std::deque<Pylon> obstacles; // структура с колоннами
    std::deque<Bonus> bonuses;   // структура с бонусами


    public:
    Generator () { // конструктор по умолчанию
    }

    void generate_new_bonuses ();
    void generate_new_pylons (unsigned int pylons_overcame); // генератор новых колонн
    void kill_unused_pylons (double left_x_pos); // устранение колонн, которые находятся за областью видимости
    void setObstacle (int pos, Pylon& pylon);
    void draw ();  // отрисовка
    void clear (); // очищение списка колонн
    void shift_left_all (double pos); // смещение всех колонн на некоторое значение
    std::deque<Pylon> getObstacles (); // метод для получение поля obstacles
};