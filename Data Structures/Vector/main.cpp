#include <iostream>
#include <type_traits>
#include "vector.h"
#include "test_runner.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
void test_defoult_ctor()
{
    Vector<int> test_vec;

    ASSERT(std::is_constructible_v<Vector<int>>);
    ASSERT(std::is_default_constructible_v<Vector<int>>);

    ASSERT_EQUAL(test_vec.size(), 0);
    ASSERT_EQUAL(test_vec.capacity(), 0);
}
//----------------------------------------------------------------------------------------------------
void test_alloc_ctor()
{
    Allocator<int> test_alloc;
    Vector<int> test_vec(test_alloc);

    ASSERT_EQUAL(test_vec.size(), 0);
    ASSERT_EQUAL(test_vec.capacity(), 0);
}
//----------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------
void test_copy_ctor()
{
    Vector<int> test_vec_1(5, 5);
    Vector<int> test_vec_2(test_vec_1);

    ASSERT_EQUAL(test_vec_2.size(), 5);
    ASSERT_EQUAL(test_vec_2.capacity(), 5);

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_move_ctor()
{
    Vector<int> test_vec_1(5, 5);
    Vector<int> test_vec_2(std::move(test_vec_1));

    ASSERT_EQUAL(test_vec_1.size(), 0);
    ASSERT_EQUAL(test_vec_1.capacity(), 0);
    ASSERT_EQUAL(test_vec_2.size(), 5);
    ASSERT_EQUAL(test_vec_2.capacity(), 5);

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_copy_alloc_ctor()
{
    Allocator<int> test_alloc;
    Vector<int> test_vec_1(5, 5);
    Vector<int> test_vec_2(test_vec_1, test_alloc);

    ASSERT_EQUAL(test_vec_2.size(), 5);
    ASSERT_EQUAL(test_vec_2.capacity(), 5);

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_move_alloc_ctor()
{
    Allocator<int> test_alloc;
    Vector<int> test_vec_1(5, 5);
    Vector<int> test_vec_2(std::move(test_vec_1), test_alloc);

    ASSERT_EQUAL(test_vec_2.size(), 5);
    ASSERT_EQUAL(test_vec_2.capacity(), 5);

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_init_list_ctor()
{
    Allocator<int> test_alloc;
    Vector<int> test_vec_1({5,5,5,5,5});
    Vector<int> test_vec_2({5,5,5,5,5,5}, test_alloc);

    ASSERT_EQUAL(test_vec_1.size(), 5);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);
    ASSERT_EQUAL(test_vec_2.size(), 6);
    ASSERT_EQUAL(test_vec_2.capacity(), 6);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_dctor()
{
    Vector<int> test_vec;

    ASSERT(std::is_destructible_v<Vector<int>>);
    ASSERT(std::is_nothrow_destructible_v<Vector<int>>);
}
//----------------------------------------------------------------------------------------------------
void test_copy_assig_oper()
{
    Vector<int> test_vec_1(10, 5);
    Vector<int> test_vec_2 = test_vec_1;

    ASSERT_EQUAL(test_vec_1.size(), 10);
    ASSERT_EQUAL(test_vec_1.capacity(), 10);
    ASSERT_EQUAL(test_vec_2.size(), 10);
    ASSERT_EQUAL(test_vec_2.capacity(), 10);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(test_defoult_ctor, "test_defoult_constructor");
    tr.RunTest(test_alloc_ctor, "test_alloc_constructor");
    tr.RunTest(test_size_ctor, "test_size_ctor");
    tr.RunTest(test_size_value_ctor, "test_size_value_ctor");
    tr.RunTest(test_input_iter_ctor, "test_input_iter_ctor");
    tr.RunTest(test_copy_ctor, "test_copy_ctor");
    tr.RunTest(test_move_ctor, "test_move_ctor");
    tr.RunTest(test_copy_alloc_ctor, "test_copy_alloc_ctor");
    tr.RunTest(test_move_alloc_ctor, "test_move_alloc_ctor");
    tr.RunTest(test_init_list_ctor, "test_init_list_ctor");
    tr.RunTest(test_copy_assig_oper, "test_copy_assig_oper");
    return 0;
}
//----------------------------------------------------------------------------------------------------