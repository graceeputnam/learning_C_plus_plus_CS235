//  :-)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc,  char *argv[])
{
    ifstream infile(argv[1]);

    string line, max_line;
    int max = 0;

    while (getline(infile, line)){
        stringstream ss(line);
        string word;
        int count = 0;
        while (ss >> word)
        {
            count++;
        }
        if (count > max) {
            max = count;
            max_line = line;
        }
    }
    cout << max_line << endl;

    infile.close();
    return 0;
}