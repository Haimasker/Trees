#pragma once
#include <utility>
#include <vector>

template <class T>
class BinaryTreeNode {
protected:
	T				data;
	size_t			counter;
	BinaryTreeNode*	left;
	BinaryTreeNode*	right;

public:
	BinaryTreeNode(T = T(), size_t = 0);			// OK
	BinaryTreeNode(const BinaryTreeNode&);			// OK
	BinaryTreeNode(BinaryTreeNode&&);				// OK
	virtual ~BinaryTreeNode() = 0;					// OK

	//todo assignment operators

protected:
	virtual BinaryTreeNode<T>* deepCopy(const BinaryTreeNode&);	// OK
};

template <class T>
class BinaryTree {
protected:
	BinaryTreeNode<T>*	root;
	size_t				size_;
	size_t				capacity_;

public:
	BinaryTree(const BinaryTreeNode<T>* = nullptr);	// OK
	BinaryTree(const BinaryTree&);					// OK
	BinaryTree(BinaryTree&&);						// OK
	virtual ~BinaryTree() = 0;

	virtual BinaryTree&	operator = (const BinaryTree&) = 0; //todo not pure virtual
	virtual BinaryTree&	operator = (BinaryTree&&) = 0;		//todo not pure virtual

	virtual BinaryTree*	operator + (const BinaryTree&) const = 0;
	virtual BinaryTree&	operator += (const BinaryTree&) = 0;
	virtual BinaryTree*	operator - (const BinaryTree&) const = 0;
	virtual BinaryTree&	operator -= (const BinaryTree&) = 0;

	virtual BinaryTree*	operator + (const T&) const = 0;
	virtual BinaryTree&	operator += (const T&) = 0;
	virtual BinaryTree*	operator - (const T&) const = 0;
	virtual BinaryTree&	operator -= (const T&) = 0;

	virtual void				merge(const BinaryTree&) = 0;
	virtual void				exclude(const BinaryTree&) = 0;

	virtual void				insert(const T&, size_t = 1) = 0;	//const & ??
	virtual bool				remove(const T&, size_t = 1) = 0;
	virtual bool				removeAll(const T&) = 0;
	virtual BinaryTreeNode<T>*	search(const T&) const = 0;

	virtual bool	empty() const = 0;
	virtual size_t	size() const = 0;
	virtual size_t	capacity() const = 0;
	virtual size_t	height() const = 0;
	virtual bool	contains(const T&) const = 0;
	virtual size_t	count(const T&) const = 0;

	virtual int	getMin() const = 0;
	virtual int	getMax() const = 0;

	virtual std::vector<T*> preorderDFS() const = 0;
	virtual std::vector<T*> inorderDFS() const = 0;
	virtual std::vector<T*> postorderDFS() const = 0;
	virtual std::vector<T*>	leftBFS() const = 0;
	virtual std::vector<T*>	rightBFS() const = 0;

	virtual void clear() = 0;
};