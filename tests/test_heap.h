#pragma once

#include <gtest/gtest.h>

#include "heap.h"

class HeapTest : public ::testing::Test
{
protected:
	void SetUp() override;


protected:
	Heap<int> m_Heap;
};

void HeapTest::SetUp()
{
	for (const auto& item : { 0, 5, 2 ,6, 8, 2, 9, 2, 3 })
		m_Heap.push(item);
}

TEST_F(HeapTest, SizeTest)
{
	ASSERT_EQ(m_Heap.size(), 9);
	ASSERT_FALSE(m_Heap.empty());
}

TEST_F(HeapTest, PushTest)
{
	m_Heap.push(12);
	ASSERT_EQ(m_Heap.size(), 10);
	ASSERT_EQ(m_Heap.top(), 0);

	m_Heap.push(-1);
	ASSERT_NE(m_Heap.top(), 0);
}

TEST_F(HeapTest, PopTest)
{
	ASSERT_FALSE(m_Heap.empty());
	ASSERT_EQ(m_Heap.top(), 0);
	
	m_Heap.pop();
	ASSERT_NE(m_Heap.top(), 0);

	while (!m_Heap.empty())
		m_Heap.pop();

	ASSERT_TRUE(m_Heap.empty());
	ASSERT_EQ(m_Heap.size(), 0);
}