#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Grid {
    double square_size;
    unsigned int width;
    unsigned int height;

    public:
    Grid () {
    }

    Grid (std::string filename, double square_size) {
        this->loadGrid (filename);
        this->setSquareSize (square_size);
    }

    std::vector<std::vector<int>> grid_data;
    std::vector<std::pair<int, int>> grid_black;

    void setSquareSize (double size);
    void setHeight (unsigned int height);
    void setWidth (unsigned int width);

    unsigned int getHeight ();
    unsigned int getWidth ();
    double getSquareSize ();

    void drawInPosition (std::pair<double, double> pos);
    void loadGrid (std::string filename);

    std::vector<std::pair<int, int>> get_grid_black ();
};