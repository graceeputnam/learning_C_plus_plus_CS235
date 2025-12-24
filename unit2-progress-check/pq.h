#include <cstddef>
#include <vector>


using namespace std;


template <class T>
class PQ {

    private:
    vector<T> data;

    public:

    void push(T const& item) {
        data.push_back(item);
    }

    void pop() {
        T max_value = data[0];
        int max_index = 0;
        for (int i = 1; i < data.size(); ++i) {
            if (data[i] > max_value) {
                max_value = data[i];
                max_index = i;
            }
        }
        data.erase(data.begin() + max_index);
    }

    size_t size() const {
        return data.size();
    }

    T top() const {
        T max_value = data[0];
        int max_index = 0;
        for (int i = 1; i < data.size(); ++i) {
            if (data[i] > max_value) {
                max_value = data[i];
                max_index = i;
            }
        }
        return data[max_index];
    }

    bool empty() const {
        return data.empty();
    }

};
