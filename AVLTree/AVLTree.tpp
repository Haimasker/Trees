#include <iostream>

template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& data, size_t counter, size_t height)
	: BinarySearchTreeNode<T>(data, counter), height(height) {
	std::cout << "AVL data ctor\n";
}

template <class T>
AVLTreeNode<T>::AVLTreeNode(const AVLTreeNode<T>& node)
	: BinarySearchTreeNode<T>(node) {
	std::cout << "AVL copy ctor\n";
	this->copyHeights(node);
	//this->left = node.left ? new AVLTreeNode<T>(*node.left) : nullptr;
	//this->right = node.right ? new AVLTreeNode<T>(*node.right) : nullptr;
}

template<class T>
AVLTreeNode<T>::AVLTreeNode(AVLTreeNode<T>&& node)
	: data(std::move(node.data)), counter(std::move(node.counter)), height(std::move(node.height)) {
	std::cout << "AVL move ctor\n";
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
}

template <class T>
AVLTreeNode<T>::~AVLTreeNode() {
	std::cout << "AVL dtor\n";
	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;
	this->counter = 0;
	this->height = 0;
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::getLeft() const {
	return static_cast<AVLTreeNode<T>*>(BinarySearchTreeNode<T>::getLeft());
}


template <class T>
void AVLTreeNode<T>::copyHeights(BinarySearchTreeNode<T>* const node) {
	if (!node)
		return;
	this->height = node->height;
	this->left->copyHeights(node->left);
	this->right->copyHeights(node->right);
	return;

}