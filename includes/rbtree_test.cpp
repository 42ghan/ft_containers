#include "rbtree.hpp"

void check_leak(void) {
  ft::RbTree<int> rbtree(11);
  rbtree.Insert(5);
  rbtree.Insert(16);

  rbtree.PrintInOrder(rbtree.GetRoot());
}

int main(void) {
  check_leak();
  system("leaks a.out");
}
