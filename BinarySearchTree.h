/*
 * BinarySearchTree.h
 *
 *  Created on: 7 Oct 2012
 *      Author: ahmed
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <boost/shared_ptr.hpp>
#include "Node.h"

template <typename T>
class BinarySearchTree {
public:
	typedef typename Node<T>::NodePtr NodePtrType;

	BinarySearchTree() {}

	~BinarySearchTree() {}

	void insert(T key)
	{
		NodePtrType y;
		NodePtrType x = root_;
		while (x) {
			y = x;
			if (key < x->key_) {
				x = x->left_;
			} else {
				x = x->right_;
			}
		}
		NodePtrType node = NodePtrType(new Node<T>(key));
		node->prev_ = y;
		if (!y) {
			root_ = node;
		} else if (node->key_ < y->key_){
			y->left_ = node;
		} else {
			y->right_ = node;
		}
	}

	void inOrderTreeWalk()
	{
		inOrderTreeWalk(root_);
	}

	void inOrderTreeWalk(const NodePtrType& node)
	{
		if (node) {
			inOrderTreeWalk(node->left_);
			std::cout << node->key_ << " ";
			inOrderTreeWalk(node->right_);
		}
	}

private:
	NodePtrType root_;
};

#endif /* BINARYSEARCHTREE_H_ */
