#pragma once

#include <vector>
#include <iostream>
using namespace std;

template <class T>
void sort(std::vector<T> &array)
{
    for (size_t i = 1; i < array.size(); ++i) {
        T key = array[i];
        size_t j = i;
        while (j > 0 && array[j - 1] > key) {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = key;
    }
    for (size_t i = 0; i < array.size(); ++i){
        cout << array[i] << " ";
        }
    cout << std::endl;
    }