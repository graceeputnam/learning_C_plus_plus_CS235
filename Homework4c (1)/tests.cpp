#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Vector.h"

#include "test_utils.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "{";
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        os << vec[i] << ", ";
    }
    os << vec[vec.size()-1] << "}";
    return os;
}

template<class T>
void assert_vectors(Vector<T> &obs, std::vector<T> const &exp) {
    ASSERT_EQ(obs.size(), exp.size());
    for (size_t i = 0; i < exp.size(); i++) {
        if (obs[i] != exp[i]) {
            std::cout << "ERROR: mismatch at position " << i;
            std::cout << " " << obs[i] << " != " <<  exp[i] << std::endl;
            FAIL;
        }
    }
}

TEST(constructor_destructor_const_size_empty, 2) {
    const Vector<float> vec;
    ASSERT_EQ(vec.size(), 0);
}

TEST(reasonable_initial_capacity, 2) {
    std::vector<Vector<int>> vecs(100000);
}

TEST(push_back_size, 2) {
    Vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    vec.push_back(1);
    ASSERT_EQ(vec.size(), 1);
    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
}

TEST(push_back_grow_size, 2) {
    Vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    int N = 100000;
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
    }
    ASSERT_EQ(vec.size(), N);
}

TEST(pop_back_size, 2) {
    Vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    vec.push_back(1);
    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
    vec.pop_back();
    ASSERT_EQ(vec.size(), 1);
    vec.pop_back();
    ASSERT_EQ(vec.size(), 0);
}

TEST(pop_back_grow_size, 5) {
    Vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    int N = 100000;
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
    }
    ASSERT_EQ(vec.size(), N);
    while (vec.size() > 0) {
        vec.pop_back();
    }
    ASSERT_EQ(vec.size(), 0);
}

TEST(clear_size, 5) {
    Vector<int> vec;
    ASSERT_EQ(vec.size(), 0);
    int N = 100000;
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
    }
    ASSERT_EQ(vec.size(), N);
    vec.clear();
    ASSERT_EQ(vec.size(), 0);
}

TEST(operator_brackets, 5) {
    Vector<int> vec;
    int N = 10;
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
    }
    ASSERT_EQ(vec.size(), N);
    ASSERT_EQ(vec[0], 0);
    ASSERT_EQ(vec[2], 2);
    ASSERT_EQ(vec[4], 4);
    ASSERT_EQ(vec[6], 6);
    ASSERT_EQ(vec[8], 8);
}

TEST(at, 5) {
    Vector<int> vec;
    int N = 10;
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
    }

    ASSERT_EQ(vec.size(), N);
    ASSERT_EQ(vec.at(0), 0);
    ASSERT_EQ(vec.at(2), 2);
    ASSERT_EQ(vec.at(4), 4);
    ASSERT_EQ(vec.at(6), 6);
    ASSERT_EQ(vec.at(8), 8);

    bool threw_exception = true;
    try {
        vec.at(100);
        std::cout << "There was no exception thrown for going out of bounds" << std::endl;
        threw_exception = false;
    } catch (std::out_of_range &caught_exception) {

    } catch (...) {
        std::cout << "The wrong exception type was thrown" << std::endl;
        FAIL
    }
    ASSERT_EQ(threw_exception, true);

    threw_exception = true;
    try {
        vec.at(10);
        std::cout << "There was no exception thrown for going out of bounds (index=10)" << std::endl;
        threw_exception = false;
    } catch (std::out_of_range &caught_exception) {

    } catch (...) {
        std::cout << "The wrong exception type was thrown" << std::endl;
        FAIL
    }
    ASSERT_EQ(threw_exception, true);

    threw_exception = true;
    try {
        vec.at(-91);
        std::cout << "There was no exception thrown for going out of bounds (index=-91)" << std::endl;
        threw_exception = false;
    } catch (std::out_of_range &caught_exception) {

    } catch (...) {
        std::cout << "The wrong exception type was thrown" << std::endl;
        FAIL
    }
    ASSERT_EQ(threw_exception, true);
}

TEST(insert_back, 5) {
    Vector<int> vec;
    std::vector<int> exp;
    int N = 100;
    for (int i = 0; i < N; i++) {
        vec.insert(i, vec.size());
        exp.push_back(i);
    }
    ASSERT_VEQ(vec, exp);
}

