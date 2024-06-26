#ifndef MAP_CLASS
#define MAP_CLASS

#include <GL/glut.h>
#include <vector>

#include "bird.hpp"
#include "font.hpp"
#include "generator.hpp"


class Map {
    public:
    Bird bird;        // птица
    Generator gen;    // генератор
    size_t tick_time; // время тика
    bool stopped;     // остановлена ли игра
    long long stop_time; // время на которое была остановлена игра

    double space_size;

    Grid heart_grid;

    bool isNight;

    unsigned int overcame_pylons; // сколько колонн преодолели

    Font font;

    Map (Bird bird, Generator gen, size_t tick_time, Grid heart_grid, Font font) { // конструктор
        this->bird            = bird;
        this->gen             = gen;
        this->tick_time       = tick_time;
        this->stopped         = false;
        this->overcame_pylons = 0;
        this->space_size =
        this->bird.grid.getHeight () * this->bird.grid.getSquareSize () * 4.5;
        this->isNight    = false;
        this->heart_grid = heart_grid;
        this->font       = font;
    }

    void update ();        // обновление состояния игры
    void draw ();          // отрисовка игры
    void checkHitboxes (); // проверка столкновений

    void stop (long long stop_time); // остановка игры на количество тиков

    void setNight ();
    void setNightFalse ();

    void drawNight ();
    void drawHearts ();
    void drawPoints ();
};

#endif