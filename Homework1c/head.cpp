#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void only_file(string filename, int num){
    ifstream input_file(filename);
    if (!input_file){
        cout << "File does not exist" << endl;
        return;
    }
    int iteration_count = 0;
    int max = num;
    while (iteration_count < max && input_file.eof() == false) {
        string line;
        getline(input_file, line);
        cout << line << endl;
        iteration_count++;
    }
    input_file.close();
}

void only_num(int number){
    for (int i=0; i< number; i++){
        string input;
        cin >> input;
        cout << input << endl;
    }
}


int main(int argc, char const* argv[]) {
    // Write your code here
    if (argc == 1){
        only_num(10);
    }

    if (argc ==2 &&  argv[1][0] != '-' ) {
        only_file(argv[1], 10);
    }

    if (argc ==2 &&  argv[1][0] == '-'){
        string arg1 = argv[1];
        only_num(stoi(arg1.substr(1)));
    }

    if (argc ==3){
        string arg1 = argv[1];
        only_file(argv[2], stoi(arg1.substr(1)));
    }

    return 0;
}

