#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <sstream>
#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <boost/shared_ptr.hpp>

enum Colour { RED, BLACK };

template <typename T>
struct Node
{
  typedef boost::shared_ptr<Node<T> > NodePtr;
  T key_;
  NodePtr left_;
  NodePtr right_;
  NodePtr parent_;
  Colour colour_;
  bool visited_ = false;
  Node(const T& key) : key_(key) {}

  friend std::ostream& operator<<(std::ostream& os, NodePtr node)
  {
    if (node) {
      os << node->key_;
    } else {
      os << "null";
    }
    return os;
  }
};

template <typename T>
class RedBlackTree
{
public:
  typedef typename Node<T>::NodePtr NodePtrType;
  NodePtrType nullNode = NodePtrType();

  RedBlackTree() { }

  void insert(const T& key)
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
    NodePtrType z = NodePtrType(new Node<T>(key));
    z->parent_ = y;
    if (!y) {
      root_ = z;
    } else if (z->key_ < y->key_) {
      y->left_ = z;
    } else {
      y->right_ = z;
    }
    z->colour_ = RED;
    insertFixup(z);
  }

  std::list<NodePtrType> inOrderTreeWalk()
  {
    std::list<NodePtrType> list;
    inOrderTreeWalk(root_, list);
    return list;
  }

  // recursive depth first traverse
  std::list<NodePtrType> depthFirstTraverse_r()
  {
    setNodesUnvisited();
    std::list<NodePtrType> depthList;
    depthFirstTraverse_r(root_, depthList);
    return depthList;
  }

  // iterative depth first traverse
  std::list<NodePtrType> depthFirstTraverse_i()
  {
    setNodesUnvisited();
    std::list<NodePtrType> depthList;
    depthFirstTraverse_i(root_, depthList);
    return depthList;
  }

  // Level order search
  std::list<NodePtrType> breadthFirstTraverse()
  {
    setNodesUnvisited();
    std::list<NodePtrType> list;
    breadthFirstTraverse(root_, list);
    return list;
  }

  std::string dotFormat() const
  {
    std::ostringstream os;
    os << "digraph G {\n";
    os << "\tnodesep=1.0;\n";
    os << "\tnode [shape=circle];\n";
    std::stack<NodePtrType> stack;
    stack.push(root_);
    while (!stack.empty()) {
      NodePtrType node = stack.top();
      stack.pop();
      if (node) {
	if (node->left_) {
	  os << "\t\"" << node->key_ << "\" -> \"" << node->left_->key_ << "\";\n";
	  stack.push(node->left_);
	}
	if (node->right_) {
	  os << "\t\"" << node->key_ << "\" -> \"" << node->right_->key_ << "\";\n";
	  stack.push(node->right_);
	}	
      }
    }
    os << "}";
    return os.str();
  }
    
