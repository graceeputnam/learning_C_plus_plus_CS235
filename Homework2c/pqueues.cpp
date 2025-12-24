#include <iostream>
#include <string>
#include <queue>
`
using namespace std;


void add_name(priority_queue<pair<int, string>>& pq) {
    string name;
    int priority;

    cout << "Name: ";
    getline(cin, name);

    string priority_str;
    cout << "Priority: ";
    getline(cin, priority_str);
    priority = stoi(priority_str);

    pq.push({priority, name});
}


void take_name(priority_queue<pair<int, string>>& pq) {
    if (pq.empty()) {
        cout << "There are no more people in line";
        return;
    }
    auto person = pq.top();
    int number = person.first;
    string person_name = person.second;
    if (number >= 0 && number < 10) {
        string num;
        num = to_string(number);
        num = "0" + num;
        cout << num << " - " << person_name << endl;
    }
    else {
       cout <<  to_string(number) << " - " << person_name << endl;
    }
    pq.pop();
}


int main(int argc, char const* argv[]) {
    priority_queue<::pair<int, string>> pq;
    while (true) {
        string operation;
        cout << "What do you want to do? ";
        getline(cin, operation);
        if (operation.empty()) {
            break;
        }
        if (operation == "add") {
            add_name(pq);
        }
        else {
            take_name(pq);
        }
    }
    return 0;
}

