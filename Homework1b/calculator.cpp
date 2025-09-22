//  :)
#include <iostream>
#include <string>
#include <cmath>
// :D
using namespace std;

double apply_calculation(string operation, double left, double right) {
    if (operation == "add"){
        return left + right;
    }
    else if (operation == "subtract"){
        return left - right;
    }
    else if (operation == "multiply"){
        return left * right;
    }
    else if (operation == "divide"){
        return left / right;
    }
    else if (operation == "mod"){
        return fmod(left, right);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    string operation;

    while (true)
    {

        cout << "operation: ";
        getline(cin, operation);

        if (operation.empty()){
            break;
        }

        if (operation != "add" && operation != "subtract" && operation != "multiply"
            && operation != "divide" && operation != "mod"){
            cout << operation << " isn't a valid operation" << endl;
            continue;
            }
        string left, right;
        double left_operand, right_operand;

        cout << "left operand: ";
        getline(cin, left);
        left_operand = stod(left);

        cout << "right operand: ";
        getline(cin, right);
        right_operand = stod(right);

       cout << apply_calculation(operation, left_operand, right_operand) << endl;
    }
    return 0;
}
// :)
