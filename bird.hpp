#pragma once

#include <GL/glut.h>
#include <iostream>

class Bird {
    private:
    double x_pos;           // позиция по X
    double y_pos;           // позиция по Y
    double speed;           // скорость по Y
    double x_speed;         // скорость по X
    double fallingConstant; // константа g
    double rotation;        // угол поворота птицы
    double vertSpeed;       // скорость прыжка

    bool alive; // жива ли птица

    public:
    double x_hibox;  // координаты хитбокса по X
    double y_hitbox; // координаты хитбокса по Y

    double x_size;
    double y_size;

    int lives;

    Bird () { // конструктор по умолчанию
    }

    Bird (double x_pos, // конструктор
    double y_pos,
    double speed,
    double fallingConstant,
    double vertSpeed,
    double rotation,
    double x_speed,
    double x_hibox,
    double y_hitbox) {
        this->x_pos           = x_pos;
        this->y_pos           = y_pos;
        this->speed           = speed;
        this->fallingConstant = fallingConstant;
        this->alive           = true;
        this->vertSpeed       = vertSpeed;
        this->rotation        = rotation;
        this->x_speed         = x_speed;
        this->x_hibox         = x_hibox;
        this->y_hitbox        = y_hitbox;


        this->lives = 3;
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
};