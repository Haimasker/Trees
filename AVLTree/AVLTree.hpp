#pragma once
#include "../BinarySearchTree/BinarySearchTree.hpp"


template <class T>
class AVLTreeNode : public BinarySearchTreeNode<T> {
	//template <class U> friend class BinarySearchTree;

//protected:
public:
	size_t height;

public:
	AVLTreeNode(const T& = T(), size_t = 1, size_t = 1);
	AVLTreeNode(const AVLTreeNode<T>&);
	AVLTreeNode(AVLTreeNode<T>&&);
	virtual ~AVLTreeNode();

	virtual AVLTreeNode<T>& operator = (const BinarySearchTreeNode<T>&) override;
	virtual AVLTreeNode<T>& operator = (BinarySearchTreeNode<T>&&) override;

	virtual AVLTreeNode<T>& operator = (const AVLTreeNode<T>&);
	virtual AVLTreeNode<T>& operator = (AVLTreeNode<T>&&);


	virtual AVLTreeNode<T>* getLeft() const override;
	//virtual void		setLeft(BinarySearchTreeNode<T>*) override;

	virtual AVLTreeNode<T>* getRight() const override;
	//virtual AVLTreeNode<T>* getRight() const override;
	//virtual void		setRight(BinarySearchTreeNode<T>*) override;

protected:
	virtual void copy(const BinarySearchTreeNode<T>&) override;
	virtual void move(BinarySearchTreeNode<T>&&) override;
};


#include "AVLTree.tpp"