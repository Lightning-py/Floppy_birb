#ifndef BIRD_CLASS
#define BIRD_CLASS


#include <GL/glut.h>
#include <iostream>

#include "grid.hpp"

class Bird {
    private:
    double x_pos;           // позиция по X
    double y_pos;           // позиция по Y
    double speed;           // скорость по Y
    double x_speed;         // скорость по X
    double fallingConstant; // константа g
    double rotation;        // угол поворота птицы
    double vertSpeed;       // скорость прыжка
    double default_size;


    bool alive; // жива ли птица

    public:
    int lives; // количество оставшихся жизней

    Grid grid;

    Bird () { // конструктор по умолчанию
    }

    Bird (double x_pos, // конструктор
    double y_pos,
    double speed,
    double fallingConstant,
    double vertSpeed,
    double rotation,
    double x_speed,
    Grid grid) {
        this->x_pos           = x_pos;
        this->y_pos           = y_pos;
        this->speed           = speed;
        this->fallingConstant = fallingConstant;
        this->alive           = true;
        this->vertSpeed       = vertSpeed;
        this->rotation        = rotation;
        this->x_speed         = x_speed;

        this->grid = grid;

        this->lives = 3;

        this->default_size = this->grid.getSquareSize ();
    }

    double getFallingConstant (); // получает константу g
    double getSpeed (); // возвращает текущую скорость птицы
    double getXSpeed (); // получение скорости птицы
    double getXPos ();   // получает позицию птички по X
    double getYPos ();   // получает позицию птички по Y

    void setFallingConstant (double fallingConstant); // задает константу g
    void setXPos (double x_pos); // задает позицию птички по X
    void setYPos (double y_pos); // задае позицию птички по Y
    void setSpeed (double speed); // задает текущую скорость птицы (применяется в прыжке)
    void setRotation (int rotation); // задает вращение

    void update (double tick_time); // обновляет координаты и скорость птицы
    void updateRotation (); // обновляет вращение птички (чтобы поворачивалась когда падает)

    void jump (); // птичка прыгает
    void kill (); // :(
    bool isAlive (); // возвращает состояние жизни птички

    void respawn ();

    void draw (); // отрисовка птички (изменить для изменения дизайна птицы)

    void make_bigger (double multiplier);
    void make_smaller (double multiplier);

    void make_x_speed_bigger (double multiplier);

    void set_default_size ();

    void heal ();

    double getSize ();
    double getDefaultSize ();
};

#endif
