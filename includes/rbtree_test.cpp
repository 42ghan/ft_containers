#include "rbtree.hpp"

void check_leak(void) {
  // ft::RbTree<int> rbtree(11);
  // rbtree.Insert(5);
  // rbtree.Insert(16);

  ft::RbTree<ft::pair<const int, int> > rbtree;
  rbtree.Insert(ft::make_pair(1, 42));
  rbtree.Insert(ft::make_pair(3, 42));
  ft::RbTree<ft::pair<const int, int> >::const_iterator cite = rbtree.begin();
  std::cout << (*cite).first << "\n";
  std::cout << rbtree.GetSize() << "\n";
  // rbtree.PrintInOrder(rbtree.GetRoot());
}

int main(void) {
  check_leak();
  // system("leaks a.out");
}
