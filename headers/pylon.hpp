#ifndef PYLON_CLASS
#define PYLON_CLASS

#include <GL/glut.h>
#include <vector>


class Pylon { // класс препятствия (колонны)
    public:
    double x_pos;           // позиция колонны по x
    double y_first_height;  // высота нижней колонны
    double y_second_height; // высота верхней колонны
    double width;           // ширина колонны
    double space_size;

    bool overcome; // преодолен ли


    /*
        дальше идут вектора цвета вершин колонны вида (r, g, b)
        в процессе отрисовки вершины будут располагаться по часовой стрелке, первая вершина окажется в левом верхнем углу
    */
    std::vector<double> first_vertex_color; // цвет верхней левой вершины
    std::vector<double> second_vertex_color; // ...
    std::vector<double> third_vertex_color;  // ...
    std::vector<double> fourth_vertex_color; // цвет нижней левой вершины

    std::vector<double> fith_vertex_color; // цвет верхней левой вершины
    std::vector<double> sixth_vertex_color;   // ...
    std::vector<double> seventh_vertex_color; // ...
    std::vector<double> eighth_vertex_color; // цвет нижней левой вершины


    Pylon (double x_pos, double y_first_height, double y_second_height, double width, double space_size = 0.4) {
        this->x_pos           = x_pos;
        this->y_first_height  = y_first_height;
        this->y_second_height = y_second_height;
        this->width           = width;
        this->overcome        = false;
        this->space_size      = space_size;

        loadDefaultColor ();
    }

    bool isOvercome (); // метод для получение статуса преодоления колонны
    void setOvercome (); // обновление статуса преодоления колонны
    double getXPos (); // методя для получения поля x_pos
    void loadDefaultColor (); // загрузить изначальный цвет колонны
    void setOneColor (std::vector<double> color); // задать всем вершинам колонны один и тот же цвет

    void setRandomColors (); // задать рандомные цвета

    void setFourColors (std::vector<double>& first, // задать всем вершинам колонны разные цвета
    std::vector<double>& second,
    std::vector<double>& third,
    std::vector<double>& fourth);

    void setEightColors (std::vector<double>& first,
    std::vector<double>& second,
    std::vector<double>& third,
    std::vector<double>& fourth,
    std::vector<double>& fith,
    std::vector<double>& sixth,
    std::vector<double>& seventh,
    std::vector<double>& eighth);

    void draw (); // отрисовка конкретной колонны
    void shift_left (double pos); // смещение левее экземпляра колонны

    void make_space_bigger (double space_change);
    void make_space_smaller (double space_change, double bird_size);
    void set_default_space_size (double space_size);
};

#endif