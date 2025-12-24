// :)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

float search_and_average(string filename, string state, string year){
    ifstream file(filename);
    if (!file){
       cout << "ERROR: could not open file " << endl;
        exit(0);
    }
    float total = 0;
    float instances = 0;
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        string word;
        vector <string> words;
        while (ss >> word){
            words.push_back(word);
        }
        if (words[0]==state && words[1]==year){
            instances++;
            total += stof(words[3]);
        }
    }
    return total/instances;
}


int main(int argc, char *argv[]){
    string filename;
    string state;
    string year;

    filename = argv[1];
    state = argv[2];
    year = argv[3];

    cout << search_and_average(filename, state, year)<< endl;
    return 0;
}

//unemployment.txt` contains information about the unemployment rates for states for approximately the last 50 years.
//Each row contains (in the following order) the name of the state, the year, the month and the unemployment rate.


//Your task is to write a command line utility that allows someone to see what the average unemployment rate is for a given state, and year.
//It may be assumed that the tests will always provide 3 arguments and provide valid input for the state, and year.
