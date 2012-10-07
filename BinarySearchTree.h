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
		while (x != 0) {
			y = x;
			if (key < x->key_) {
				x = x->left_;
			} else {
				x = x->right_;
			}
		}
		NodePtrType node = NodePtrType(new Node<T>(key));
		std::cout << *node << std::endl;
	}

private:
	NodePtrType root_;
};

#endif /* BINARYSEARCHTREE_H_ */
