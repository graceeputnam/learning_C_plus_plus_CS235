#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc,  char *argv[]){
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    string line;
    while (getline(infile, line)){
        stringstream ss(line);
        string first_name, last_name;
        int points;
        double factor;

        ss >> first_name >> last_name >> points >> factor;

        double result = points * factor;

        outfile << last_name << ", " << first_name << ": " << result << endl;

    }
    infile.close();
    outfile.close();

    return 0;
}