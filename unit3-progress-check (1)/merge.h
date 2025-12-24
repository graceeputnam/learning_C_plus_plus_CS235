#pragma once

#include <vector>
template <typename T>
void merge(std::vector<T>& data, int start, int mid, int end) {
    std::vector<T> left(data.begin() + start, data.begin() + mid);
    std::vector<T> right(data.begin() + mid, data.begin() + end);
    int i = 0, j = 0, k = start;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j])
            data[k++] = left[i++];
        else
            data[k++] = right[j++];
    }
    while (i < left.size()) data[k++] = left[i++];
    while (j < right.size()) data[k++] = right[j++];
}

template <typename T>
void mergeSortHelper(std::vector<T>& data, int start, int end) {
    if (end - start <= 1) return;
    int mid = (start + end) / 2;
    mergeSortHelper(data, start, mid);
    mergeSortHelper(data, mid, end);
    merge(data, start, mid, end);
}

template <typename T>
void sort(std::vector<T>& data) {
    mergeSortHelper(data, 0, data.size());
}

