// :)
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <random>
#include <fstream>


using namespace std;


unordered_map<string, vector<string> > make_map(istream& in) {
    unordered_map<string, vector<string> > words;
    string prev = "";
    string curr;
    while (in >> curr) {
        words[prev].push_back(curr);
        prev = curr;
    }
    return words;
}


string get_random(vector<string>& words) {
    if (words.empty()) return "";
    int ind = rand() % words.size();
    return words[ind];
}


void generate_text(unordered_map<string, vector<string> > map, string start, int num, ostream& out) {
    string word = start;
    for (int i = 0; i < num; i++) {
        vector<string> word_bank = map[word];
        string string_picked = get_random(word_bank);
        out << string_picked <<  " ";
        word = string_picked;
    }
}


int main(int argc, char const* argv[]) {
    srand(time(nullptr));
    string filename = argv[1];
    int num  = stoi(argv[2]);

    // Adding the feature to allow the starting word to be a command line input
    string start = argv[3];
    ifstream input(filename);

    auto map = make_map(input);

    //Using the starting word given by the user as the start for generating text
    generate_text(map, start, num, cout);

    cout << endl;
    return 0;
}
