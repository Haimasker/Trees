template <class T>
RBTreeNode<T>::RBTreeNode(const T& data, size_t counter, NodeColor color)
	: BinarySearchTreeNode<T>(data, counter),
	parent(nullptr), color(color) { }

template <class T>
RBTreeNode<T>::RBTreeNode(const BinarySearchTreeNode<T>& node)
	: BinarySearchTreeNode<T>() {
	if (typeid(*this) == typeid(node)) {
		this->~RBTreeNode();
		new(this) RBTreeNode<T>(*dynamic_cast<const RBTreeNode<T>*>(&node));
	}
}

template<class T>
RBTreeNode<T>::RBTreeNode(BinarySearchTreeNode<T>&& node)
	: BinarySearchTreeNode<T>() {
	if (typeid(*this) == typeid(node)) {
		this->~RBTreeNode();
		new(this) RBTreeNode<T>(std::move(*dynamic_cast<RBTreeNode<T>*>(&node)));
	}
}

template <class T>
RBTreeNode<T>::RBTreeNode(const RBTreeNode<T>& node)
	: BinarySearchTreeNode<T>() {
	copy(node);
}

template<class T>
RBTreeNode<T>::RBTreeNode(RBTreeNode<T>&& node)
	: BinarySearchTreeNode<T>() {
	move(std::move(node));
}

template <class T>
RBTreeNode<T>::~RBTreeNode() { }

template <class T>
RBTreeNode<T>& RBTreeNode<T>::operator = (const BinarySearchTreeNode<T>& node) {
	if (typeid(*this) == typeid(node) && this != &node) {
		this->~RBTreeNode();
		new(this) RBTreeNode<T>(*dynamic_cast<const RBTreeNode<T>*>(&node));
	}
	return *this;
}

template <class T>
RBTreeNode<T>& RBTreeNode<T>::operator = (BinarySearchTreeNode<T>&& node) {
	if (typeid(*this) == typeid(node) && this != &node) {
		this->~RBTreeNode();
		new(this) RBTreeNode<T>(std::move(*dynamic_cast<RBTreeNode<T>*>(&node)));
	}
	return *this;
}

template <class T>
RBTreeNode<T>& RBTreeNode<T>::operator = (const RBTreeNode<T>& node) {
	if (this != &node) {
		this->~RBTreeNode();
		new(this) RBTreeNode<T>(node);
	}
	return *this;
}

template <class T>
RBTreeNode<T>& RBTreeNode<T>::operator = (RBTreeNode<T>&& node) {
	if (this != &node) {
		this->~RBTreeNode();
		new(this) RBTreeNode<T>(std::move(node));
	}
	return *this;
}

template <class T>
RBTreeNode<T>* RBTreeNode<T>::getLeft() const {
	return dynamic_cast<RBTreeNode<T>*>(this->left);
}

template <class T>
bool RBTreeNode<T>::setLeft(BinarySearchTreeNode<T>* node) {
	if (typeid(*this) != typeid(*node))
		return false;
	this->left = node;
	if (this->left)
		this->getLeft()->parent = this;
	return true;
}

template <class T>
RBTreeNode<T>* RBTreeNode<T>::getRight() const {
	return dynamic_cast<RBTreeNode<T>*>(this->right);
}

template <class T>
bool RBTreeNode<T>::setRight(BinarySearchTreeNode<T>* node) {
	if (typeid(*this) != typeid(*node))
		return false;
	this->right = node;
	if (this->right)
		this->getRight()->parent = this;
	return true;
}

template <class T>
RBTreeNode<T>* RBTreeNode<T>::getParent() const {
	return dynamic_cast<RBTreeNode<T>*>(this->parent);
}

template <class T>
bool RBTreeNode<T>::setParent(BinarySearchTreeNode<T>* node) {
	if (typeid(*this) != typeid(*node))
		return false;
	this->parent = node;
	return true;
}

template <class T>
NodeColor RBTreeNode<T>::getColor() const {
	return this->color;
}

template <class T>
void RBTreeNode<T>::setColor(const NodeColor& color) {
	this->color = color;
	return;
}

