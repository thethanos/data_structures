#pragma once

#include <gtest/gtest.h>

#include "bstree.h"

template <class T>
void bstree_inorder(BS::Node<T>* root, std::vector<T>& res)
{
	if (!root) return;

	bstree_inorder(root->m_pLeft, res);
	res.push_back(root->m_Value);
	bstree_inorder(root->m_pRight, res);
}

class BSTreeTest : public ::testing::Test
{
protected:
	void SetUp() override;


protected:
	BSTree<int> m_Tree;
};

void BSTreeTest::SetUp()
{
	for (const auto& item : { 8, 6, 12, 3, 7 , 10, 14 })
		m_Tree.insert(item);
}

TEST_F(BSTreeTest, SizeTest)
{
	ASSERT_EQ(m_Tree.size(), 7);
	ASSERT_FALSE(m_Tree.empty());
}

TEST_F(BSTreeTest, InorderTest)
{
	std::vector<int> output, correct_res = { 3, 6, 7, 8, 10, 12, 14 };
	bstree_inorder<int>(m_Tree.get_root(), output);

	ASSERT_TRUE(std::equal(output.begin(), output.end(), correct_res.begin()));
}

TEST_F(BSTreeTest, InsertRemoveTest)
{
	size_t size = m_Tree.size();

	m_Tree.remove(0);
	ASSERT_EQ(size, m_Tree.size());

	m_Tree.remove(3);
	ASSERT_NE(size, m_Tree.size());

	m_Tree.remove(12);
	ASSERT_EQ(m_Tree.size(), 5);

	std::vector<int> output1, correct_res1 = {6, 7, 8, 10, 14 };
	bstree_inorder<int>(m_Tree.get_root(), output1);
	ASSERT_TRUE(std::equal(output1.begin(), output1.end(), correct_res1.begin()));

	m_Tree.insert(3);
	m_Tree.insert(3);
	m_Tree.insert(14);

	ASSERT_EQ(m_Tree.size(), 6);

	std::vector<int> output2, correct_res2 = { 3, 6, 7, 8, 10, 14 };
	bstree_inorder<int>(m_Tree.get_root(), output2);
	ASSERT_TRUE(std::equal(output2.begin(), output2.end(), correct_res2.begin()));
}

TEST_F(BSTreeTest, ContainsTest)
{
	ASSERT_TRUE(m_Tree.contains(3));
	ASSERT_FALSE(m_Tree.contains(16));
}