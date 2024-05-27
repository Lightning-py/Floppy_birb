#ifndef FONT_CLASS
#define FONT_CLASS

#include <GL/glu.h>
#include <vector>

#include "grid.hpp"

class Font {
    private:
    std::vector<Grid> numbers;
    std::vector<Grid> letters;


    public:
    bool inverted;

    Font () {
    }

    Font (std::string filename) {
        this->load_numbers (filename);
        inverted = false;
    }


    void load_numbers (std::string filename);
    void load_letters (std::string filename);
    void print_letter (char letter, double x_pos, double y_pos, double size);
    void print_text (std::string text, double x_pos, double y_pos, double size);

    double get_size (std::string text, double size);
};

#endif