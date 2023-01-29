template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const T& data, size_t counter)
	: data(data), counter(counter), left(nullptr), right(nullptr) { }

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(const BinarySearchTreeNode<T>& node) {
	this->copy(node);
}

template<class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(BinarySearchTreeNode<T>&& node) {
	this->move(std::move(node));
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
bool BinarySearchTreeNode<T>::operator == (const BinarySearchTreeNode<T>& node) const {
	return ((this == &node) || isEqual(this, &node));
}

template <class T>
bool BinarySearchTreeNode<T>::operator != (const BinarySearchTreeNode<T>& node) const {
	return !(*this == node);
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
	this->data = node.data;
	this->counter = node.counter;
	this->left = node.left ? new BinarySearchTreeNode<T>(*node.left) : nullptr;
	this->right = node.right ? new BinarySearchTreeNode<T>(*node.right) : nullptr;
	return;
}

template <class T>
void BinarySearchTreeNode<T>::move(BinarySearchTreeNode<T>&& node) {
	this->data = std::move(node.data);
	this->counter = std::move(node.counter);
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
	return;
}

template <class T>
bool BinarySearchTreeNode<T>::isEqual(const BinarySearchTreeNode<T>* node1, const BinarySearchTreeNode<T>* node2) const {
	if ((node1 == node2) || (!node1 && !node2))
		return true;
	if ((!node1 && node2) || (node1 && !node2))
		return false;
	if (typeid(*node1) != typeid(*node2))
		return false;
	if (node1->data != node2->data || node1->counter != node2->counter)
		return false;
	return (isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right));
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
		new(this) BinarySearchTree<T>(tree);
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
bool BinarySearchTree<T>::operator == (const BinarySearchTree<T>& tree) const {
	if (this == &tree)
		return true;
	if (this->size_ != tree.size_ || this->capacity_ != tree.capacity_)
		return false;
	return (*(this->root) == *(tree.root));
}

template <class T>
bool BinarySearchTree<T>::operator != (const BinarySearchTree<T>& tree) const {
	return !(*this == tree);
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
			if (!current->left) {
				current->left = new BinarySearchTreeNode<T>(data, counter);
				break;
			}
			current = current->left;
		}
		else if (data > current->data) {
			if (!current->right) {
				current->right = new BinarySearchTreeNode<T>(data, counter);
				break;
			}
			current = current->right;
		}
		else {
			current->counter += counter;
			this->size_ += counter;
			return;
		}
	}
	this->size_ += counter;
	this->capacity_++;
	return;
}

template <class T>
size_t BinarySearchTree<T>::remove(const T& data, size_t counter) {
	BinarySearchTreeNode<T>* toDelete = search(data);
	if (!toDelete)
		return 0;
	if (counter >= toDelete->counter)
		return removeAll(data);
	toDelete->counter -= counter;
	this->size_ -= counter;
	return counter;
}

template <class T>
size_t BinarySearchTree<T>::removeAll(const T& data) {
	if (!this->root)
		return 0;
	BinarySearchTreeNode<T>** toDelete = &(this->root);

	while (*toDelete && (*toDelete)->data != data)
		toDelete = (data < (*toDelete)->data) ? &((*toDelete)->left) : &((*toDelete)->right);
	if (!(*toDelete))
		return 0;
	size_t deletedCount = (*toDelete)->counter;

	if ((*toDelete)->left && (*toDelete)->right) {
		BinarySearchTreeNode<T>* successor = getMin((*toDelete)->right);
		T tmpData = successor->data;
		size_t tmpCounter = successor->counter;
		size_t tmpDeleted = removeAll(successor->data);
		(*toDelete)->data = tmpData;
		(*toDelete)->counter = tmpCounter;
		this->size_ = this->size_ - deletedCount + tmpDeleted;
		return deletedCount;
	}
	else if (!(*toDelete)->left && !(*toDelete)->right) {
		delete *toDelete;
		*toDelete = nullptr;
	}
	else {
		BinarySearchTreeNode<T>* tmpNode = (!(*toDelete)->left) ? (*toDelete)->right : (*toDelete)->left;
		((!(*toDelete)->left) ? (*toDelete)->right : (*toDelete)->left) = nullptr;
		delete *toDelete;
		*toDelete = std::move(tmpNode);
	}
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
BinarySearchTree<T> BinarySearchTree<T>::operator - (const T& data) const {
	BinarySearchTree<T> result = *this;
	result.remove(data);
	return result;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator += (const T& data) {
	insert(data);
	return *this;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator -= (const T& data) {
	remove(data);
	return *this;
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator + (const BinarySearchTree<T>& tree) const {
	BinarySearchTree<T> result = *this;
	result.insert(tree.root);
	return result;
}

template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator - (const BinarySearchTree<T>& tree) const {
	BinarySearchTree<T> result = *this;
	result.remove(tree.root);
	return result;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator += (const BinarySearchTree<T>& tree) {
	this->insert(tree.root);
	return *this;
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
	return height(this->root);
}

template <class T>
bool BinarySearchTree<T>::contains(const T& data) const {
	return search(data);
}

template <class T>
size_t BinarySearchTree<T>::count(const T& data) const {
	BinarySearchTreeNode<T>* node = search(data);
	return (node ? node->counter : 0);
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMin() const {
	return getMin(this->root);
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getMax() const {
	return getMax(this->root);
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::preorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	preorderDFS(this->root, result);
	return result;
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::inorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	inorderDFS(this->root, result);
	return result;
}

template <class T>
std::vector<BinarySearchTreeNode<T>*> BinarySearchTree<T>::postorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> result;
	postorderDFS(this->root, result);
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
	this->~BinarySearchTree();
}

template <class T>
void BinarySearchTree<T>::insert(const BinarySearchTreeNode<T>* node) {
	if (node) {
		insert(node->data, node->counter);
		insert(node->left);
		insert(node->right);
	}
	return;
}

template <class T>
void BinarySearchTree<T>::remove(const BinarySearchTreeNode<T>* node) {
	if (node) {
		remove(node->data, node->counter);
		remove(node->left);
		remove(node->right);
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