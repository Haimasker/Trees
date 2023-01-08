#include "BinaryTree.hpp"

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T data, size_t counter)
	: data(data), counter(counter), left(nullptr), right(nullptr) { }

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode& node) {
	this->data = node ? node.data : T();
	this->counter = node ? node.counter : 0;
	this->left = nullptr;
	this->right = nullptr;
	//left = new BinaryTreeNode(node.left.data, node.left.counter);
	//right = new BinaryTreeNode(node.right.data, node.right.counter);
}

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(BinaryTreeNode&& node)
	: data(node.data), counter(node.counter) {
	std::exchange(this->left, node.left);
	std::exchange(this->right, node.right);
}

template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::deepCopy(const BinaryTreeNode& node) {
	this->data = node.data;
	this->counter = node.counter;
	this->left = nullptr;
	this->right = nullptr;
	if (node.left)
		this->left = deepCopy(node.left);
	if (node.right)
		this->right = deepCopy(node.right);
	return this;
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTreeNode<T>* node)
	: root(node), size_(node->counter), capacity_(1) { }

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree& tree)
	: root(tree.root), size_(tree.size_), capacity_(tree.capacity_) {
	this->root.left = deepCopy(tree.root.left);
	this->root.right = deepCopy(tree.root.right);
}

template <class T>
BinaryTree<T>::BinaryTree(BinaryTree&& tree) {
	std::exchange(this->root, tree.root);
	std::exchange(this->size_, tree.size_);
	std::exchange(this->capacity_, tree.capacity_);
}