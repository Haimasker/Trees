#pragma once
#include "../BinarySearchTree/BinarySearchTree.hpp"


enum class NodeColor {
	COLOR_BLACK,
	COLOR_RED
};


template <class T>
class RBTreeNode : public BinarySearchTreeNode<T> {
	template <class T1> friend class RBTree;

protected:
	BinarySearchTreeNode<T>*	parent;
	NodeColor			color;

public:
	RBTreeNode(const T& = T(), size_t = 1, NodeColor = NodeColor::COLOR_RED);
	RBTreeNode(const BinarySearchTreeNode<T>&);
	RBTreeNode(BinarySearchTreeNode<T>&&);
	RBTreeNode(const RBTreeNode<T>&);
	RBTreeNode(RBTreeNode<T>&&);
	virtual ~RBTreeNode();

	virtual RBTreeNode<T>& operator = (const BinarySearchTreeNode<T>&) override;
	virtual RBTreeNode<T>& operator = (BinarySearchTreeNode<T>&&) override;

	virtual RBTreeNode<T>& operator = (const RBTreeNode<T>&);
	virtual RBTreeNode<T>& operator = (RBTreeNode<T>&&);

	virtual RBTreeNode<T>*	getLeft() const override;
	virtual bool		setLeft(BinarySearchTreeNode<T>*) override;

	virtual RBTreeNode<T>*	getRight() const override;
	virtual bool		setRight(BinarySearchTreeNode<T>*) override;

	virtual RBTreeNode<T>*	getParent() const final;
	virtual bool		setParent(BinarySearchTreeNode<T>*) final;

	virtual NodeColor	getColor() const final;
	virtual void		setColor(const NodeColor&) final;

protected:
	virtual void copy(const BinarySearchTreeNode<T>&) override;
	virtual void move(BinarySearchTreeNode<T>&&) override;

	virtual bool isEqual(const BinarySearchTreeNode<T>*, const BinarySearchTreeNode<T>*) const override;
};


template <class T>
class RBTree : public BinarySearchTree<T> {
public:
	RBTree();
	RBTree(const BinarySearchTree<T>&);
	RBTree(BinarySearchTree<T>&&);
	RBTree(const RBTree<T>&);
	RBTree(RBTree<T>&&);
	virtual ~RBTree();

	virtual RBTree<T>& operator = (const BinarySearchTree<T>&) override;
	virtual RBTree<T>& operator = (BinarySearchTree<T>&&) override;

	virtual RBTree<T>& operator = (const RBTree<T>&);
	virtual RBTree<T>& operator = (RBTree<T>&&);

	virtual RBTreeNode<T>*	search(const T&) const override;
	virtual void		insert(const T&, size_t = 1) override;
	virtual size_t		removeAll(const T&) override;

	RBTree<T> operator + (const T&) const;
	RBTree<T> operator - (const T&) const;

	RBTree<T> operator + (const BinarySearchTree<T>&) const;
	RBTree<T> operator - (const BinarySearchTree<T>&) const;

	virtual RBTreeNode<T>* getMin() const override;
	virtual RBTreeNode<T>* getMax() const override;

	virtual RBTreeNode<T>* getPredecessor(const T&) const override;
	virtual RBTreeNode<T>* getSuccessor(const T&) const override;

	std::vector<RBTreeNode<T>*> preorderDFS() const;
	std::vector<RBTreeNode<T>*> inorderDFS() const;
	std::vector<RBTreeNode<T>*> postorderDFS() const;
	std::vector<RBTreeNode<T>*> leftBFS() const;
	std::vector<RBTreeNode<T>*> rightBFS() const;

	virtual RBTreeNode<T>* getRoot() const override;

protected:
	virtual RBTreeNode<T>* leftRotation(RBTreeNode<T>*) final;
	virtual RBTreeNode<T>* rightRotation(RBTreeNode<T>*) final;

	virtual void removeRedBlackTwo(BinarySearchTreeNode<T>*) final;
	virtual void removeBlackOne(BinarySearchTreeNode<T>*) final;
	virtual void removeRedBlackZero(BinarySearchTreeNode<T>*) final;

	virtual void fixRemoveBlackSibling(RBTreeNode<T>*) final;
	virtual void fixRemoveRedSibling(RBTreeNode<T>*) final;

	virtual void fixInsert(RBTreeNode<T>*) final;
	virtual void fixRemove(RBTreeNode<T>*) final;

	virtual RBTreeNode<T>* getMin(BinarySearchTreeNode<T>* const) const override;
	virtual RBTreeNode<T>* getMax(BinarySearchTreeNode<T>* const) const override;
};


#include "RBTree.tpp"