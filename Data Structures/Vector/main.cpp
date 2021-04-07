#include <iostream>
#include <type_traits>
#include "vector.h"
#include "test_runner.h"
#include <vector>

void test_defoult_ctor()
{
    Vector<int> test_vec;
    ASSERT(std::is_constructible_v<Vector<int>>);
    ASSERT(std::is_default_constructible_v<Vector<int>>);
    ASSERT_EQUAL(test_vec.size(), 0);
    ASSERT_EQUAL(test_vec.capacity(), 0);
}

void test_alloc_ctor()
{
    Allocator<int> test_alloc;
    Vector<int> test_vec(test_alloc);
    ASSERT_EQUAL(test_vec.size(), 0);
    ASSERT_EQUAL(test_vec.capacity(), 0);
}

void test_size_ctor()
{
    Vector<int> test_vec(5);
    ASSERT_EQUAL(test_vec.size(), 5);
    ASSERT_EQUAL(test_vec.capacity(), 5);

    for (int& i : test_vec)
    {
        ASSERT_EQUAL(i, 0);
    }
}

void test_size_value_ctor()
{
    Vector<int> test_vec(5, 5);
    ASSERT_EQUAL(test_vec.size(), 5);
    ASSERT_EQUAL(test_vec.capacity(), 5);

    for (int& i : test_vec)
    {
        ASSERT_EQUAL(i, 5);
    }
}

void test_input_iter_ctor()
{
    std::vector<int> test_std_vec(5, 5);
    Vector<int> test_vec(test_std_vec.begin(), test_std_vec.end());
    ASSERT_EQUAL(test_vec.size(), 5);
    ASSERT_EQUAL(test_vec.capacity(), 5);

    for (int& i : test_vec)
    {
        ASSERT_EQUAL(i, 5);
    }
}

int main()
{
    TestRunner tr;
    tr.RunTest(test_defoult_ctor, "test_defoult_constructor");
    tr.RunTest(test_alloc_ctor, "test_alloc_constructor");
    tr.RunTest(test_size_ctor, "test_size_ctor");
    tr.RunTest(test_size_value_ctor, "test_size_value_ctor");
    tr.RunTest(test_input_iter_ctor, "test_input_iter_ctor");
    return 0;
}