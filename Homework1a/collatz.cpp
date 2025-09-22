#include <iostream>
#include <string>
// :D
using namespace std;

int main(int argc, char *argv[])
{
    if (argc <1) {
        cout << "prod requires 1 argument" << endl;
        return 1;
    }

    int start;
    start = stoi(argv[1]);

    cout << argv[1] << endl;

    while (start != 1) {
        if (start%2 == 0){
            start = start/2;
            cout << start << endl;
        }
        else {
            start = (start * 3) + 1;
            cout << start << endl;
        }
    }
    return 0;
}

// :)
