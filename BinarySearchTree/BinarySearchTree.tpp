//#include "BinarySearchTree.hpp"
#include <iostream>

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const T& data, size_t counter)
	: data(data), counter(counter), left(nullptr), right(nullptr) { }

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const BinarySearchTreeNode<T>& node)
	: data(node.data), counter(node.counter) {
	this->left = node.left ? new BinarySearchTreeNode<T>(*node.left) : nullptr;
	this->right = node.right ? new BinarySearchTreeNode<T>(*node.right) : nullptr;
}

template<class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(BinarySearchTreeNode<T>&& node)
	: data(std::move(node.data)), counter(std::move(node.counter)) {
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
}

template <class T>
BinarySearchTreeNode<T>::~BinarySearchTreeNode() {
	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;
	this->counter = 0;
}

template <class T>
BinarySearchTreeNode<T>& BinarySearchTreeNode<T>::operator = (const BinarySearchTreeNode<T>& node) {
	if (this != &node) {
		this->~BinarySearchTreeNode();
		new(this) BinarySearchTreeNode<T>(node);
	}
	return *this;
}

template <class T>
BinarySearchTreeNode<T>& BinarySearchTreeNode<T>::operator = (BinarySearchTreeNode<T>&& node) {
	if (this != &node) {
		this->~BinarySearchTreeNode();
		new(this) BinarySearchTreeNode<T>(std::move(node));
	}
	return *this;
}

template <class T>
T BinarySearchTreeNode<T>::getData() const {
	return this->data;
}

template <class T>
void BinarySearchTreeNode<T>::setData(const T& data) {
	this->data = data;
	return;
}

template <class T>
size_t BinarySearchTreeNode<T>::getCounter() const {
	return this->counter;
}

