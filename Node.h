/*
 * Node.h
 *
 *  Created on: 7 Oct 2012
 *      Author: ahmed
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <boost/shared_ptr.hpp>

template <typename T>
class BinarySearchTree;

template <typename T>
class Node {
public:
	typedef boost::shared_ptr<Node<T> > NodePtr;
	friend class BinarySearchTree<T>;

	explicit Node(T key) : key_(key) { }

	virtual ~Node()	{	}

	friend std::ostream& operator<<(std::ostream& os, const Node<T>& node)
	{
		os << node.key_;
		return os;
	}

private:
	T key_;
	NodePtr left_;
	NodePtr right_;
	NodePtr prev_;
};

#endif /* NODE_H_ */
