#include <iostream>
#include <string>

#include "HashSet.h"
#include "test_utils.h"

TEST(insert, 10)
{
    HashSet<int> set;
    ASSERT(set.insert(1));
    ASSERT(set.insert(2));
    ASSERT(set.insert(3));
    ASSERT(set.insert(4));
    ASSERT(set.insert(5));

    ASSERT_EQ(set.insert(5), false);
    ASSERT_EQ(set.insert(3), false);
    ASSERT_EQ(set.insert(1), false);
}

TEST(contains, 10)
{
    HashSet<int> set;

    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.insert(6);
    set.insert(7);
    set.insert(10);

    ASSERT_EQ(set.contains(1), false);
    ASSERT(set.contains(2));
    ASSERT(set.contains(3));
    ASSERT(set.contains(4));
    ASSERT_EQ(set.contains(5), false);
    ASSERT(set.contains(6));
    ASSERT(set.contains(7));
    ASSERT_EQ(set.contains(8), false);
    ASSERT_EQ(set.contains(9), false);
    ASSERT(set.contains(10));
}

TEST(remove, 10)
{
    HashSet<std::string> set;

    set.insert("quilt");
    set.insert("pineapple");
    set.insert("utopia");
    set.insert("unity");

    ASSERT(set.remove("quilt"));
    ASSERT(set.remove("utopia"));
    ASSERT_EQ(set.remove("seahorse"), false);

    ASSERT_EQ(set.contains("quilt"), false);
    ASSERT(set.contains("pineapple"));
    ASSERT_EQ(set.contains("utopia"), false);
    ASSERT(set.contains("unity"));
    ASSERT_EQ(set.contains("seahorse"), false);
}

TEST(size, 10)
{
    HashSet<std::string> set;
    ASSERT_EQ(set.size(), 0);

    set.insert("laughter");
    set.insert("freedom");
    set.insert("igloo");
    ASSERT_EQ(set.size(), 3);

    set.remove("laughter");
    set.remove("igloo");
    ASSERT_EQ(set.size(), 1);

    set.remove("short");
    ASSERT_EQ(set.size(), 1);

    set.remove("freedom");
    set.remove("igloo");
    ASSERT_EQ(set.size(), 0);

    set.remove("igloo");
    ASSERT_EQ(set.size(), 0);

    set.insert("goblet");
    set.insert("beard");
    ASSERT_EQ(set.size(), 2);
}

TEST(clear, 10)
{
    HashSet<std::string> set;
    ASSERT_EQ(set.size(), 0);

    set.insert("laughter");
    set.insert("freedom");
    set.insert("igloo");
    ASSERT_EQ(set.size(), 3);

    ASSERT(set.contains("laughter"));
    ASSERT(set.contains("freedom"));
    ASSERT(set.contains("igloo"));

    set.clear();
    ASSERT_EQ(set.contains("laughter"), false);
    ASSERT_EQ(set.contains("freedom"), false);
    ASSERT_EQ(set.contains("igloo"), false);

    ASSERT_EQ(set.size(), 0);
}


TEST(rehashing_stress_test, 20)
{
    HashSet<int> set;

    for (int i = 0; i < 1000; i++) {
        set.insert(i);
    }

    for (int i = 0; i < 1000; i++) {
        if (!set.contains(i)) {
            std::cout << "\nERROR: set.contains(" << i << ") = false, but it should be true" << std::endl;
            FAIL
        }
    }
}

TEST(performance, 20)
{
    HashSet<int> hashset;
    Timer timer;

    int N = 100;

    for (int round = 0; round < 5; round++) {
        std::cout << N  << " items" << std::endl;
        long long calibrated_ns = calibrate(N);
        std::cout << "Calibration time for " << N << " swaps: " << calibrated_ns << std::endl;

        timer.start();
        for (size_t i = 0; i < N; i++) {
            hashset.insert(i);
        }
        long long time_1 = timer.milliseconds();
        ASSERT_EQ(hashset.size(), N);

        for (size_t i = 0; i < N; i++) {
            if (!hashset.contains(i)) FAIL;
        }
        long long time_2 = timer.milliseconds();

        for (size_t i = 0; i < N; i++) {
            hashset.remove(i);
        }
        long long time_3 = timer.milliseconds();
        ASSERT_EQ(hashset.size(), 0);

        timer.stop();

        auto ratio = (timer.nanoseconds() / calibrated_ns);
        std::cout << "Ratio: " << ratio << std::endl;
        ASSERT(ratio < 1000, "Hashset insert/contains/remove time must be < 500x the calibration time");

        std::cout << "Insertion time:\t" << time_1 <<std::endl;
        std::cout << "Contains time:\t" << time_2 - time_1 <<std::endl;
        std::cout << "Remove time:\t" << time_3 - time_2 <<std::endl;
        std::cout << std::endl;

        N *= 10;
        if (timer.seconds() > 10) {
            FAIL;
        }
    }
}

DO_VALGRIND(10);

TEST_MAIN();
