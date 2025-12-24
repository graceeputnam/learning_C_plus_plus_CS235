#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void get_unique(string file){
    ifstream inputfile(file);
    string line;
    vector<string> v;
    while (getline(inputfile, line)) {
        if (find(v.begin(), v.end(), line) == v.end()) {
            v.push_back(line);
        }
    }
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }}

void unique_input(){
    string line;
    set<string> s;
    while (true){
        getline(cin, line);
        if (line.empty()){
            break;
        }
        if (s.find(line) == s.end()){
            cout << line << endl;
            s.insert(line);
        }
        s.insert(line);
    }
}

int main(int argc, char const* argv[]) {
    // Write your code here
    if (argc == 2) {
        string file = argv[1];
        get_unique(file);
    }
    else {
        unique_input();
    }
    return 0;
}
