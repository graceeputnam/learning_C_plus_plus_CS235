#include <iostream>
#include <string>
// :D
using namespace std;

int main(int argc, char *argv[])
{
    if (argc <4) {
        cout << "prod requires 3 arguments" << endl;
        return 1;
    }

        int start, end, divisor;
        start = stoi(argv[1]);
        end = stoi(argv[2]);
        divisor = stoi(argv[3]);


        if (start < end){
            for (int i = start; i <= end; i++)
            {
                if (i%divisor == 0) {
                    cout << i << endl;
                }
            }
        }
        if (start >= end) {
            for (int i = start; i >= end; i--)
            {
                if (i%divisor == 0) {
                    cout << i << endl;
                }
            }

        }
    return 0;
    }