template <class T>
void BinarySearchTreeNode<T>::setCounter(const size_t counter) {
	this->counter = counter;
	return;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTreeNode<T>::getLeft() const {
	return this->left;
}

template <class T>
void BinarySearchTreeNode<T>::setLeft(BinarySearchTreeNode<T>* node) {
	this->left = node;
	return;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTreeNode<T>::getRight() const {
	return this->right;
}

template <class T>
void BinarySearchTreeNode<T>::setRight(BinarySearchTreeNode<T>* node) {
	this->right = node;
	return;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree()
	: root(nullptr), size_(0), capacity_(0) { }

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTreeNode<T>* node)
	: root(node), size_(countSize(node)), capacity_(countCapacity(node)) { }

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree)
	: root(tree.root ? new BinarySearchTreeNode<T>(*tree.root) : nullptr),
	size_(tree.size_), capacity_(tree.capacity_) { }

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& tree)
	: root(std::exchange(tree.root, nullptr)),
	size_(std::exchange(tree.size_, 0)),
	capacity_(std::exchange(tree.capacity_, 0)) { }

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	if (this->root)
		delete this->root;
	this->size_ = this->capacity_ = 0;
	//this->root = nullptr;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator = (const BinarySearchTree<T>& tree) {
	if (this != &tree) {
		this->~BinarySearchTree();
		new(this) BinarySearchTree(tree);
	}
	return *this;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator = (BinarySearchTree<T>&& tree) {
	if (this != &tree) {
		this->~BinarySearchTree();
		new(this) BinarySearchTree<T>(std::move(tree));
	}
	return *this;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(const T& data, const BinarySearchTreeNode<T>* node) const {
	BinarySearchTreeNode<T>* current = node;
	while (current) {
		if (current->data = data)
			return current;
		current = (data < current->data) ? current->left : current->right;
	}
	return current;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(const T& data) const {
	return this->search(data, this->root);
}

template <class T>
void BinarySearchTree<T>::insert(const T& data, size_t counter) {
	BinarySearchTreeNode<T>* current = this->search(data);
	this->size_ += counter;
	if (current)
		current->counter += counter;
	else {
		this->capacity_++;
		current = new BinarySearchTreeNode<T>(data, counter);
	}
	return;
}

template <class T>
size_t BinarySearchTree<T>::remove(const T& data, const BinarySearchTreeNode<T>* node, size_t counter) {
	BinarySearchTreeNode<T>* current = this->search(data, node);
	if (!current)
		return 0;

	size_t deletedCount = std::min(current->counter, counter);
	this->size_ -= deletedCount;
	this->capacity_ -= (counter >= current->counter) ? 1 : 0;

	if (counter < current->counter)
		current->counter -= counter;
	else {
		if (!current->left && !current->right)
			delete current;
		else if(!current->left)
			current = current->right;
		else if(!current->right)
			current = current->left;
		else {
			BinarySearchTreeNode<T>* tmpNode = getMin(current->right);
			current->data = tmpNode->data;
			current->counter = tmpNode->counter;
			this->removeAll(tmpNode->data, current->right);
		}
	}
	return deletedCount;
}

template <class T>
size_t BinarySearchTree<T>::remove(const T& data, size_t counter) {
	return this->remove(data, this->root, counter);
}

template <class T>
size_t BinarySearchTree<T>::removeAll(const T& data, const BinarySearchTreeNode<T>* node) {
	BinarySearchTreeNode<T>* current = this->search(data, node);
	if (!current)
		return 0;

	size_t deletedCount = current->counter;
	this->size_ -= deletedCount;
	this->capacity_--;

	if (!current->left && !current->right)
		delete current;
	else if(!current->left)
		current = current->right;
	else if(!current->right)
		current = current->left;
	else {
		BinarySearchTreeNode<T>* tmpNode = getMin(current->right);
		current->data = tmpNode->data;
		current->counter = tmpNode->counter;
		this->removeAll(tmpNode->data, current->right);
	}
	return deletedCount;
}

template <class T>
size_t BinarySearchTree<T>::removeAll(const T& data) {
	return this->removeAll(data, this->root);
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator + (const T& data) const {
	BinarySearchTree<T> result = this;
	result.insert(data);
	return result;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator += (const T& data) {
	this->insert(data);
	return *this;
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator - (const T& data) const {
	BinarySearchTree<T> result = this;
	result.remove(data);
	return result;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator -= (const T& data) {
	this->remove(data);
	return *this;
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator + (const BinarySearchTree<T>& tree) const {
	BinarySearchTree<T> result = this;
	result.insert(tree.root);
	return result;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator += (const BinarySearchTree<T>& tree) {
	this->insert(tree.root);
	return *this;
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator - (const BinarySearchTree<T>& tree) const {
	BinarySearchTree<T> result = this;
	result.remove(tree.root);
	return result;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator -= (const BinarySearchTree<T>& tree) {
	this->remove(tree.root);
	return *this;
}

template <class T>
void BinarySearchTree<T>::merge(const BinarySearchTree<T>& tree) {
	this += tree;
	return;
}

template <class T>
void BinarySearchTree<T>::exclude(const BinarySearchTree<T>& tree) {
	this -= tree;
	return;
}

template <class T>
bool BinarySearchTree<T>::empty() const {
	return (this->size_ == 0);
}

template <class T>
size_t BinarySearchTree<T>::size() const {
	return this->size_;
}

template <class T>
size_t BinarySearchTree<T>::capacity() const {
	return this->capacity_;
}

template <class T>
size_t BinarySearchTree<T>::height(const BinarySearchTreeNode<T>* node) const {
	return (!node) ? 0 : std::max(this->height(node->left), this->height(node->right)) + 1;
}

template <class T>
size_t BinarySearchTree<T>::height() const {
	return this->height(this->root);
}

template <class T>
bool BinarySearchTree<T>::contains(const T& data) const {
	return this->search(data);
}

template <class T>
size_t BinarySearchTree<T>::count(const T& data) const {
	BinarySearchTreeNode<T>* node = this->search(data);
	return (node) ? node->counter : 0;
}






template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMin(const BinarySearchTreeNode<T>* node) const {
	BinarySearchTreeNode<T>* current = node;
	while (current->left)
		current = current->left;
	return current;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMin() const {
	return this->getMin(this->root);
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMax(const BinarySearchTreeNode<T>* node) const {
	BinarySearchTreeNode<T>* current = node;
	while (current->right)
		current = current->right;
	return current;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMax() const {
	return this->getMax(this->root);
}

template <class T>
size_t BinarySearchTree<T>::countSize(const BinarySearchTreeNode<T>* node) const {
	if (!node)
		return 0;
	return node->counter + countSize(node->left) + countSize(node->right);
}

template <class T>
size_t BinarySearchTree<T>::countSize() const {
	return this->countSize(this->root);
}

template <class T>
size_t BinarySearchTree<T>::countCapacity(const BinarySearchTreeNode<T>* node) const {
	if (!node)
		return 0;
	return 1 + countCapacity(node->left) + countCapacity(node->right);
}

template <class T>
size_t BinarySearchTree<T>::countCapacity() const {
	return this->countCapacity(this->root);
}





template <class T>
void BinarySearchTree<T>::insert(const BinarySearchTreeNode<T>* node) {
	if (node) {
		this += node->data;
		this->insert(node->left);
		this->insert(node->right);
	}
	return;
}

template <class T>
void BinarySearchTree<T>::remove(const BinarySearchTreeNode<T>* node) {
	if (node) {
		this -= node->data;
		this->remove(node->left);
		this->remove(node->right);
	}
	return;
}