private:

  void insertFixup(NodePtrType& z)
  {
    while (z && z != root_ && colourOf(parentOf(z)) == RED) {
      // fixup red-red in left subtree
      if (parentOf(z) == parentOf(parentOf(z))->left_) {
	NodePtrType y = parentOf(parentOf(z))->right_;
	// parent has two red children, blacken both
	if (colourOf(y) == RED) {
	  setColour(parentOf(z), BLACK);
	  setColour(y, BLACK);
	  setColour(parentOf(parentOf(z)), RED);
	  z = parentOf(parentOf(z));
	} else { // parent has red and black children
	  if (z == parentOf(z)->right_) {
	    z = parentOf(z);
	    rotateLeft(z);
	  }
	  setColour(parentOf(z), BLACK);
	  setColour(parentOf(parentOf(z)), RED);
	  rotateRight(parentOf(parentOf(z)));
	}
      } else { // fixup red-red in right subtree
	NodePtrType y = parentOf(parentOf(z))->left_;
	// parent has two red children, blacken both
	if (colourOf(y) == RED) {
	  setColour(parentOf(z), BLACK);
	  setColour(y, BLACK);
	  setColour(parentOf(parentOf(z)), RED);
	  z = parentOf(parentOf(z));
	} else { // parent has red and black children
	  if (z == parentOf(z)->left_) {
	    z = parentOf(z);
	    rotateRight(z);
	  }
	  setColour(parentOf(z), BLACK);
	  setColour(parentOf(parentOf(z)), RED);
	  rotateLeft(parentOf(parentOf(z)));
	}
      } 
    } // end of while
    root_->colour_ = BLACK;
  }

  void rotateLeft(const NodePtrType& x)
  {
    NodePtrType y = x->right_;
    x->right_ = y->left_; // turn y's left subtree into x's right subtree
    if (y->left_) {
      y->left_->parent_ = x;
    }
    y->parent_ = x->parent_; // link x's parent to y
    if (!x->parent_) {
      root_ = y;
    } else if (x == x->parent_->left_) {
      x->parent_->left_ = y;
    } else {
      x->parent_->right_ = y;
    }
    y->left_ = x; // put x on y's left
    x->parent_ = y;
  }

  void rotateRight(const NodePtrType& y)
  {
    NodePtrType x = y->left_;
    y->left_ = x->right_; // turn x's right subtree into y's left subtree
    if (x->right_) {
      x->right_->parent_ = y;  // TODO: check this
    }
    x->parent_ = y->parent_; // link y's parent to x
    if (!y->parent_) {
      root_ = x;
    } else if (y == y->parent_->right_) {
      y->parent_->right_ = x;
    } else {
      y->parent_->left_ = x;
    }
    x->right_ = y; // put y on x's right
    y->parent_ = x;
  }

  Colour colourOf(const NodePtrType& node) 
  {
    if (node)
      return BLACK;
    else
      return node->colour_;
  }

  void setColour(const NodePtrType& node, const Colour& colour)
  {
    if (node) node->colour_ = colour;
  }

  NodePtrType& parentOf(const NodePtrType& node) 
  {
    if (node)
      return node->parent_;
    else
      return nullNode;
  }

  void inOrderTreeWalk(const NodePtrType& node, std::list<NodePtrType>& list)
  {
    if (node) {
      inOrderTreeWalk(node->left_, list);
      list.push_back(node);
      inOrderTreeWalk(node->right_, list);
    }
  }

  // recursive depth first traverse
  void depthFirstTraverse_r(const NodePtrType& node,     
			  std::list<NodePtrType>& depthList)
  {
    while (node && !node->visited_) {
      node->visited_ = true;
      depthFirstTraverse(node->left_, depthList);
      depthFirstTraverse(node->right_, depthList);
      depthList.push_front(node->key_);
    }
  }

  // iterative depth first traverse
  void depthFirstTraverse_i(const NodePtrType& node, std::list<NodePtrType>& list)
  {
    std::stack<NodePtrType> stack;
    stack.push(node);
    while (!stack.empty()) {
      NodePtrType n = stack.top();
      stack.pop();
      if (n && !n->visited_) {
	n->visited_ = true;
	stack.push(n->left_);
	stack.push(n->right_);
	list.push_front(n);
      }
    }
  }

  void breadthFirstTraverse(const NodePtrType& node, std::list<NodePtrType>& list)
  {
    std::queue<NodePtrType> queue;
    queue.push(node);
    while (!queue.empty()) {
      NodePtrType n = queue.front();
      queue.pop();
      if (n && !n->visited_) {
	n->visited_ = true;
	queue.push(n->left_);
	queue.push(n->right_);
	list.push_back(n);
      }
    }
  }

  void setNodesUnvisited()
  {
    typedef std::list<NodePtrType> NodePtrList;
    NodePtrList nodes = inOrderTreeWalk();
    typename NodePtrList::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); ++it) {
      (*it)->visited_ = false;
    }
  }

  RedBlackTree(const RedBlackTree&);
  RedBlackTree& operator=(const RedBlackTree&);
  NodePtrType root_;
};

#endif /* RED_BLACK_TREE_H */
