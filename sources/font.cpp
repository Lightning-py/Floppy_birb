#include "font.hpp"
#include "grid.hpp"

void Font::load_numbers (std::string filename) {
    std::ifstream input;
    input.open (filename);

    if (!input.is_open ())
        throw "File read error";

    for (int i = 0; i < 10; ++i) {
        Grid number_i;

        int height, width;

        input >> height >> width;


        number_i.setHeight (height);
        number_i.setWidth (width);

        std::vector<std::vector<int>> grid_data (height, std::vector<int> (width, 0));
        std::vector<std::vector<int>> grid_data_inverted (
        height, std::vector<int> (width, 0));

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                input >> grid_data[i][j];
            }
        }

        for (int i = 0; i < height; ++i) {
            grid_data_inverted[i] = grid_data[grid_data.size () - i - 1];
        }


        number_i.setGridData (grid_data_inverted);

        this->numbers.push_back (number_i);
    }
}

void Font::load_letters (std::string filename) {
    std::ifstream input;
    input.open (filename);

    if (!input.is_open ())
        throw "File read error";

    for (int i = 0; i < 26; ++i) {
        Grid number_i;

        int height, width;

        input >> height >> width;


        number_i.setHeight (height);
        number_i.setWidth (width);

        std::vector<std::vector<int>> grid_data (height, std::vector<int> (width, 0));

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                input >> grid_data[i][j];
            }
        }

        number_i.setGridData (grid_data);

        this->numbers.push_back (number_i);
    }
}

void Font::print_letter (char letter, double x_pos, double y_pos, double size) {
    if ((letter >= 48) && (letter <= 57)) {
        this->numbers[letter - 48].setSquareSize (
        size / this->numbers[letter - 48].getHeight ());
        // this->numbers[letter - 48].drawInPosition (std::make_pair (x_pos, y_pos));

        Grid letter_grid = this->numbers[letter - 48];

        glTranslated (x_pos - letter_grid.getWidth () * letter_grid.getSquareSize () / 2,
        y_pos - letter_grid.getHeight () * letter_grid.getSquareSize () / 2, 0.0);

        for (unsigned int width_i = 0; width_i < letter_grid.getWidth (); ++width_i) {
            for (unsigned int height_i = 0; height_i < letter_grid.getHeight (); ++height_i) {
                if (letter_grid.grid_data[height_i][width_i] != 0) {
                    if (inverted == false) {
                        glColor3f (0.0, 0.0, 0.0);
                    } else {
                        glColor3f (1.0, 1.0, 1.0);
                    }


                    glBegin (GL_QUADS);

                    glVertex3f (width_i * letter_grid.getSquareSize (),
                    height_i * letter_grid.getSquareSize (), 0);
                    glVertex3f (width_i * letter_grid.getSquareSize (),
                    (height_i + 1) * letter_grid.getSquareSize (), 0);
                    glVertex3f ((width_i + 1) * letter_grid.getSquareSize (),
                    (height_i + 1) * letter_grid.getSquareSize (), 0);
                    glVertex3f ((width_i + 1) * letter_grid.getSquareSize (),
                    height_i * letter_grid.getSquareSize (), 0);

                    glEnd ();
                }
            }
        }
    }
}

void Font::print_text (std::string text, double x_pos, double y_pos, double size) {


    for (size_t i = 0; i < text.size (); ++i) {
        if (text[i] != ' ') {
            glLoadIdentity ();
            this->print_letter (text[i], x_pos, y_pos, size);
        }
        x_pos += 0.001 + size / this->numbers[0].getHeight () * this->numbers[0].getWidth ();
    }
}

double Font::get_size (std::string text, double size) {
    double width = size / this->numbers[0].getHeight () * this->numbers[0].getWidth ();
    double interval = 0.01;

    return width * text.size () + (text.size () - 1) * interval;
}
