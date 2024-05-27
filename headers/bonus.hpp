#ifndef BONUS_CLASS
#define BONUS_CLASS


#include <GL/glut.h>
#include <vector>

class Bonus { // класс бонуса
    private:
    double x_pos;  // позиция центра бонуса по x
    double y_pos;  // позиция центра бонуса по y
    double width;  // ширина бонуса
    double height; // высота бонуса

    unsigned int bonus_type;


    std::vector<double> color;

    std::pair<double, double> left_bottom_pos;
    std::pair<double, double> left_top_pos;
    std::pair<double, double> right_top_pos;
    std::pair<double, double> right_bottom_pos;

    public:
    Bonus (double x_pos, double y_pos, double width, double height, std::vector<double> color, unsigned int bonus_type) {
        this->x_pos  = x_pos;
        this->y_pos  = y_pos;
        this->width  = width;
        this->height = height;


        this->color = color;

        this->left_bottom_pos = std::make_pair (x_pos - width / 2, y_pos - height / 2);
        this->left_top_pos = std::make_pair (x_pos - width / 2, y_pos + height / 2);
        this->right_top_pos = std::make_pair (x_pos + width / 2, y_pos + height / 2);
        this->right_bottom_pos = std::make_pair (x_pos + width / 2, y_pos - height / 2);

        this->bonus_type = bonus_type;
    }

    void draw ();
    unsigned int getBonusType ();
    void shift_left (double pos);
    double getXPos ();
    double getYPos ();
    double getWidth ();
    double getHeight ();
};


#endif
