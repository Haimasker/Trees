template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& data, size_t counter, size_t height)
	: BinarySearchTreeNode<T>(data, counter), height(height) { }

template <class T>
AVLTreeNode<T>::AVLTreeNode(const BinarySearchTreeNode<T>& node)
	: BinarySearchTreeNode<T>() {
	if (typeid(*this) == typeid(node)) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(&node));
	}
}

template<class T>
AVLTreeNode<T>::AVLTreeNode(BinarySearchTreeNode<T>&& node)
	: BinarySearchTreeNode<T>() {
	if (typeid(*this) == typeid(node)) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(std::move(*dynamic_cast<AVLTreeNode<T>*>(&node)));
	}
}

template <class T>
AVLTreeNode<T>::AVLTreeNode(const AVLTreeNode<T>& node)
	: BinarySearchTreeNode<T>() {
	copy(node);
}

template<class T>
AVLTreeNode<T>::AVLTreeNode(AVLTreeNode<T>&& node)
	: BinarySearchTreeNode<T>() {
	move(std::move(node));
}

template <class T>
AVLTreeNode<T>::~AVLTreeNode() { }

template <class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (const BinarySearchTreeNode<T>& node) {
	if (typeid(*this) == typeid(node) && this != &node) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(&node));
	}
	return *this;
}

template <class T>
AVLTreeNode<T>& AVLTreeNode<T>::operator = (BinarySearchTreeNode<T>&& node) {
	if (typeid(*this) == typeid(node) && this != &node) {
		this->~AVLTreeNode();
		new(this) AVLTreeNode<T>(std::move(*dynamic_cast<AVLTreeNode<T>*>(&node)));
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
	return dynamic_cast<AVLTreeNode<T>*>(this->left);
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::getRight() const {
	return dynamic_cast<AVLTreeNode<T>*>(this->right);
}

template <class T>
size_t AVLTreeNode<T>::getHeight() const {
	return this->height;
}

template <class T>
void AVLTreeNode<T>::setHeight(const size_t height) {
	this->height = height;
	return;
}

template <class T>
void AVLTreeNode<T>::copy(const BinarySearchTreeNode<T>& node) {
	this->data = node.data;
	this->counter = node.counter;
	this->height = (dynamic_cast<const AVLTreeNode<T>*>(&node))->height;
	this->left = node.left ? new AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(node.left)) : nullptr;
	this->right = node.right ? new AVLTreeNode<T>(*dynamic_cast<const AVLTreeNode<T>*>(node.right)) : nullptr;
	return;
}

template <class T>
void AVLTreeNode<T>::move(BinarySearchTreeNode<T>&& node) {
	this->data = std::move(node.data);
	this->counter = std::move(node.counter);
	this->height = std::move((dynamic_cast<const AVLTreeNode<T>*>(&node))->height);
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
	return;
}

template <class T>
bool AVLTreeNode<T>::isEqual(const BinarySearchTreeNode<T>* node1, const BinarySearchTreeNode<T>* node2) const {
	if (!node1 && !node2)
		return true;
	if ((!node1 && node2) || (node1 && !node2))
		return false;
	if (typeid(*node1) != typeid(*node2))
		return false;
	const AVLTreeNode<T>* avl1 = dynamic_cast<const AVLTreeNode<T>*>(node1);
	const AVLTreeNode<T>* avl2 = dynamic_cast<const AVLTreeNode<T>*>(node2);
	if (avl1->data != avl2->data || avl1->counter != avl2->counter || avl1->height != avl2->height)
		return false;
	return (isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right));
}

template <class T>
AVLTree<T>::AVLTree()
	: BinarySearchTree<T>() { }

template <class T>
AVLTree<T>::AVLTree(const BinarySearchTree<T>& tree)
	: BinarySearchTree<T>() {
	if (typeid(*this) == typeid(tree)) {
		this->~AVLTree();
		new(this) AVLTree<T>(*dynamic_cast<const AVLTree<T>*>(&tree));
	}
}

