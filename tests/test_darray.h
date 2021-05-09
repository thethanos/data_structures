#pragma once

#include <algorithm>
#include <gtest/gtest.h>

#include "darray.h"

TEST(DArrayTest, EmptyTest)
{
    DArray<int> darray;

    ASSERT_TRUE(darray.empty());
    ASSERT_EQ(darray.size(), 0);

    darray.reserve(5);
    ASSERT_TRUE(darray.empty());
}

TEST(DArrayTest, ConstructorTest)
{
    std::vector<int> example{0, 1, 2, 3, 4, 5, 6};

    DArray<int> darray1{0, 1, 2, 3, 4, 5, 6};
    ASSERT_TRUE(std::equal(darray1.begin(), darray1.end(), example.begin()));

    DArray<int> darray2(100);
    ASSERT_EQ(darray2.size(), 100);


    DArray<int> darray3(std::move(darray1));
    ASSERT_TRUE(std::equal(darray3.begin(), darray3.end(), example.begin()));
    ASSERT_TRUE(darray1.empty());
}

TEST(DArrayTest, SizeTest)
{
    DArray<int> darray{0, 1, 2, 3, 4, 5};

    ASSERT_EQ(darray.size(), 6);
    ASSERT_EQ(darray.capacity(), 6);

    darray.resize(100);
    ASSERT_EQ(darray.size(), 100);
    
    darray.reserve(200);
    ASSERT_EQ(darray.capacity(), 200);
}

TEST(DArrayTest, PushTest)
{
    DArray<int> darray;

    darray.push_back(10);
    ASSERT_FALSE(darray.empty());
    ASSERT_EQ(darray[0], 10);

    darray.push_back(20);
    ASSERT_EQ(darray.size(), 2);
    ASSERT_EQ(darray[1], 20);

    for(size_t i(0); i < 100; ++i)
        darray.push_back(i);

    ASSERT_EQ(darray.size(), 102);
}

TEST(DArrayTest, PopTest)
{
    DArray<int> darray{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ASSERT_EQ(darray.back(), 10);

    darray.pop_back();
    ASSERT_NE(darray.back(), 10);
    ASSERT_EQ(darray.back(), 9);

    darray.pop_back();
    darray.pop_back();
    ASSERT_EQ(darray.back(), 7);

    while(!darray.empty())
        darray.pop_back();

    ASSERT_EQ(darray.size(), 0);    
}

TEST(DArrayTest, CopyTest)
{
    DArray<int> darray1{0, 1, 2, 3, 4, 5, 6, 7}, darray2;

    darray2 = darray1;
    ASSERT_TRUE(std::equal(darray2.begin(), darray2.end(), darray1.begin()));

    DArray<int> darray3(darray1);
    ASSERT_TRUE(std::equal(darray3.begin(), darray3.end(), darray1.begin()));
}