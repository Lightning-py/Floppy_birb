#include <cstdlib>
#include <vector>


int randInt (int lowerBound, int upperBound);
double randDouble (double lowerBound, double upperBound, int accuracy);
float randFloat (float lowerBound, float upperBound, int accuracy);
std::vector<double> randColord ();
std::vector<float> randColorf ();

int randomChoice (int number, std::vector<int> chances);