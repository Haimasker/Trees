#pragma once
#include <utility>
#include <vector>

template <class T>
class BinarySearchTreeNode {
protected:
	T		data;
	size_t		counter;
	BinarySearchTreeNode<T>*	left;
	BinarySearchTreeNode<T>*	right;

public:
	BinarySearchTreeNode(const T& = T(), size_t = 1);
	BinarySearchTreeNode(const BinarySearchTreeNode<T>&);
	BinarySearchTreeNode(BinarySearchTreeNode<T>&&);
	virtual ~BinarySearchTreeNode();

	virtual BinarySearchTreeNode<T>& operator = (const BinarySearchTreeNode<T>&);
	virtual BinarySearchTreeNode<T>& operator = (BinarySearchTreeNode<T>&&);

	T getData() const;
	void setData(const T&);

	size_t getCounter() const;
	void setCounter(const size_t);

	BinarySearchTreeNode<T>* getLeft() const;
	void setLeft(BinarySearchTreeNode<T>*);

	BinarySearchTreeNode<T>* getRight() const;
	void setRight(BinarySearchTreeNode<T>*);
};


template <class T>
class BinarySearchTree {
protected:
	BinarySearchTreeNode<T>*	root;
	size_t				size_;
	size_t				capacity_;

public:
	BinarySearchTree();												// OK
	BinarySearchTree(const BinarySearchTreeNode<T>*);				//
	BinarySearchTree(const BinarySearchTree<T>&);					// OK
	BinarySearchTree(BinarySearchTree<T>&&);						// OK
	virtual ~BinarySearchTree();									// OK

	virtual BinarySearchTree<T>& operator = (const BinarySearchTree<T>&);	// OK
	virtual BinarySearchTree<T>& operator = (BinarySearchTree<T>&&);		// OK

	virtual BinarySearchTreeNode<T>*	search(const T&, const BinarySearchTreeNode<T>*) const;	// OK
	virtual BinarySearchTreeNode<T>*	search(const T&) const;									// OK
	virtual void			insert(const T&, size_t = 1);										// OK
	virtual size_t			remove(const T&, const BinarySearchTreeNode<T>*, size_t = 1);		// OK
	virtual size_t			remove(const T&, size_t = 1);										// OK
	virtual size_t			removeAll(const T&, const BinarySearchTreeNode<T>*);				// OK
	virtual size_t			removeAll(const T&);												// OK

	virtual BinarySearchTree<T> operator + (const T&) const;	// OK
	virtual BinarySearchTree<T>& operator += (const T&);		// OK
	virtual BinarySearchTree<T> operator - (const T&) const;	// OK
	virtual BinarySearchTree<T>& operator -= (const T&);		// OK

	virtual BinarySearchTree<T> operator + (const BinarySearchTree<T>&) const;	// OK
	virtual BinarySearchTree<T>& operator += (const BinarySearchTree<T>&);		// OK
	virtual BinarySearchTree<T> operator - (const BinarySearchTree<T>&) const;	// OK
	virtual BinarySearchTree<T>& operator -= (const BinarySearchTree<T>&);		// OK

	virtual void merge(const BinarySearchTree<T>&);		// OK
	virtual void exclude(const BinarySearchTree<T>&);	// OK

	virtual bool	empty() const final;								// OK
	virtual size_t	size() const final;									// OK
	virtual size_t	capacity() const final;								// OK
	virtual size_t	height(const BinarySearchTreeNode<T>*) const final;	// OK
	virtual size_t	height() const final;								// OK
	virtual bool	contains(const T&) const final;						// OK
	virtual size_t	count(const T&) const final;						// OK

	virtual BinarySearchTreeNode<T>* getMin(const BinarySearchTreeNode<T>*) const final;	// OK
	virtual BinarySearchTreeNode<T>* getMin() const final;									// OK
	virtual BinarySearchTreeNode<T>* getMax(const BinarySearchTreeNode<T>*) const final;	// OK
	virtual BinarySearchTreeNode<T>* getMax() const final;									// OK

	virtual size_t countSize(const BinarySearchTreeNode<T>*) const final;		// OK
	virtual size_t countSize() const final;										// OK
	virtual size_t countCapacity(const BinarySearchTreeNode<T>*) const final;	// OK
	virtual size_t countCapacity() const final;									// OK

	// virtual std::vector<T*>	preorderDFS() const final;
	// virtual std::vector<T*>	inorderDFS() const final;
	// virtual std::vector<T*>	postorderDFS() const final;
	// virtual std::vector<T*>	leftBFS() const final;
	// virtual std::vector<T*>	rightBFS() const final;

	// virtual void clear() final;

protected:
	virtual void insert(const BinarySearchTreeNode<T>*);	// OK
	virtual void remove(const BinarySearchTreeNode<T>*);	// OK

};


#include "BinarySearchTree.tpp"