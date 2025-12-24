#pragma once
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

template<class T>
class VectorSet {
public:
    bool contains(T item) const {
        // implement contains here
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == item){
                return true;
            }
        }
        // return true if item is in the set and false if not
        return false;
    }

    bool insert(T item) {
        // implement insert here
        if (!contains(item)) {
            v.push_back(item);
            return true;
        }
        // return true if item is inserted and false if item is already in the
        // set
        return false;
    }

    bool remove(T item)
    {
        // implement remove here
        for (int i = 0; i < v.size(); i++){
            if (v[i] == item){
                v.erase(v.begin() + i);
                return true;
            }
            // return true if item is removed and false if item wasn't in the se
        }
        return false ;
    }

    size_t size() const {
        // implement size here
        // return the number of items in the set
        return v.size();
    }

    bool empty() const {
        // implement empty here
        if (v.size() == 0){
            return true;
        }
        // return true if the set is empty and return false otherwise
        return false;
    }

    void clear() {
        // implement clear here
        v.clear();
        // remove all items from the set
    }

    void printSet() {
        cout << "The elements of the set are:" << endl;
        for (int i = 0; i < v.size(); i++){
            cout << v[i] << endl;
        }
        cout << endl;
    }

private:
    vector<T> v;
};
