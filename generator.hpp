#pragma once

#include "pylon.hpp"
#include <deque>

class Generator {
    private:
    std::deque<Pylon> obstacles; // структура с колоннами


    public:
    Generator () { // конструктор по умолчанию
    }

    void generate_new_pylons (); // генератор новых колонн
    void kill_unused_pylons (double left_x_pos); // устранение колонн, которые находятся за областью видимости
    void draw ();                                // отрисовка
    void clear (); // очищение списка колонн
    void shift_left_all (double pos); // смещение всех колонн на некоторое значение
    std::deque<Pylon> getObstacles (); // метод для получение поля obstacles
};