template <class T>
void RBTreeNode<T>::copy(const BinarySearchTreeNode<T>& node) {
	this->data = node.data;
	this->counter = node.counter;
	this->color = (dynamic_cast<const RBTreeNode<T>*>(&node))->color;
	this->parent = (dynamic_cast<const RBTreeNode<T>*>(&node))->parent;
	this->left = node.left ? new RBTreeNode<T>(*dynamic_cast<const RBTreeNode<T>*>(node.left)) : nullptr;
	this->right = node.right ? new RBTreeNode<T>(*dynamic_cast<const RBTreeNode<T>*>(node.right)) : nullptr;
	if (this->left)
		this->getLeft()->parent = this;
	if (this->right)
		this->getRight()->parent = this;
	return;
}

template <class T>
void RBTreeNode<T>::move(BinarySearchTreeNode<T>&& node) {
	this->data = std::move(node.data);
	this->counter = std::move(node.counter);
	this->color = std::move((dynamic_cast<const RBTreeNode<T>*>(&node))->color);
	this->parent = std::move((dynamic_cast<const RBTreeNode<T>*>(&node))->parent);
	this->left = std::exchange(node.left, nullptr);
	this->right = std::exchange(node.right, nullptr);
	if (this->left)
		this->getLeft()->parent = this;
	if (this->right)
		this->getRight()->parent = this;
	return;
}

template <class T>
bool RBTreeNode<T>::isEqual(const BinarySearchTreeNode<T>* node1, const BinarySearchTreeNode<T>* node2) const {
	if (!node1 && !node2)
		return true;
	if ((!node1 && node2) || (node1 && !node2))
		return false;
	if (typeid(*node1) != typeid(*node2))
		return false;
	const RBTreeNode<T>* rb1 = dynamic_cast<const RBTreeNode<T>*>(node1);
	const RBTreeNode<T>* rb2 = dynamic_cast<const RBTreeNode<T>*>(node2);
	if (rb1->data != rb2->data || rb1->counter != rb2->counter || rb1->color != rb2->color)
		return false;
	return (isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right));
}

template <class T>
RBTree<T>::RBTree()
	: BinarySearchTree<T>() { }

template <class T>
RBTree<T>::RBTree(const BinarySearchTree<T>& tree)
	: BinarySearchTree<T>() {
	if (typeid(*this) == typeid(tree)) {
		this->~RBTree();
		new(this) RBTree<T>(*dynamic_cast<const RBTree<T>*>(&tree));
	}
}

template <class T>
RBTree<T>::RBTree(BinarySearchTree<T>&& tree)
	: BinarySearchTree<T>() {
	if (typeid(*this) == typeid(tree)) {
		this->~RBTree();
		new(this) RBTree<T>(std::move(*dynamic_cast<RBTree<T>*>(&tree)));
	}
}

template <class T>
RBTree<T>::RBTree(const RBTree<T>& tree)
	: BinarySearchTree<T>() {
	this->root = tree.root ? new RBTreeNode<T>(*dynamic_cast<RBTreeNode<T>*>(tree.root)) : nullptr;
	this->size_ = tree.size_;
	this->capacity_ = tree.capacity_;
}

template <class T>
RBTree<T>::RBTree(RBTree<T>&& tree)
	: BinarySearchTree<T>() {
	this->root = std::exchange(tree.root, nullptr);
	this->size_ = std::exchange(tree.size_, 0);
	this->capacity_ = std::exchange(tree.capacity_, 0);
}

template <class T>
RBTree<T>::~RBTree() { }

template <class T>
RBTree<T>& RBTree<T>::operator = (const BinarySearchTree<T>& tree) {
	if (typeid(*this) == typeid(tree) && this != &tree) {
		this->~RBTree();
		new(this) RBTree<T>(*dynamic_cast<const RBTree<T>*>(&tree));
	}
	return *this;
}

template <class T>
RBTree<T>& RBTree<T>::operator = (BinarySearchTree<T>&& tree) {
	if (typeid(*this) == typeid(tree) && this != &tree) {
		this->~RBTree();
		new(this) RBTree<T>(std::move(*dynamic_cast<RBTree<T>*>(&tree)));
	}
	return *this;
}

template <class T>
RBTree<T>& RBTree<T>::operator = (const RBTree<T>& tree) {
	if (this != &tree) {
		this->~RBTree();
		new(this) RBTree<T>(tree);
	}
	return *this;
}

