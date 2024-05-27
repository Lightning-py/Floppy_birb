#include "grid.hpp"


void Grid::setSquareSize (double size) {
    this->square_size = size;
}

void selectColor (int color) {
    // 0 - прозрачность
    // 1  - черный
    // 2 - оранжевый
    // 3 - красный
    // 4 - желтый
    // 5 - белый

    switch (color) {
    case 1: glColor3f (0.0, 0.0, 0.0); break;
    case 2: glColor3f (1.0, 0.54, 0.0); break;
    case 3: glColor3f (0.86, 0.078, 0.23); break;
    case 4: glColor3f (1.0, 1.0, 0.0); break;
    case 5: glColor3f (1.0, 1.0, 1.0); break;
    }
}

void Grid::drawInPosition (std::pair<double, double> pos) {
    glTranslated (pos.first - this->width * this->square_size / 2,
    pos.second - this->height * this->square_size / 2, 0.0);

    for (unsigned int width_i = 0; width_i < this->width; ++width_i) {
        for (unsigned int height_i = 0; height_i < this->height; ++height_i) {
            if (this->grid_data[height_i][width_i] != 0) {
                selectColor (this->grid_data[height_i][width_i]);
                glBegin (GL_QUADS);

                glVertex3f (width_i * this->square_size, height_i * this->square_size, 0);
                glVertex3f (width_i * this->square_size,
                (height_i + 1) * this->square_size, 0);
                glVertex3f ((width_i + 1) * this->square_size,
                (height_i + 1) * this->square_size, 0);
                glVertex3f ((width_i + 1) * this->square_size,
                height_i * this->square_size, 0);

                glEnd ();
            }
        }
    }
}

void Grid::loadGrid (std::string filename) {
    std::ifstream input;
    input.open (filename);

    input >> this->height >> this->width;


    if (!input.is_open ())
        throw "File read error";

    this->grid_data =
    std::vector<std::vector<int>> (this->height, std::vector<int> (this->width, 0));

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            input >> this->grid_data[i][j];

            if (this->grid_data[i][j] == 1) {
                this->grid_black.push_back (std::make_pair (i, j));
            }
        }
    }
}

double Grid::getSquareSize () {
    return this->square_size;
}

void Grid::setHeight (unsigned int height) {
    this->height = height;
}

void Grid::setWidth (unsigned int width) {
    this->width = width;
}

unsigned int Grid::getHeight () {
    return this->height;
}

unsigned int Grid::getWidth () {
    return this->width;
}

std::vector<std::pair<int, int>> Grid::get_grid_black () {
    return this->grid_black;
}


void Grid::setGridData (std::vector<std::vector<int>> grid_data) {
    this->grid_data = grid_data;
}
