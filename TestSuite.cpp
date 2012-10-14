#include "RedBlackTree.h"
#include "StringUtils.h"
#include <fstream>

#define DOT = "/usr/local/graphviz-2.14/bin/dot";
#define ACROBAT = "/Applications/Adobe\ Reader.app/Contents/MacOS/AdobeReader"

template <typename T>
void renderDot(const RedBlackTree<T>& tree)
{
  std::ofstream ofs("graph.dot", std::ios::out);
  if (ofs.is_open()) {
    std::string dotFormat = tree.dotFormat();
    ofs << dotFormat;
    ofs.close();
  }
}

void testRedBlackTree()
{
  RedBlackTree<int> rb;
  rb.insert(15);
  rb.insert(6);
  rb.insert(7);
  rb.insert(3);
  rb.insert(4);
  rb.insert(2);
  rb.insert(13);
  rb.insert(9);
  rb.insert(17);
  rb.insert(18);
  rb.insert(20);

  rb.insert(14);
  // rb.insert(5);
  rb.insert(21);
  rb.insert(19);
  
  typedef std::list<typename RedBlackTree<int>::NodePtrType> NodePtrList;
  NodePtrList list = rb.inOrderTreeWalk();
  // 2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20 
  for (NodePtrList::iterator it = list.begin(); it != list.end(); ++it) {
    std::cout << (*it)->key_ << " ";
  }
  std::cout << std::endl;

  std::string dotFormat = rb.dotFormat();
  std::cout << dotFormat << std::endl;
  renderDot(rb);

  NodePtrList depthList = rb.depthFirstTraverse_i();
  for (NodePtrList::const_iterator it = 
	 depthList.begin(); it != depthList.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  NodePtrList breadthList = rb.breadthFirstTraverse();
  for (NodePtrList::const_iterator it = 
	 breadthList.begin(); it != breadthList.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void testReverseString()
{
  char str[] = {"ahmed riza is good"};
  reverseString(str, strlen(str));
  std::cout << str << std::endl;
}

void testReverseWords()
{
  char str[] = {"ahmed riza is a good old boy"};
  std::cout << str << std::endl;
  reverseWords(str, ' ');
  std::cout << str << std::endl;
}

void testTokenize()
{
  char str[] = {"ahmed riza is good"};
  typedef std::vector<std::string> Vec;
  Vec v = tokenize(str, " ");
  for (Vec::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << * it << std::endl;
  }
}

void testIntToRoman(int n)
{
  std::string s = intToRoman(n);
  std::cout << s << std::endl;
}

int main(int argc, char** argv)
{
  // testReverseString();
  // testReverseWords();
  // testTokenize();
  testIntToRoman(73);
  return 0;
}
