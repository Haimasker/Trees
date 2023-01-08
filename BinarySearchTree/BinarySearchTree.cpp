#include "BinarySearchTree.hpp"

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(T data, size_t counter)
	: BinaryTreeNode<T>(data, counter) { }

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const BinarySearchTreeNode& node)
	: BinaryTreeNode<T>(node) { }

template<class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(BinarySearchTreeNode&& node)
	: BinaryTreeNode<T>(node) { }

template <class T>
BinarySearchTreeNode<T>::~BinarySearchTreeNode() {
	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;
	delete this;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTreeNode<T>* node)
	: BinaryTree<T>(node) { }