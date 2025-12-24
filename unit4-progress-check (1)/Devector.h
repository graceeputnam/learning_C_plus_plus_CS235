
#pragma once

# include  <fstream>

template <class T>
class Devector
{

private:
    T* buffer = nullptr;
    size_t buffer_capacity = 0;
    size_t buffer_size = 0;
    size_t buffer_front = 0;

public:
    Devector() {
        buffer_capacity = 10;
        buffer = new T[buffer_capacity];
        buffer_size = 0;
        buffer_front = 0;
    }

    ~Devector()
    {
        delete[] buffer;
    }

    void push_back(T const &item)
    {
        if (buffer_size == buffer_capacity)
        {
            size_t new_capacity = buffer_capacity * 2;
            T* new_buffer = new T[new_capacity];
            for (size_t i = 0; i < buffer_size; i++)
            {
                new_buffer[i] = buffer[(buffer_front + i) % buffer_capacity];
            }
            delete[] buffer;
            buffer = new_buffer;
            buffer_capacity = new_capacity;
            buffer_front = 0;
        }
        size_t pos = (buffer_front + buffer_size) % buffer_capacity;
        buffer[pos] = item;
        buffer_size++;
    }

    void pop_back()
    {
        if (buffer_size == 0)
        {
            return;
        }
        buffer_size--;
    }

    void push_front(T const &item)
    {
        if (buffer_size == buffer_capacity) {
            size_t new_capacity = buffer_capacity * 2;
            T* new_buffer = new T[new_capacity];
            for (size_t i = 0; i < buffer_size; i++)
            {
                new_buffer[i] = buffer[(buffer_front + i) % buffer_capacity];
            }
            delete[] buffer;
            buffer = new_buffer;
            buffer_capacity = new_capacity;
            buffer_front = 0;
        }
        buffer_front = (buffer_front + buffer_capacity - 1) % buffer_capacity;
        buffer[buffer_front] = item;
        buffer_size++;
    }

    void pop_front()
    {
        if (buffer_size == 0)
        {
            return;
        }
        buffer_front = (buffer_front + 1) % buffer_capacity;
        buffer_size--;
    }

    T &operator[](size_t index)
    {
        return buffer[(buffer_front + index) % buffer_capacity];
    }

    T& at(size_t index)
    {
        if (index >= buffer_size)
        {
            throw std::out_of_range("index out of range");
        }
        return buffer[(buffer_front + index) % buffer_capacity];
    }

    size_t size() const
    {
        return buffer_size;
    }

    void clear()
    {
        buffer_size = 0;
        buffer_front = 0;
    }
};