template <class T>
AVLTree<T>::AVLTree(BinarySearchTree<T>&& tree)
	: BinarySearchTree<T>() {
	if (typeid(*this) == typeid(tree)) {
		this->~AVLTree();
		new(this) AVLTree<T>(std::move(*dynamic_cast<AVLTree<T>*>(&tree)));
	}
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
	: BinarySearchTree<T>() {
	this->root = tree.root ? new AVLTreeNode<T>(*dynamic_cast<AVLTreeNode<T>*>(tree.root)) : nullptr;
	this->size_ = tree.size_;
	this->capacity_ = tree.capacity_;
}

template <class T>
AVLTree<T>::AVLTree(AVLTree<T>&& tree)
	: BinarySearchTree<T>() {
	this->root = std::exchange(tree.root, nullptr);
	this->size_ = std::exchange(tree.size_, 0);
	this->capacity_ = std::exchange(tree.capacity_, 0);
}

template <class T>
AVLTree<T>::~AVLTree() { }

template <class T>
AVLTree<T>& AVLTree<T>::operator = (const BinarySearchTree<T>& tree) {
	if (typeid(*this) == typeid(tree) && this != &tree) {
		this->~AVLTree();
		new(this) AVLTree<T>(*dynamic_cast<const AVLTree<T>*>(&tree));
	}
	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator = (BinarySearchTree<T>&& tree) {
	if (typeid(*this) == typeid(tree) && this != &tree) {
		this->~AVLTree();
		new(this) AVLTree<T>(std::move(*dynamic_cast<AVLTree<T>*>(&tree)));
	}
	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator = (const AVLTree<T>& tree) {
	if (this != &tree) {
		this->~AVLTree();
		new(this) AVLTree<T>(tree);
	}
	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator = (AVLTree<T>&& tree) {
	if (this != &tree) {
		this->~AVLTree();
		new(this) AVLTree<T>(std::move(tree));
	}
	return *this;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(const T& data) const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::search(data));
}

template <class T>
void AVLTree<T>::insert(const T& data, size_t counter) {
	if (!this->root) {
		this->root = new AVLTreeNode<T>(data, counter);
		this->size_ = counter;
		this->capacity_ = 1;
		return;
	}
	BinarySearchTreeNode<T>** current = &(this->root);
	std::vector<BinarySearchTreeNode<T>**> path;

	while (current) {
		path.push_back(current);
		if (data < (*current)->data) {
			if (!(*current)->left) {
				(*current)->left = new AVLTreeNode<T>(data, counter);
				path.push_back(&((*current)->left));
				break;
			}
			current = &((*current)->left);
		}
		else if (data > (*current)->data) {
			if (!(*current)->right) {
				(*current)->right = new AVLTreeNode<T>(data, counter);
				path.push_back(&((*current)->right));
				break;
			}
			current = &((*current)->right);
		}
		else {
			(*current)->counter += counter;
			this->size_ += counter;
			return;
		}
	}
	this->size_ += counter;
	this->capacity_++;
	balancePath(path);
	return;
}

template <class T>
size_t AVLTree<T>::removeAll(const T& data) {
	if (!this->root)
		return 0;
	BinarySearchTreeNode<T>** toDelete = &(this->root);
	std::vector<BinarySearchTreeNode<T>**> path;

	while (*toDelete && (*toDelete)->data != data) {
		path.push_back(toDelete);
		toDelete = (data < (*toDelete)->data) ? &((*toDelete)->left) : &((*toDelete)->right);
	}
	if (!(*toDelete))
		return 0;
	path.push_back(toDelete);
	size_t deletedCount = (*toDelete)->counter;

	if ((*toDelete)->left && (*toDelete)->right) {
		AVLTreeNode<T>* successor = getMin((*toDelete)->right);
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
		delete dynamic_cast<AVLTreeNode<T>*>(*toDelete);
		*toDelete = std::move(dynamic_cast<AVLTreeNode<T>*>(tmpNode));
	}
	path.pop_back();
	balancePath(path);
	this->size_ -= deletedCount;
	this->capacity_--;
	return deletedCount;
}

template <class T>
AVLTree<T> AVLTree<T>::operator + (const T& data) const {
	AVLTree<T> result = *this;
	result.insert(data);
	return result;
}

template <class T>
AVLTree<T> AVLTree<T>::operator - (const T& data) const {
	AVLTree<T> result = *this;
	result.remove(data);
	return result;
}

template <class T>
AVLTree<T> AVLTree<T>::operator + (const BinarySearchTree<T>& tree) const {
	AVLTree<T> result = *this;
	if (typeid(*this) == typeid(tree))
		result.BinarySearchTree<T>::insert(tree.root);
	return result;
}

template <class T>
AVLTree<T> AVLTree<T>::operator - (const BinarySearchTree<T>& tree) const {
	AVLTree<T> result = *this;
	if (typeid(*this) == typeid(tree))
		result.BinarySearchTree<T>::remove(tree.root);
	return result;
}

template <class T>
size_t AVLTree<T>::height(BinarySearchTreeNode<T>* const node) const {
	return (!node) ? 0 : dynamic_cast<AVLTreeNode<T>*>(node)->height;
}

template <class T>
size_t AVLTree<T>::height() const {
	return this->getRoot()->height;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getMin() const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::getMin(this->root));
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getMax() const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::getMax(this->root));
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getPredecessor(const T& data) const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::getPredecessor(data));
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getSuccessor(const T& data) const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::getSuccessor(data));
}

