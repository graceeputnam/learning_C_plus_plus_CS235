#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include "DLList.h"

#include "test_utils.h"

template <class T, class E>
void assert_lists(DLList<T> const &obs, E const &exp)
{
    ASSERT_EQ(obs.size(), exp.size());
    const typename DLList<T>::Node *node = obs.get_head();

    for (size_t i = 0; i < exp.size(); i++)
    {
        if (node == nullptr) { FAIL; }
        if (node->value != exp[i])
        {
            std::cout << "ERROR: mismatch at position " << i;
            std::cout << " " << node->value << " != " << exp[i] << std::endl;
            FAIL;
        }
        node = node->next;
    }
}

TEST(push_front_size, 2)
{
    DLList<float> list;
    ASSERT_EQ(list.size(), 0);
    list.push_front(1);
    ASSERT_EQ(list.size(), 1);
    list.push_front(2);
    ASSERT_EQ(list.size(), 2);
    list.push_front(3);
    ASSERT_EQ(list.size(), 3);
}

TEST(push_pop_front_size, 5)
{
    DLList<int> list;
    ASSERT_EQ(list.size(), 0);
    for (size_t i = 0; i < 100; i++)
    {
        list.push_front(i);
    }
    ASSERT_EQ(list.size(), 100);

    for (size_t i = 0; i < 100; i++)
    {
        list.pop_front();
    }
    ASSERT_EQ(list.size(), 0);
}

TEST(push_back_size, 3)
{
    DLList<int> list;
    ASSERT_EQ(list.size(), 0);
    list.push_back(1);
    ASSERT_EQ(list.size(), 1);
    list.push_back(2);
    ASSERT_EQ(list.size(), 2);
    list.push_back(3);
    ASSERT_EQ(list.size(), 3);
}

TEST(push_pop_back_size, 5)
{
    DLList<int> list;
    ASSERT_EQ(list.size(), 0);
    for (size_t i = 0; i < 100; i++)
    {
        list.push_back(i);
    }
    ASSERT_EQ(list.size(), 100);

    for (size_t i = 0; i < 100; i++)
    {
        list.pop_back();
    }
    ASSERT_EQ(list.size(), 0);
}

TEST(push_front_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.push_front(i);
    }
    std::vector<int> exp = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    assert_lists(list, exp);
}

TEST(push_back_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.push_back(i);
    }
    std::vector<int> exp = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert_lists(list, exp);
}

TEST(push_front_back_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        if (i & 1)
        {
            list.push_back(i);
        }
        else
        {
            list.push_front(i);
        }
    }
    std::vector<int> exp = {8, 6, 4, 2, 0, 1, 3, 5, 7, 9};
    assert_lists(list, exp);
}

TEST(insert_front_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.insert(i, 0);
    }
    std::vector<int> exp = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    assert_lists(list, exp);
}

TEST(insert_back_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.insert(i, list.size());
    }
    std::vector<int> exp = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert_lists(list, exp);
}

TEST(insert_middle_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.insert(i, list.size() / 2);
    }
    std::vector<int> exp = {1, 3, 5, 7, 9, 8, 6, 4, 2, 0};
    assert_lists(list, exp);
}

TEST(remove_front_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.push_back(i);
    }
    for (size_t i = 0; i < 5; i++)
    {
        list.remove(0);
    }
    std::vector<int> exp = {5, 6, 7, 8, 9};
    assert_lists(list, exp);
}

TEST(remove_back_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.push_back(i);
    }
    for (size_t i = 0; i < 5; i++)
    {
        list.remove(list.size() - 1);
    }
    std::vector<int> exp = {0, 1, 2, 3, 4};
    assert_lists(list, exp);
}

TEST(remove_middle_contents, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.push_back(i);
    }
    for (size_t i = 0; i < 5; i++)
    {
        list.remove(list.size() / 2);
    }
    std::vector<int> exp = {0, 1, 2, 8, 9};
    assert_lists(list, exp);
}

TEST(front, 5)
{
    DLList<int> list;

    for (size_t i = 0; i < 5; i++)
    {
        list.push_back(i);
        ASSERT_EQ(list.front(), 0);
    }

    for (size_t i = 10; i < 15; i++)
    {
        list.push_front(i);
        ASSERT_EQ(list.front(), i);
    }

    list.pop_front();
    ASSERT_EQ(list.front(), 13);

    list.pop_back();
    ASSERT_EQ(list.front(), 13);
}

TEST(back, 5)
{
    DLList<int> list;

    for (size_t i = 0; i < 5; i++)
    {
        list.push_back(i);
        ASSERT_EQ(list.back(), i);
    }

    for (size_t i = 10; i < 15; i++)
    {
        list.push_front(i);
        ASSERT_EQ(list.back(), 4);
    }

    list.pop_front();
    ASSERT_EQ(list.back(), 4);

    list.pop_back();
    ASSERT_EQ(list.back(), 3);
}

TEST(at, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 5; i++)
    {
        list.push_back(i);
        ASSERT_EQ(list.at(i), i);
    }
}

TEST(contains, 5)
{
    DLList<int> list;
    for (size_t i = 0; i < 5; i++)
    {
        list.push_back(i);
    }
    ASSERT(list.contains(0));
    ASSERT(list.contains(4));
    ASSERT(!list.contains(7));
    list.remove(3);
    ASSERT(!list.contains(3));
}

TEST(clear, 5)
{
    DLList<int> list;

    for (size_t i = 0; i < 5; i++)
    {
        list.push_back(i);
    }

    ASSERT_EQ(list.size(), 5);

    list.clear();
    ASSERT_EQ(list.size(), 0);

    for (size_t i = 0; i < 5; i++)
    {
        list.push_back(i);
    }

    ASSERT_EQ(list.size(), 5);
}

TEST(gamut, 10)
{
    DLList<int> list;

    for (size_t i = 0; i < 1000; i++)
    {
        list.push_back(i);
    }

    while (list.size() > 0)
    {
        list.pop_front();
    }

    for (size_t i = 0; i < 1000; i++)
    {
        list.push_front(i);
    }

    while (list.size() > 0)
    {
        list.pop_back();
    }

    while (list.size() < 1000)
    {
        list.insert(list.size(), list.size() / 2);
    }

    while (list.size() > 0)
    {
        list.remove(list.size() / 2);
    }

    list.clear();
    list.clear();

    auto head = list.get_head();
    ASSERT_EQ(head, nullptr);

    std::vector<int> expected;
    for (size_t i = 0; i < 100000; i++)
    {
        list.push_back(i);
        expected.push_back(i);
    }
    assert_lists(list, expected);
}

DO_VALGRIND(5);

TEST_MAIN();