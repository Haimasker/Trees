#include <iostream>

template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& data, size_t counter, size_t height)
	: BinarySearchTreeNode<T>(data, counter), height(height) {
	std::cout << "AVL data ctor\n";
}

template <class T>
AVLTreeNode<T>::AVLTreeNode(const AVLTreeNode<T>& node)
	: BinarySearchTreeNode<T>() {
	std::cout << "AVL copy ctor\n";
	this->copy(node);
}

template<class T>
AVLTreeNode<T>::AVLTreeNode(AVLTreeNode<T>&& node)
	: BinarySearchTreeNode<T>() {
	std::cout << "AVL move ctor\n";
	this->move(std::move(node));
	//(dynamic_cast<AVLTreeNode<T>*>(this))->copyHeights(node);
	//this->left = std::exchange(node.left, nullptr);
	//this->right = std::exchange(node.right, nullptr);
}

template <class T>
AVLTreeNode<T>::~AVLTreeNode() {
	std::cout << "AVL dtor\n";
	//if (this->left)
	//	delete this->left;
	//if (this->right)
	//	delete this->right;
	//this->counter = 0;
	this->height = 0;
}

template <class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (const BinarySearchTreeNode<T>& node) {
	if (this != &node) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(&node));
	}
	return *this;
}

template <class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (BinarySearchTreeNode<T>&& node) {
	if (this != &node) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(std::move(*dynamic_cast<const AVLTreeNode<T>*>(&node)));
	}
	return *this;
}

template <class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (const AVLTreeNode<T>& node) {
	if (this != &node) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(node);
	}
	return *this;
}

template <class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (AVLTreeNode<T>&& node) {
	if (this != &node) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(std::move(node));
	}
	return *this;
}


template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::getLeft() const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTreeNode<T>::getLeft());
}

/*
template <class T>
void AVLTreeNode<T>::setLeft(BinarySearchTreeNode<T>* node) {
	this->left = node;
	return;
}
*/

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::getRight() const {
	return dynamic_cast<AVLTreeNode<T>*>(this->BinarySearchTreeNode<T>::getRight());
}

/*
template <class T>
void AVLTreeNode<T>::setRight(BinarySearchTreeNode<T>* node) {
	this->right = node;
	return;
}
*/

/*
template <class T>
void AVLTreeNode<T>::copyHeights(AVLTreeNode<T>* const node) {
	if (!node)
		return;
	this->height = static_cast<AVLTreeNode<T>*>(node)->height;
	static_cast<AVLTreeNode<T>*>(this->left)->copyHeights(static_cast<AVLTreeNode<T>*>(node)->left);
	static_cast<AVLTreeNode<T>*>(this->right)->copyHeights(static_cast<AVLTreeNode<T>*>(node)->right);
	return;

}
*/

template <class T>
void AVLTreeNode<T>::copy(const BinarySearchTreeNode<T>& node) {
	std::cout << "AVL copy\n";
	this->data = node.data;
	this->counter = node.counter;
	this->height = (dynamic_cast<const AVLTreeNode<T>*>(&node))->height;
	this->left = node.left ? new AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(node.left)) : nullptr;
	this->right = node.right ? new AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(node.right)) : nullptr;
	return;
}

template <class T>
void AVLTreeNode<T>::move(BinarySearchTreeNode<T>&& node) {
	std::cout << "AVL move\n";
	this->data = std::move(node.data);
	this->counter = std::move(node.counter);
	this->height = std::move((dynamic_cast<const AVLTreeNode<T>*>(&node))->height);
	//this->left = std::move(dynamic_cast<AVLTreeNode<T>*>(node.left));
	//this->right = std::move(dynamic_cast<AVLTreeNode<T>*>(node.right));
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
	return;
}