template <class T>
std::vector<AVLTreeNode<T>*> AVLTree<T>::preorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::preorderDFS();
	std::vector<AVLTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<AVLTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<AVLTreeNode<T>*> AVLTree<T>::inorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::inorderDFS();
	std::vector<AVLTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<AVLTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<AVLTreeNode<T>*> AVLTree<T>::postorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::postorderDFS();
	std::vector<AVLTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<AVLTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<AVLTreeNode<T>*> AVLTree<T>::leftBFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::leftBFS();
	std::vector<AVLTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<AVLTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<AVLTreeNode<T>*> AVLTree<T>::rightBFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::rightBFS();
	std::vector<AVLTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<AVLTreeNode<T>*>(node));
	return result;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getRoot() const {
	return dynamic_cast<AVLTreeNode<T>*>(this->root);
}

template <class T>
int AVLTree<T>::balanceFactor(AVLTreeNode<T>* node) const {
	if (!node)
		return 0;
	return (node->left ? node->getLeft()->height : 0) - (node->right ? node->getRight()->height : 0);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* node) {
	AVLTreeNode<T>* newNode = dynamic_cast<AVLTreeNode<T>*>(node->right);
	node->right = nullptr;
	node->right = newNode->left;
	newNode->left = nullptr;
	newNode->left = node;
	updateHeights(node);
	updateHeights(newNode);
	return newNode;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>* node) {
	AVLTreeNode<T>* newNode = dynamic_cast<AVLTreeNode<T>*>(node->left);
	node->left = nullptr;
	node->left = newNode->right;
	newNode->right = nullptr;
	newNode->right = node;
	updateHeights(node);
	updateHeights(newNode);
	return newNode;
}

template <class T>
void AVLTree<T>::updateHeights(AVLTreeNode<T>* node) {
	node->height = std::max(node->left ? node->getLeft()->height : 0, node->right ? node->getRight()->height : 0) + 1;
	return;
}

template <class T>
void AVLTree<T>::balancePath(std::vector<BinarySearchTreeNode<T>**> path) {
	std::reverse(path.begin(), path.end());
	for (BinarySearchTreeNode<T>** current: path) {
		updateHeights(dynamic_cast<AVLTreeNode<T>*>(*current));
		if (balanceFactor(dynamic_cast<AVLTreeNode<T>*>(*current)) >= 2 && balanceFactor(dynamic_cast<AVLTreeNode<T>*>((*current)->left)) >= 1)
			*current = rightRotation(dynamic_cast<AVLTreeNode<T>*>(*current));
		else if (balanceFactor(dynamic_cast<AVLTreeNode<T>*>(*current)) >= 2) {
			(*current)->left = leftRotation(dynamic_cast<AVLTreeNode<T>*>((*current)->left));
			*current = rightRotation(dynamic_cast<AVLTreeNode<T>*>(*current));
		}
		else if (balanceFactor(dynamic_cast<AVLTreeNode<T>*>(*current)) <= -2 && balanceFactor(dynamic_cast<AVLTreeNode<T>*>((*current)->right)) <= -1)
			*current = leftRotation(dynamic_cast<AVLTreeNode<T>*>(*current));
		else if (balanceFactor(dynamic_cast<AVLTreeNode<T>*>(*current)) <= -2) {
			(*current)->right = rightRotation(dynamic_cast<AVLTreeNode<T>*>((*current)->right));
			*current = leftRotation(dynamic_cast<AVLTreeNode<T>*>(*current));
		}
	}
	return;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getMin(BinarySearchTreeNode<T>* const node) const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::getMin(node));
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::getMax(BinarySearchTreeNode<T>* const node) const {
	return dynamic_cast<AVLTreeNode<T>*>(BinarySearchTree<T>::getMax(node));
}