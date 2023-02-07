#pragma once
#include "../BinarySearchTree/BinarySearchTree.hpp"


template <class T>
class AVLTreeNode : public BinarySearchTreeNode<T> {
	template <class T1> friend class AVLTree;

protected:
	size_t height;

public:
	AVLTreeNode(const T& = T(), size_t = 1, size_t = 1);
	AVLTreeNode(const BinarySearchTreeNode<T>&);
	AVLTreeNode(BinarySearchTreeNode<T>&&);
	AVLTreeNode(const AVLTreeNode<T>&);
	AVLTreeNode(AVLTreeNode<T>&&);
	virtual ~AVLTreeNode();

	virtual AVLTreeNode<T>& operator = (const BinarySearchTreeNode<T>&) override;
	virtual AVLTreeNode<T>& operator = (BinarySearchTreeNode<T>&&) override;

	virtual AVLTreeNode<T>& operator = (const AVLTreeNode<T>&);
	virtual AVLTreeNode<T>& operator = (AVLTreeNode<T>&&);

	virtual AVLTreeNode<T>* getLeft() const override;
	virtual AVLTreeNode<T>* getRight() const override;

	virtual size_t	getHeight() const final;
	virtual void	setHeight(const size_t) final;

protected:
	virtual void copy(const BinarySearchTreeNode<T>&) override;
	virtual void move(BinarySearchTreeNode<T>&&) override;

	virtual bool isEqual(const BinarySearchTreeNode<T>*, const BinarySearchTreeNode<T>*) const override;
};


template <class T>
class AVLTree : public BinarySearchTree<T> {
public:
	AVLTree();
	AVLTree(const BinarySearchTree<T>&);
	AVLTree(BinarySearchTree<T>&&);
	AVLTree(const AVLTree<T>&);
	AVLTree(AVLTree<T>&&);
	virtual ~AVLTree();

	virtual AVLTree<T>& operator = (const BinarySearchTree<T>&) override;
	virtual AVLTree<T>& operator = (BinarySearchTree<T>&&) override;

	virtual AVLTree<T>& operator = (const AVLTree<T>&);
	virtual AVLTree<T>& operator = (AVLTree<T>&&);

	virtual AVLTreeNode<T>*	search(const T&) const override;
	virtual void		insert(const T&, size_t = 1) override;
	virtual size_t		removeAll(const T&) override;

	AVLTree<T> operator + (const T&) const;
	AVLTree<T> operator - (const T&) const;

	AVLTree<T> operator + (const BinarySearchTree<T>&) const;
	AVLTree<T> operator - (const BinarySearchTree<T>&) const;

	virtual size_t	height(BinarySearchTreeNode<T>* const) const override;
	virtual size_t	height() const override;

	virtual AVLTreeNode<T>* getMin() const override;
	virtual AVLTreeNode<T>* getMax() const override;

	virtual AVLTreeNode<T>* getPredecessor(const T&) const override;
	virtual AVLTreeNode<T>* getSuccessor(const T&) const override;

	std::vector<AVLTreeNode<T>*> preorderDFS() const;
	std::vector<AVLTreeNode<T>*> inorderDFS() const;
	std::vector<AVLTreeNode<T>*> postorderDFS() const;
	std::vector<AVLTreeNode<T>*> leftBFS() const;
	std::vector<AVLTreeNode<T>*> rightBFS() const;

	virtual AVLTreeNode<T>* getRoot() const override;

protected:
	virtual int balanceFactor(AVLTreeNode<T>*) const final;

	virtual AVLTreeNode<T>* leftRotation(AVLTreeNode<T>*);
	virtual AVLTreeNode<T>* rightRotation(AVLTreeNode<T>*);

	virtual void updateHeights(AVLTreeNode<T>*) final;

	virtual void balancePath(std::vector<BinarySearchTreeNode<T>**>);

	virtual AVLTreeNode<T>* getMin(BinarySearchTreeNode<T>* const) const override;
	virtual AVLTreeNode<T>* getMax(BinarySearchTreeNode<T>* const) const override;
};


#include "AVLTree.tpp"