#pragma once

#include "gtest/gtest.h"

#include "stack.h"

class CStackTest : public ::testing::Test
{
protected:
    void SetUp() override;

protected:
    Stack<int> m_Stack;
};

void CStackTest::SetUp()
{
    for(size_t i(0); i < 100; ++i)
        m_Stack.push(i);
}

TEST(StackTest, EmptyTest)
{
    Stack<int> st;
    ASSERT_TRUE(st.empty());
    ASSERT_EQ(st.size(), 0);
}

TEST_F(CStackTest, PushTest)
{
    size_t size = m_Stack.size();
    m_Stack.push(1);
    ASSERT_EQ(m_Stack.size(), size + 1);
    ASSERT_EQ(m_Stack.top(), 1);

    for(size_t i(0); i < 100; ++i)
        m_Stack.push(i);

    ASSERT_EQ(m_Stack.size(), 201);
    ASSERT_EQ(m_Stack.top(), 99);
}

TEST_F(CStackTest, PopTest)
{
    size_t size = m_Stack.size();
    m_Stack.pop();
    ASSERT_EQ(m_Stack.size(), size-1);

    m_Stack.pop();
    m_Stack.pop();
    ASSERT_EQ(m_Stack.size(), size-3);

    while(!m_Stack.empty())
        m_Stack.pop();

    ASSERT_TRUE(m_Stack.empty());
    ASSERT_EQ(m_Stack.size(), 0);
}