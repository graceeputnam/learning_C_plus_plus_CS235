#include <iostream>
#include <cstdlib> // atof
#include <string>
using std::abs;  

const double EPSILON = 0.0001;

int main(int argc, char *argv[]){

    if (argc <2) {
        std::cout << "requires 1 argument" << std::endl;
        return 1;
    }

    if (std::stoi(argv[1]) < 0) {
        std::cout << "Input must be greater than 0" << std::endl;
        return 1;
    }

    double input = std::stod(argv[1]);
    double lower = 0.0;
    double upper = input;
    double value = (lower + upper) / 2.0;

    while (abs(value * value - input) >= EPSILON){
        std::cout << value << " (" << value * value << ")" << std::endl;

        if (value * value > input){
            upper = value;
        }
        else{
            lower = value;
        }
        value = (lower + upper) / 2.0;
    }

    std::cout << value << " (" << value * value << ")" << std::endl;

    return 0;
}
// :)
