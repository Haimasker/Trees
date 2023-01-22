#pragma once
#include <utility>
#include <vector>
#include <queue>


template <class T>
class BinarySearchTreeNode {
	template <class T1> friend class BinarySearchTree;
	template <class N1> friend class AVLTreeNode;

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

	T	getData() const;
	void	setData(const T&);

	size_t	getCounter() const;
	void	setCounter(const size_t);

	virtual BinarySearchTreeNode<T>* getLeft() const;
	virtual void		setLeft(BinarySearchTreeNode<T>*);

	virtual BinarySearchTreeNode<T>* getRight() const;
	virtual void		setRight(BinarySearchTreeNode<T>*);

protected:
	virtual void copy(const BinarySearchTreeNode<T>&);
	virtual void move(BinarySearchTreeNode<T>&&);
};


template <class T>
class BinarySearchTree {
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

	virtual BinarySearchTreeNode<T>*	search(const T&) const;
	virtual void				insert(const T&, size_t = 1);
	virtual size_t				remove(const T&, size_t = 1);
	virtual size_t				removeAll(const T&);

	virtual BinarySearchTree<T>	operator + (const T&) const;
	virtual BinarySearchTree<T>&	operator += (const T&);
	virtual BinarySearchTree<T>	operator - (const T&) const;
	virtual BinarySearchTree<T>&	operator -= (const T&);

	virtual BinarySearchTree<T>	operator + (const BinarySearchTree<T>&) const;
	virtual BinarySearchTree<T>&	operator += (const BinarySearchTree<T>&);
	virtual BinarySearchTree<T>	operator - (const BinarySearchTree<T>&) const;
	virtual BinarySearchTree<T>&	operator -= (const BinarySearchTree<T>&);

	virtual void merge(const BinarySearchTree<T>&);
	virtual void exclude(const BinarySearchTree<T>&);

	virtual bool	empty() const final;
	virtual size_t	size() const final;
	virtual size_t	capacity() const final;
	virtual size_t	height(BinarySearchTreeNode<T>* const) const final;
	virtual size_t	height() const final;
	virtual bool	contains(const T&) const final;
	virtual size_t	count(const T&) const final;

	virtual BinarySearchTreeNode<T>* getMin() const final;
	virtual BinarySearchTreeNode<T>* getMax() const final;

	virtual std::vector<BinarySearchTreeNode<T>*> preorderDFS() const final;
	virtual std::vector<BinarySearchTreeNode<T>*> inorderDFS() const final;
	virtual std::vector<BinarySearchTreeNode<T>*> postorderDFS() const final;
	virtual std::vector<BinarySearchTreeNode<T>*> leftBFS() const final;
	virtual std::vector<BinarySearchTreeNode<T>*> rightBFS() const final;

	virtual BinarySearchTreeNode<T>* getRoot() const final;

	virtual void clear() final;

protected:
	virtual BinarySearchTreeNode<T>* findPreviousNode(const T&) const final;

	virtual void insert(const BinarySearchTreeNode<T>*) final;
	virtual void remove(const BinarySearchTreeNode<T>*) final;

	virtual BinarySearchTreeNode<T>* getMin(BinarySearchTreeNode<T>* const) const final;
	virtual BinarySearchTreeNode<T>* getMax(BinarySearchTreeNode<T>* const) const final;

	virtual void preorderDFS(BinarySearchTreeNode<T>* const, std::vector<BinarySearchTreeNode<T>*>&) const final;
	virtual void inorderDFS(BinarySearchTreeNode<T>* const, std::vector<BinarySearchTreeNode<T>*>&) const final;
	virtual void postorderDFS(BinarySearchTreeNode<T>* const, std::vector<BinarySearchTreeNode<T>*>&) const final;

};


#include "BinarySearchTree.tpp"