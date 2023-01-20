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

	virtual AVLTreeNode<T>* getLeft() const override;

protected:
	virtual void copyHeights(BinarySearchTreeNode<T>* const) final;
};


#include "AVLTree.tpp"