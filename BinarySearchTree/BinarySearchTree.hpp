#pragma once
#include <utility>
#include <vector>

template <class T>
class BinarySearchTreeNode {
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

	BinarySearchTreeNode<T>* getLeft() const;
	void		setLeft(BinarySearchTreeNode<T>*);

	BinarySearchTreeNode<T>* getRight() const;
	void		setRight(BinarySearchTreeNode<T>*);
};


template <class T>
class BinarySearchTree {
protected:
	BinarySearchTreeNode<T>*	root;
	size_t				size_;
	size_t				capacity_;

public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTreeNode<T>*);
	BinarySearchTree(const BinarySearchTree<T>&);
	BinarySearchTree(BinarySearchTree<T>&&);
	virtual ~BinarySearchTree();

	virtual BinarySearchTree<T>& operator = (const BinarySearchTree<T>&);
	virtual BinarySearchTree<T>& operator = (BinarySearchTree<T>&&);

	virtual BinarySearchTreeNode<T>*	search(const T&, const BinarySearchTreeNode<T>*) const;
	virtual BinarySearchTreeNode<T>*	search(const T&) const;
	virtual void				insert(const T&, size_t = 1);
	virtual size_t				remove(const T&, const BinarySearchTreeNode<T>*, size_t = 1);
	virtual size_t				remove(const T&, size_t = 1);
	virtual size_t				removeAll(const T&, const BinarySearchTreeNode<T>*);
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
	virtual size_t	height(const BinarySearchTreeNode<T>*) const final;
	virtual size_t	height() const final;
	virtual bool	contains(const T&) const final;
	virtual size_t	count(const T&) const final;

	virtual BinarySearchTreeNode<T>* getMin(const BinarySearchTreeNode<T>*) const final;
	virtual BinarySearchTreeNode<T>* getMin() const final;
	virtual BinarySearchTreeNode<T>* getMax(const BinarySearchTreeNode<T>*) const final;
	virtual BinarySearchTreeNode<T>* getMax() const final;

	virtual size_t countSize(const BinarySearchTreeNode<T>*) const final;
	virtual size_t countSize() const final;
	virtual size_t countCapacity(const BinarySearchTreeNode<T>*) const final;
	virtual size_t countCapacity() const final;

	// virtual std::vector<T*>	preorderDFS() const final;
	// virtual std::vector<T*>	inorderDFS() const final;
	// virtual std::vector<T*>	postorderDFS() const final;
	// virtual std::vector<T*>	leftBFS() const final;
	// virtual std::vector<T*>	rightBFS() const final;

	// virtual void clear() final;

protected:
	virtual void insert(const BinarySearchTreeNode<T>*);
	virtual void remove(const BinarySearchTreeNode<T>*);

};


#include "BinarySearchTree.tpp"