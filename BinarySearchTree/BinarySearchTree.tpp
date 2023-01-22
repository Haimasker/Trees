#include <iostream>

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const T& data, size_t counter)
	: data(data), counter(counter), left(nullptr), right(nullptr) {
	std::cout << "BST data ctor\n";
}

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const BinarySearchTreeNode<T>& node) {
	std::cout << "BST copy ctor\n";
	this->copy(node);
}

template<class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(BinarySearchTreeNode<T>&& node) {
	std::cout << "BST move ctor\n";
	this->move(std::move(node));
}

template <class T>
BinarySearchTreeNode<T>::~BinarySearchTreeNode() {
	std::cout << "BST dtor\n";
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
void BinarySearchTreeNode<T>::copy(const BinarySearchTreeNode<T>& node) {
	std::cout << "BST copy\n";
	this->data = node.data;
	this->counter = node.counter;
	this->left = node.left ? new BinarySearchTreeNode<T>(*node.left) : nullptr;
	this->right = node.right ? new BinarySearchTreeNode<T>(*node.right) : nullptr;
	return;
}

template <class T>
void BinarySearchTreeNode<T>::move(BinarySearchTreeNode<T>&& node) {
	std::cout << "BST move\n";
	this->data = std::move(node.data);
	this->counter = std::move(node.counter);
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
	return;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree()
	: root(nullptr), size_(0), capacity_(0) { }

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
	if (this->root) {
		delete this->root;
		this->size_ = this->capacity_ = 0;
		this->root = nullptr;
	}
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
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(const T& data) const {
	BinarySearchTreeNode<T>* current = this->root;
	while (current && current->data != data)
		current = (data < current->data) ? current->left : current->right;
	return current;
}

template <class T>
void BinarySearchTree<T>::insert(const T& data, size_t counter) {
	if (!this->root) {
		this->root = new BinarySearchTreeNode<T>(data, counter);
		this->size_ = counter;
		this->capacity_ = 1;
		return;
	}
	BinarySearchTreeNode<T>* current = root;
	while (current) {
		if (data < current->data) {
			if (current->left)
				current = current->left;
			else {
				current->left = new BinarySearchTreeNode<T>(data, counter);
				this->size_ += counter;
				this->capacity_++;
				break;
			}
		}
		else if (data > current->data) {
			if (current->right)
				current = current->right;
			else {
				current->right = new BinarySearchTreeNode<T>(data, counter);
				this->size_ += counter;
				this->capacity_++;
				break;
			}
		}
		else {
			current->counter += counter;
			this->size_ += counter;
			break;
		}
	}
	return;
}

template <class T>
size_t BinarySearchTree<T>::remove(const T& data, size_t counter) {
	if (!this->root)
		return 0;

	BinarySearchTreeNode<T>* toDelete = this->search(data);
	if (!toDelete)
		return 0;

	size_t deletedCount = std::min(toDelete->counter, counter);

	if (counter >= toDelete->counter)
		return this->removeAll(data);
	toDelete->counter -= counter;
	this->size_ -= deletedCount;
	return deletedCount;
}

template <class T>
size_t BinarySearchTree<T>::removeAll(const T& data) {
	if (!this->root)
		return 0;

	BinarySearchTreeNode<T>* previous = findPreviousNode(data);
	if (!previous && data != this->root->data)
		return 0;

	BinarySearchTreeNode<T>* toDelete = this->root;
	if (previous && previous->left && previous->left->data == data)
		toDelete = previous->left;
	else if (previous && previous->right && previous->right->data == data)
		toDelete = previous->right;

	size_t deletedCount = toDelete->counter;

	if (toDelete->left && toDelete->right) {
		BinarySearchTreeNode<T>* tmpNode = getMin(toDelete->right);
		T tmpData = tmpNode->data;
		size_t tmpCounter = tmpNode->counter;
		size_t tmpDeleted = this->removeAll(tmpNode->data);
		toDelete->data = tmpData;
		toDelete->counter = tmpCounter;
		this->size_ = this->size_ - deletedCount + tmpDeleted;
		return deletedCount;
	}
	else if (!toDelete->left && !toDelete->right) {
		if (!previous) {
			this->clear();
			return deletedCount;
		}
		((previous->left == toDelete) ? previous->left : previous->right) = nullptr;
	}
	else if (!toDelete->left) {
		BinarySearchTreeNode<T>* tmpNode = toDelete->right;
		toDelete->right = nullptr;
		if (!previous)
			this->root = std::move(tmpNode);
		else
			((previous->left == toDelete) ? previous->left : previous->right) = std::move(tmpNode);
	}
	else {
		BinarySearchTreeNode<T>* tmpNode = toDelete->left;
		toDelete->left = nullptr;
		if (!previous)
			this->root = std::move(tmpNode);
		else
			((previous->left == toDelete) ? previous->left : previous->right) = std::move(tmpNode);
	}
	delete toDelete;
	this->size_ -= deletedCount;
	this->capacity_--;
	return deletedCount;
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator + (const T& data) const {
	BinarySearchTree<T> result = *this;
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
	BinarySearchTree<T> result = *this;
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
	BinarySearchTree<T> result = *this;
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
	BinarySearchTree<T> result = *this;
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
	*this += tree;
	return;
}

template <class T>
void BinarySearchTree<T>::exclude(const BinarySearchTree<T>& tree) {
	*this -= tree;
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
size_t BinarySearchTree<T>::height(BinarySearchTreeNode<T>* const node) const {
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
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMin() const {
	return this->getMin(this->root);
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMax() const {
	return this->getMax(this->root);
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::preorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	this->preorderDFS(this->root, result);
	return result;
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::inorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	this->inorderDFS(this->root, result);
	return result;
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::postorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	this->postorderDFS(this->root, result);
	return result;
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::leftBFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	if (!this->root)
		return result;
	std::queue<BinarySearchTreeNode<T>*> q;
	q.push(this->root);
	while (!q.empty()) {
		BinarySearchTreeNode<T>* tmpNode = q.front();
		q.pop();
		result.push_back(tmpNode);
		if (tmpNode->left)
			q.push(tmpNode->left);
		if (tmpNode->right)
			q.push(tmpNode->right);
	}
	return result;
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::rightBFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	if (!this->root)
		return result;
	std::queue<BinarySearchTreeNode<T>*> q;
	q.push(this->root);
	while (!q.empty()) {
		BinarySearchTreeNode<T>* tmpNode = q.front();
		q.pop();
		result.push_back(tmpNode);
		if (tmpNode->right)
			q.push(tmpNode->right);
		if (tmpNode->left)
			q.push(tmpNode->left);
	}
	return result;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getRoot() const {
	return this->root;
}

template <class T>
void BinarySearchTree<T>::clear() {
	this->~BinarySearchTree<T>();
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::findPreviousNode(const T& data) const {
	BinarySearchTreeNode<T>* current = this->root;
	while (current) {
		if ((current->left && current->left->data == data) || (current->right && current->right->data == data))
			break;
		current = (data < current->data) ? current->left : current->right;
	}
	return current;
}

template <class T>
void BinarySearchTree<T>::insert(const BinarySearchTreeNode<T>* node) {
	if (node) {
		this->insert(node->data, node->counter);
		this->insert(node->left);
		this->insert(node->right);
	}
	return;
}

template <class T>
void BinarySearchTree<T>::remove(const BinarySearchTreeNode<T>* node) {
	if (node) {
		this->remove(node->data, node->counter);
		this->remove(node->left);
		this->remove(node->right);
	}
	return;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMin(BinarySearchTreeNode<T>* const node) const {
	if (!node)
		return nullptr;
	BinarySearchTreeNode<T>* current = node;
	while (current->left)
		current = current->left;
	return current;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMax(BinarySearchTreeNode<T>* const node) const {
	if (!node)
		return nullptr;
	BinarySearchTreeNode<T>* current = node;
	while (current->right)
		current = current->right;
	return current;
}

template <class T>
void BinarySearchTree<T>::preorderDFS(BinarySearchTreeNode<T>* const node, std::vector<BinarySearchTreeNode<T>*>& result) const {
	if (!node)
		return;
	result.push_back(node);
	preorderDFS(node->left, result);
	preorderDFS(node->right, result);
	return;
}

template <class T>
void BinarySearchTree<T>::inorderDFS(BinarySearchTreeNode<T>* const node, std::vector<BinarySearchTreeNode<T>*>& result) const {
	if (!node)
		return;
	inorderDFS(node->left, result);
	result.push_back(node);
	inorderDFS(node->right, result);
	return;
}

template <class T>
void BinarySearchTree<T>::postorderDFS(BinarySearchTreeNode<T>* const node, std::vector<BinarySearchTreeNode<T>*>& result) const {
	if (!node)
		return;
	postorderDFS(node->left, result);
	postorderDFS(node->right, result);
	result.push_back(node);
	return;
}