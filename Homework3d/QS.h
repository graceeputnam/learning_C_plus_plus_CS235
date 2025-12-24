#pragma once

#include <vector>
#include <algorithm>

template <class T>
int median_of_three(std::vector<T>& table, int first, int last) {
    int middle = (first + last) / 2;
    if (table[first] > table[middle])
        std::swap(table[first], table[middle]);
    if (table[last] < table[middle])
        std::swap(table[last], table[middle]);
    if (table[middle] < table[first])
        std::swap(table[middle], table[first]);
    std::swap(table[first], table[middle]);
    return first;
}

template <class T>
int partition(std::vector<T>& table, int first, int last, int pivotIndex) {
    std::swap(table[first], table[pivotIndex]);
    int up = first + 1;
    int down = last;
    do {
        while (up <= last && table[up] <= table[first]) up++;
        while (down > first && table[down] > table[first]) down--;
        if (up < down) std::swap(table[up], table[down]);
    } while (up < down);

    std::swap(table[first], table[down]);
    return down;
}

template <class T>
void sort_helper(std::vector<T>& array, int first, int last) {
    if (first >= last) return;
    int pivotIndex = median_of_three(array, first, last);
    int split = partition(array, first, last, pivotIndex);
    sort_helper(array, first, split - 1);
    sort_helper(array, split + 1, last);
}

template <class T>
void sort(std::vector<T>& array) {
    if (array.size() > 1)
        sort_helper(array, 0, array.size() - 1);
}
