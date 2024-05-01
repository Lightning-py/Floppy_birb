#pragma once

#include <GL/glut.h>
#include <vector>

#include "bird.hpp"
#include "generator.hpp"


class Map {
    public:
    Bird bird;        // птица
    Generator gen;    // генератор
    size_t tick_time; // время тика
    bool stopped;     // остановлена ли игра
    long long stop_time; // время на которое была остановлена игра

    unsigned int overcame_pylons; // сколько колонн преодолели

    Map (Bird bird, Generator gen, size_t tick_time) { // конструктор
        this->bird            = bird;
        this->gen             = gen;
        this->tick_time       = tick_time;
        this->stopped         = false;
        this->overcame_pylons = 0;
    }

    void update ();        // обновление состояния игры
    void draw ();          // отрисовка игры
    void checkHitboxes (); // проверка столкновений

    void stop (long long stop_time); // остановка игры на количество тиков
};