TEST(insert_front, 5) {
    Vector<int> vec;
    std::vector<int> exp;
    int N = 100;
    for (int i = 0; i < N; i++) {
        vec.insert(i, 0);
        exp.push_back(N - 1 - i);
    }
    ASSERT_VEQ(vec, exp);
}

TEST(insert_middle, 5) {
    Vector<int> vec;
    for (int i = 0; i < 5; i++) {
        vec.push_back(i);
    }
    vec.insert(7, 1);
    vec.insert(8, 4);
    vec.insert(9, 3);

    std::vector<int> exp = {0, 7, 1, 9, 2, 8, 3, 4};
    ASSERT_VEQ(vec, exp);
}

TEST(remove_back, 5) {
    Vector<int> vec;
    for (int i = 0; i < 20; i++) {
        vec.push_back(i);
    }
    for (int i = 0; i < 15; i++) {
        vec.remove(vec.size()-1);
    }
    std::vector<int> exp = {0, 1, 2, 3, 4};
    ASSERT_VEQ(vec, exp);
}

TEST(remove_front, 5) {
    Vector<int> vec;
    for (int i = 0; i < 20; i++) {
        vec.push_back(i);
    }
    for (int i = 0; i < 15; i++) {
        vec.remove(0);
    }
    std::vector<int> exp = {15, 16, 17, 18, 19};
    ASSERT_VEQ(vec, exp);
}

TEST(remove_middle, 5) {
    Vector<int> vec;
    for (int i = 0; i < 5; i++) {
        vec.push_back(i);
    }
    vec.remove(1);
    vec.remove(2);
    std::vector<int> exp = {0, 2, 4};
    ASSERT_VEQ(vec, exp);
}

TEST(operator_bracket_assignment, 5) {
    Vector<int> vec;
    for (int i = 0; i < 5; i++) { 
        vec.push_back(i);
    }
    vec[0] = 7;
    vec[4] = 8;
    std::vector<int> exp = {7, 1, 2, 3, 8};
    ASSERT_VEQ(vec, exp);
}

TEST(grow, 10) {
    // If the vector grows correctly, then memory location should change

    Vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
    }
    int* addr = &(vec[0]);

    for (int i = 0; i < 1000; i++) {
        vec.push_back(i);
    }
    int* addr_after_first_add = &(vec[0]);
    ASSERT_EQ((addr != addr_after_first_add), true, "The address for the first item should move after growing")

    for (int i = 0; i < 10000; i++) {
        vec.push_back(i);
    }
    int* addr_after_second_add = &(vec[0]);
    ASSERT_EQ((addr != addr_after_second_add), true, "The address for the first item should move after growing")
}

TEST(gamut, 10) {
    Vector<int> vec;
    std::vector<int> expected;
    int N = 100;
    for (int i = 0; i < N; i++) {
        vec.insert(i, 0);
        expected.insert(expected.begin(), i);
    }
    assert_vectors(vec, expected);

    N *= 100;
    
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
        expected.push_back(i);
    }
    assert_vectors(vec, expected);

    
    vec.clear();
    expected.clear();
    assert_vectors(vec, expected);

    for (int i = 0; i < N; i++) {
        vec.push_back(i);
        expected.push_back(i);
    }
    assert_vectors(vec, expected);

    while (vec.size() != 0) {
        vec.pop_back();
        expected.pop_back();
    }
    assert_vectors(vec, expected);

    N = 100;
    srand(235);
    for (int i = 0; i < N; i++) {
        size_t pos = rand() % (vec.size() + 1);
        vec.insert(i, pos);
        expected.insert(expected.begin() + pos, i);
    }
    assert_vectors(vec, expected);

    while (vec.size() > 0) {
        size_t pos = rand() % vec.size();
        vec.remove(pos);
    }
    ASSERT_EQ(vec.size(), 0);
}

TEST(performance, 10) {
    Timer timer;
    int N = 1000;
    size_t n_rounds = 5;
    Vector<int> vec;

    for (size_t round = 1; round <= n_rounds; round++) {
        N *= 10;
        std::cout << "Round " << round << ": N = " << N << std::endl;

        timer.start();
        for (int i = 0; i < N; i++) {
            vec.push_back(i);        
        }
        while (vec.size() > 0) {
            vec.pop_back();
        }
        std::cout << "Time: " << timer.milliseconds() << " ms" << std::endl;
        if (timer.seconds() > 20) {
            PARTIAL_CREDIT(round / n_rounds);
        }
    }
}

DO_VALGRIND(5);

TEST_MAIN()
