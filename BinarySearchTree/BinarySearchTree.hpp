#pragma once
#include "../BinaryTree/BinaryTree.hpp"

template <class T>
class BinarySearchTreeNode : public BinaryTreeNode<T> {
public:
	BinarySearchTreeNode(T = T(), size_t = 0);
	BinarySearchTreeNode(const BinarySearchTreeNode&);
	BinarySearchTreeNode(BinarySearchTreeNode&&);
	~BinarySearchTreeNode();
};

template <class T>
class BinarySearchTree : public BinaryTree<T> {
public:
	BinarySearchTree(const BinarySearchTreeNode<T>* = nullptr);		//
	BinarySearchTree(const BinarySearchTree&);						//
	BinarySearchTree(BinarySearchTree&&);							//
	virtual ~BinarySearchTree() = 0;
};