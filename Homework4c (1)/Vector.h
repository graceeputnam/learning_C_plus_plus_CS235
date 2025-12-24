#pragma once

#include <iostream>
#include <string>
const int INITIAL_CAPACITY = 10;

template<class T>
class Vector {
public:
    Vector() {
        m_capacity = INITIAL_CAPACITY;
        m_size = 0;
        m_data = new T[m_capacity];
    }

    ~Vector() {
        clear();
        delete[] m_data;
    }

    void grow() {
        size_t newSize = m_capacity * 2;
        T * newArray = new T[newSize];
        for (size_t i = 0; i < m_size; i++) {
            newArray[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newArray;
        m_capacity = newSize;
    }

    void push_back(T const& item) {
        // implement push_back here
        if (m_size < m_capacity) {
            m_data[m_size++] = item;
        }
        else {
            grow();
            m_data[m_size++] = item;
        }

    }
    
    void pop_back() {
        // implement pop_back here
        m_size--;
    }

    void insert(T const& item, size_t position) {
        // implement insert here
        if (position > m_size) {
            throw std::out_of_range("Insert position ouf of bounds");
        }
        if (m_size >= m_capacity) {
            grow();
        }
        for (size_t i = m_size; i > position; i--) {
            m_data[i] = m_data[i - 1];
        }
        m_data[position] = item;
        m_size++;
    }

    void remove(size_t position) {
        // implement remove here
        if (position < 0 || position >= m_size) {
            throw std::out_of_range("Remove position out of bounds");
        }
        for (size_t i = position; i < m_size; i++) {
            m_data[i] = m_data[i + 1];
        }
        m_size--;
    }

    T& operator[](size_t index) {
        // implement operator[] here
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Your index is out of bounds");
        }
        return m_data[index];
    }

    T& at(size_t index) {
        // implement at here
        if (index >= m_size) {
            throw std::out_of_range("Your index is out of bounds");
        }
        return m_data[index];
    }

    size_t size() const {
        // implement size here
        return m_size;
    }

    void clear() {
        // implement clear here
        m_size = 0;
    }

private:
    T * m_data;
    size_t m_capacity;
    size_t m_size;


};