template <class T>
RBTree<T>& RBTree<T>::operator = (RBTree<T>&& tree) {
	if (this != &tree) {
		this->~RBTree();
		new(this) RBTree<T>(std::move(tree));
	}
	return *this;
}

template <class T>
RBTreeNode<T>* RBTree<T>::search(const T& data) const {
	return dynamic_cast<RBTreeNode<T>*>(BinarySearchTree<T>::search(data));
}

template <class T>
void RBTree<T>::insert(const T& data, size_t counter) {
	if (!this->root) {
		this->root = new RBTreeNode<T>(data, counter);
		this->size_ = counter;
		this->capacity_ = 1;
		this->getRoot()->color = NodeColor::COLOR_BLACK;
		return;
	}
	BinarySearchTreeNode<T>** current = &(this->root);
	while (current) {
		if (data < (*current)->data) {
			if (!(*current)->left) {
				dynamic_cast<RBTreeNode<int>*>(*current)->setLeft(new RBTreeNode<T>(data, counter));
				current = &((*current)->left);
				break;
			}
			current = &((*current)->left);
		}
		else if (data > (*current)->data) {
			if (!(*current)->right) {
				dynamic_cast<RBTreeNode<int>*>(*current)->setRight(new RBTreeNode<T>(data, counter));
				current = &((*current)->right);
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
	fixInsert(dynamic_cast<RBTreeNode<T>*>(*current));
	return;
}

template <class T>
size_t RBTree<T>::removeAll(const T& data) {
	if (!this->root)
		return 0;
	BinarySearchTreeNode<T>** toDelete = &(this->root);
	while (*toDelete && (*toDelete)->data != data)
		toDelete = (data < (*toDelete)->data) ? &((*toDelete)->left) : &((*toDelete)->right);
	if (!(*toDelete))
		return 0;
	size_t deletedCount = (*toDelete)->counter;
	if ((*toDelete)->left && (*toDelete)->right)
		removeRedBlackTwo(*toDelete);
	else if (!(*toDelete)->left && !(*toDelete)->right)
		removeRedBlackZero(*toDelete);
	else
		removeBlackOne(*toDelete);
	this->size_ -= deletedCount;
	this->capacity_--;
	return deletedCount;
}

template <class T>
RBTree<T> RBTree<T>::operator + (const T& data) const {
	RBTree<T> result = *this;
	result.insert(data);
	return result;
}

template <class T>
RBTree<T> RBTree<T>::operator - (const T& data) const {
	RBTree<T> result = *this;
	result.remove(data);
	return result;
}

template <class T>
RBTree<T> RBTree<T>::operator + (const BinarySearchTree<T>& tree) const {
	RBTree<T> result = *this;
	if (typeid(*this) == typeid(tree))
		result.BinarySearchTree<T>::insert(tree.root);
	return result;
}

template <class T>
RBTree<T> RBTree<T>::operator - (const BinarySearchTree<T>& tree) const {
	RBTree<T> result = *this;
	if (typeid(*this) == typeid(tree))
		result.BinarySearchTree<T>::remove(tree.root);
	return result;
}

template <class T>
RBTreeNode<T>* RBTree<T>::getMin() const {
	return dynamic_cast<RBTreeNode<T>*>(BinarySearchTree<T>::getMin(this->root));
}

template <class T>
RBTreeNode<T>* RBTree<T>::getMax() const {
	return dynamic_cast<RBTreeNode<T>*>(BinarySearchTree<T>::getMax(this->root));
}

template <class T>
std::vector<RBTreeNode<T>*> RBTree<T>::preorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::preorderDFS();
	std::vector<RBTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<RBTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<RBTreeNode<T>*> RBTree<T>::inorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::inorderDFS();
	std::vector<RBTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<RBTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<RBTreeNode<T>*> RBTree<T>::postorderDFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::postorderDFS();
	std::vector<RBTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<RBTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<RBTreeNode<T>*> RBTree<T>::leftBFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::leftBFS();
	std::vector<RBTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<RBTreeNode<T>*>(node));
	return result;
}

template <class T>
std::vector<RBTreeNode<T>*> RBTree<T>::rightBFS() const {
	std::vector<BinarySearchTreeNode<T>*> tmp = BinarySearchTree<T>::rightBFS();
	std::vector<RBTreeNode<T>*> result;
	for (auto node : tmp)
		result.push_back(dynamic_cast<RBTreeNode<T>*>(node));
	return result;
}

template <class T>
RBTreeNode<T>* RBTree<T>::getRoot() const {
	return dynamic_cast<RBTreeNode<T>*>(this->root);
}

template <class T>
RBTreeNode<T>* RBTree<T>::leftRotation(RBTreeNode<T>* node) {
	RBTreeNode<T>* newNode = dynamic_cast<RBTreeNode<T>*>(node->right);
	newNode->parent = nullptr;
	node->right = nullptr;
	node->setRight(newNode->left);
	newNode->left = nullptr;
	newNode->setLeft(node);
	return newNode;
}

template <class T>
RBTreeNode<T>* RBTree<T>::rightRotation(RBTreeNode<T>* node) {
	RBTreeNode<T>* newNode = dynamic_cast<RBTreeNode<T>*>(node->left);
	newNode->parent = nullptr;
	node->left = nullptr;
	node->setLeft(newNode->right);
	newNode->right = nullptr;
	newNode->setRight(node);
	return newNode;
}

template <class T>
void RBTree<T>::removeRedBlackTwo(BinarySearchTreeNode<T>* node) {
	BinarySearchTreeNode<T>* successor = node->right;
	while (successor->left)
		successor = successor->left;
	std::swap(node->data, successor->data);
	std::swap(node->counter, successor->counter);
	(!successor->left && !successor->right) ? removeRedBlackZero(successor) : removeBlackOne(successor);
	return;
}

template <class T>
void RBTree<T>::removeBlackOne(BinarySearchTreeNode<T>* node) {
	BinarySearchTreeNode<T>* child = node->right ? node->right : node->left;
	std::swap(node->data, child->data);
	std::swap(node->counter, child->counter);
	(!child->left && !child->right) ? removeRedBlackZero(child) : removeBlackOne(child);
	return;
}

template <class T>
void RBTree<T>::removeRedBlackZero(BinarySearchTreeNode<T>* node) {
	if (dynamic_cast<RBTreeNode<T>*>(node)->color == NodeColor::COLOR_BLACK)
		fixRemove(dynamic_cast<RBTreeNode<T>*>(node));
	if (node != this->root && node == dynamic_cast<RBTreeNode<T>*>(node)->getParent()->left)
		dynamic_cast<RBTreeNode<T>*>(node)->getParent()->left = nullptr;
	else if (node != this->root)
		dynamic_cast<RBTreeNode<T>*>(node)->getParent()->right = nullptr;
	if (node == this->root)
		this->root = nullptr;
	delete node;
	return;
}

template <class T>
void RBTree<T>::fixRemoveBlackSibling(RBTreeNode<T>* node) {
	RBTreeNode<T>* gparent = node->getParent()->getParent();
	RBTreeNode<T>* sibling = (node == node->parent->left) ? node->getParent()->getRight() : node->getParent()->getLeft();

	if ((sibling->left && sibling->right) && (sibling->getRight()->color != sibling->getLeft()->color) &&
		(((node == node->parent->left) ? sibling->getRight()->color : sibling->getLeft()->color) == NodeColor::COLOR_BLACK)) {
		((node == node->parent->left) ? sibling->getLeft()->color : sibling->getRight()->color) = NodeColor::COLOR_BLACK;
		sibling->color = NodeColor::COLOR_RED;
		(node == node->parent->left) ? node->parent->setRight(rightRotation(sibling)) : node->parent->setLeft(leftRotation(sibling));
	}
	if (((node == node->parent->left) ? sibling->getRight()->color : sibling->getLeft()->color) == NodeColor::COLOR_RED) {
		sibling->color = sibling->getParent()->color;
		sibling->getParent()->color = NodeColor::COLOR_BLACK;
		((node == node->parent->left) ? sibling->getRight()->color : sibling->getLeft()->color) = NodeColor::COLOR_BLACK;
		if (gparent && node->parent == gparent->left)
			gparent->setLeft((node == node->parent->left) ? leftRotation(node->getParent()) : rightRotation(node->getParent()));
		else if (gparent)
			gparent->setRight((node == node->parent->left) ? leftRotation(node->getParent()) : rightRotation(node->getParent()));
		else
			this->root = (node == node->parent->left) ? leftRotation(node->getParent()) : rightRotation(node->getParent());
	}
	else if (sibling->getRight()->color == NodeColor::COLOR_BLACK && sibling->getLeft()->color == NodeColor::COLOR_BLACK) {
		sibling->color = NodeColor::COLOR_RED;
		if (sibling->getParent()->color == NodeColor::COLOR_RED)
			sibling->getParent()->color = NodeColor::COLOR_BLACK;
		else
			fixRemove(sibling->getParent());
	}
	return;
}

template <class T>
void RBTree<T>::fixRemoveRedSibling(RBTreeNode<T>* node) {
	RBTreeNode<T>* gparent = node->getParent()->getParent();
	RBTreeNode<T>* sibling = (node == node->parent->left) ? node->getParent()->getRight() : node->getParent()->getLeft();

	node->getParent()->color = NodeColor::COLOR_RED;
	sibling->color = NodeColor::COLOR_BLACK;
	if (gparent && node->parent == gparent->left)
		gparent->setLeft((node == node->parent->left) ? leftRotation(node->getParent()) : rightRotation(node->getParent()));
	else if (gparent)
		gparent->setRight((node == node->parent->left) ? leftRotation(node->getParent()) : rightRotation(node->getParent()));
	else
		this->root = (node == node->parent->left) ? leftRotation(node->getParent()) : rightRotation(node->getParent());
	fixRemoveBlackSibling(node);
	return;
}

template <class T>
void RBTree<T>::fixInsert(RBTreeNode<T>* node) {
	RBTreeNode<T>* parent = nullptr;
	RBTreeNode<T>* gparent = nullptr;
	RBTreeNode<T>* uncle = nullptr;
	while (node != this->root && node->color == NodeColor::COLOR_RED && node->getParent()->color == NodeColor::COLOR_RED) {
		parent = node->getParent();
		gparent = parent->getParent();

		uncle = (parent == gparent->getLeft()) ? gparent->getRight() : gparent->getLeft();
		if (uncle && uncle->color == NodeColor::COLOR_RED) {
			uncle->color = NodeColor::COLOR_BLACK;
			parent->color = NodeColor::COLOR_BLACK;
			gparent->color = NodeColor::COLOR_RED;
			node = gparent;
			continue;
		}
		if (parent == gparent->getLeft()) {
			if (node == parent->getRight()) {
				gparent->setLeft(leftRotation(parent));
				node = parent;
				parent = node->getParent();
			}
			if (gparent->getParent()) {
				if (gparent == gparent->getParent()->getLeft())
					gparent->getParent()->setLeft(rightRotation(gparent));
				else
					gparent->getParent()->setRight(rightRotation(gparent));
			}
			else
				this->root = rightRotation(gparent);
		}
		else {
			if (node == parent->getLeft()) {
				gparent->setRight(rightRotation(parent));
				node = parent;
				parent = node->getParent();
			}
			if (gparent->getParent()) {
				if (gparent == gparent->getParent()->getLeft())
					gparent->getParent()->setLeft(leftRotation(gparent));
				else
					gparent->getParent()->setRight(leftRotation(gparent));
			}
			else
				this->root = leftRotation(gparent);
		}
		std::swap(parent->color, gparent->color);
	}
	this->getRoot()->color = NodeColor::COLOR_BLACK;
	return;
}

template <class T>
void RBTree<T>::fixRemove(RBTreeNode<T>* node) {
	if (node == this->root)
		return;
	if ((node == node->parent->left ? node->getParent()->getRight()->color : node->getParent()->getLeft()->color) == NodeColor::COLOR_BLACK)
		fixRemoveBlackSibling(node);
	else
		fixRemoveRedSibling(node);
	return;
}

template <class T>
RBTreeNode<T>* RBTree<T>::getMin(BinarySearchTreeNode<T>* const node) const {
	return dynamic_cast<RBTreeNode<T>*>(BinarySearchTree<T>::getMin(node));
}

template <class T>
RBTreeNode<T>* RBTree<T>::getMax(BinarySearchTreeNode<T>* const node) const {
	return dynamic_cast<RBTreeNode<T>*>(BinarySearchTree<T>::getMax(node));
}