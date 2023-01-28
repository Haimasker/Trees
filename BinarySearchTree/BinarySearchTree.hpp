#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>


template <class T>
class BinarySearchTreeNode {
	template <class T1> friend class BinarySearchTree;

	template <class T2> friend class AVLTree;
	template <class N2> friend class AVLTreeNode;

protected:
	T				data;
	size_t				counter;
	BinarySearchTreeNode<T>*	left;
	BinarySearchTreeNode<T>*	right;

public:
	BinarySearchTreeNode(const T& = T(), size_t = 1);
	BinarySearchTreeNode(const BinarySearchTreeNode<T>&);
	BinarySearchTreeNode(BinarySearchTreeNode<T>&&);
	virtual ~BinarySearchTreeNode();

	virtual BinarySearchTreeNode<T>& operator = (const BinarySearchTreeNode<T>&);
	virtual BinarySearchTreeNode<T>& operator = (BinarySearchTreeNode<T>&&);

	virtual bool operator == (const BinarySearchTreeNode<T>&) const final;
	virtual bool operator != (const BinarySearchTreeNode<T>&) const final;

	virtual T	getData() const final;
	virtual void	setData(const T&) final;

	virtual size_t	getCounter() const final;
	virtual void	setCounter(const size_t) final;

	virtual BinarySearchTreeNode<T>* getLeft() const;
	virtual void			setLeft(BinarySearchTreeNode<T>*) final;

	virtual BinarySearchTreeNode<T>* getRight() const;
	virtual void			setRight(BinarySearchTreeNode<T>*) final;

protected:
	virtual void copy(const BinarySearchTreeNode<T>&);
	virtual void move(BinarySearchTreeNode<T>&&);

	virtual bool isEqual(const BinarySearchTreeNode<T>*, const BinarySearchTreeNode<T>*) const;
};


template <class T>
class BinarySearchTree {
	template <class T1> friend class AVLTree;

protected:
	BinarySearchTreeNode<T>*	root;
	size_t				size_;
	size_t				capacity_;

public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>&);
	BinarySearchTree(BinarySearchTree<T>&&);
	virtual ~BinarySearchTree();

	virtual BinarySearchTree<T>& operator = (const BinarySearchTree<T>&);
	virtual BinarySearchTree<T>& operator = (BinarySearchTree<T>&&);

	virtual bool operator == (const BinarySearchTree<T>&) const final;
	virtual bool operator != (const BinarySearchTree<T>&) const final;

	virtual BinarySearchTreeNode<T>*	search(const T&) const;
	virtual void				insert(const T&, size_t = 1);
	virtual size_t				remove(const T&, size_t = 1) final;
	virtual size_t				removeAll(const T&);

	BinarySearchTree<T> operator + (const T&) const;
	BinarySearchTree<T> operator - (const T&) const;

	virtual BinarySearchTree<T>& operator += (const T&);
	virtual BinarySearchTree<T>& operator -= (const T&);

	BinarySearchTree<T> operator + (const BinarySearchTree<T>&) const;
	BinarySearchTree<T> operator - (const BinarySearchTree<T>&) const;

	virtual BinarySearchTree<T>& operator += (const BinarySearchTree<T>&);
	virtual BinarySearchTree<T>& operator -= (const BinarySearchTree<T>&);

	virtual void merge(const BinarySearchTree<T>&) final;
	virtual void exclude(const BinarySearchTree<T>&) final;

	virtual bool	empty() const final;
	virtual size_t	size() const final;
	virtual size_t	capacity() const final;
	virtual size_t	height(BinarySearchTreeNode<T>* const) const;
	virtual size_t	height() const;
	virtual bool	contains(const T&) const final;
	virtual size_t	count(const T&) const final;

	virtual BinarySearchTreeNode<T>* getMin() const;
	virtual BinarySearchTreeNode<T>* getMax() const;

	std::vector<BinarySearchTreeNode<T>*> preorderDFS() const;
	std::vector<BinarySearchTreeNode<T>*> inorderDFS() const;
	std::vector<BinarySearchTreeNode<T>*> postorderDFS() const;
	std::vector<BinarySearchTreeNode<T>*> leftBFS() const;
	std::vector<BinarySearchTreeNode<T>*> rightBFS() const;

	virtual BinarySearchTreeNode<T>* getRoot() const;

	virtual void clear() final;

protected:
	virtual BinarySearchTreeNode<T>* findPreviousNode(const T&) const final;

	virtual void insert(const BinarySearchTreeNode<T>*) final;
	virtual void remove(const BinarySearchTreeNode<T>*) final;

	virtual BinarySearchTreeNode<T>* getMin(BinarySearchTreeNode<T>* const) const;
	virtual BinarySearchTreeNode<T>* getMax(BinarySearchTreeNode<T>* const) const;

	virtual void preorderDFS(BinarySearchTreeNode<T>* const, std::vector<BinarySearchTreeNode<T>*>&) const final;
	virtual void inorderDFS(BinarySearchTreeNode<T>* const, std::vector<BinarySearchTreeNode<T>*>&) const final;
	virtual void postorderDFS(BinarySearchTreeNode<T>* const, std::vector<BinarySearchTreeNode<T>*>&) const final;
};


#include "BinarySearchTree.tpp"