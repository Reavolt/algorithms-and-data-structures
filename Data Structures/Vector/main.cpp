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
void test_move_assig_oper()
{
    Vector<int> test_vec_1(10, 5);
    Vector<int> test_vec_2 = std::move(test_vec_1);

    ASSERT_EQUAL(test_vec_1.size(), 0);
    ASSERT_EQUAL(test_vec_1.capacity(), 0);
    ASSERT_EQUAL(test_vec_2.size(), 10);
    ASSERT_EQUAL(test_vec_2.capacity(), 10);

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_init_assig_oper()
{
    Vector<int> test_vec_1 = {5,5,5,5,5};

    ASSERT_EQUAL(test_vec_1.size(), 5);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_assign_itr()
{
    Vector<int> test_vec_1(5,5);
    Vector<int> test_vec_2;
    Vector<int> test_vec_3(10, 5);
    Vector<int> test_vec_4(20, 5);

    ASSERT_EQUAL(test_vec_1.size(), 5);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);

    test_vec_2.assign(test_vec_1.begin(), test_vec_1.end());

    ASSERT_EQUAL(test_vec_2.size(), 5);
    ASSERT_EQUAL(test_vec_2.capacity(), 5);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }

    test_vec_4.assign(test_vec_3.begin(), test_vec_3.end());

    ASSERT_EQUAL(test_vec_4.size(), 10);
    ASSERT_EQUAL(test_vec_4.capacity(), 20);

    for (int& i : test_vec_4)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_assign_value_size()
{
    Vector<int> test_vec_1(5,5);
    Vector<int> test_vec_2(10, 5);

    ASSERT_EQUAL(test_vec_1.size(), 5);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);

    ASSERT_EQUAL(test_vec_2.size(), 10);
    ASSERT_EQUAL(test_vec_2.capacity(), 10);

    test_vec_1.assign(10, 5);

    ASSERT_EQUAL(test_vec_1.size(), 10);
    ASSERT_EQUAL(test_vec_1.capacity(), 10);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }

    test_vec_2.assign(5, 5);

    ASSERT_EQUAL(test_vec_2.size(), 5);
    ASSERT_EQUAL(test_vec_2.capacity(), 10);

    for (int& i : test_vec_2)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_assign_init_list()
{
    Vector<int> test_vec_1(5,5);

    ASSERT_EQUAL(test_vec_1.size(), 5);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);

    test_vec_1.assign({5,5,5,5});

    ASSERT_EQUAL(test_vec_1.size(), 4);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }

    test_vec_1.assign({5,5,5,5,5});

    ASSERT_EQUAL(test_vec_1.size(), 5);
    ASSERT_EQUAL(test_vec_1.capacity(), 5);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }

    test_vec_1.assign({5,5,5,5,5,5});

    ASSERT_EQUAL(test_vec_1.size(), 6);
    ASSERT_EQUAL(test_vec_1.capacity(), 6);

    for (int& i : test_vec_1)
    {
        ASSERT_EQUAL(i, 5);
    }
}
//----------------------------------------------------------------------------------------------------
void test_iterator()
{
    Vector<int> test_vec{1,2,3,4,5};
    Vector<int>::iterator test_iter_beg = test_vec.begin();
    Vector<int>::iterator test_iter_end = test_vec.end();

    ASSERT_EQUAL(*test_iter_beg, 1);
    ASSERT_EQUAL(*std::prev(test_iter_end), 5);

    size_t i = 0;
    for (; test_iter_beg != test_iter_end; test_iter_beg++)
    {
        ASSERT_EQUAL(*test_iter_beg, ++i);
    }
}
//----------------------------------------------------------------------------------------------------
void test_const_iterator()
{
//    std::vector<int> test_vec{1,2,3,4,5};
//    std::vector<int>::const_iterator test_iter_beg = test_vec.begin();
//    std::vector<int>::const_iterator test_iter_end = test_vec.end();

    Vector<int> test_vec{1,2,3,4,5};
    Vector<int>::const_iterator test_iter_beg = test_vec.begin();
    Vector<int>::const_iterator test_iter_end = test_vec.end();

    ASSERT_EQUAL(*test_iter_beg, 1);
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
    tr.RunTest(test_dctor, "test_dctor");
    tr.RunTest(test_copy_assig_oper, "test_copy_assig_oper");
    tr.RunTest(test_move_assig_oper, "test_move_assig_oper");
    tr.RunTest(test_init_assig_oper, "test_init_assig_oper");
    tr.RunTest(test_assign_itr, "test_assign_itr");
    tr.RunTest(test_assign_value_size, "test_assign_value_size");
    tr.RunTest(test_assign_init_list, "test_assign_init_list");
    tr.RunTest(test_iterator, "test_iterator");
    tr.RunTest(test_const_iterator, "test_const_iterator");
    return 0;
}
//----------------------------------------------------------------------------------------------------