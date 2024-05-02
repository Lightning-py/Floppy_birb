#include <cstdlib>
#include <vector>

int randInt (int lowerBound, int upperBound) {
    return lowerBound + (rand () % (upperBound - lowerBound));
}

double randDouble (double lowerBound, double upperBound, int accuracy) {
    int part = randInt (0, accuracy);

    return lowerBound + (upperBound - lowerBound) / ((double)accuracy) * part;
}

float randFloat (float lowerBound, float upperBound, int accuracy) {
    int part = randInt (0, accuracy);

    return lowerBound + (upperBound - lowerBound) / ((float)accuracy) * part;
}


std::vector<double> randColord () {
    std::vector<double> result = { randDouble (0.0, 1.0, 100),
        randDouble (0.0, 1.0, 100), randDouble (0.0, 1.0, 100) };
    return result;
}

std::vector<float> randColorf () {
    std::vector<float> result = { randFloat (0.0, 1.0, 100),
        randFloat (0.0, 1.0, 100), randFloat (0.0, 1.0, 100) };
    return result;
}