#include "rbtree.hpp"

void check_leak(void) {
  // ft::RbTree<int> rbtree(11);
  // rbtree.Insert(5);
  // rbtree.Insert(16);

  ft::RbTree<ft::pair<const int, int> > rbtree;
  rbtree.Insert(ft::make_pair(1, 42));
  rbtree.Insert(ft::make_pair(3, 42));
  std::cout << (rbtree.begin() != rbtree.end()) << "\n";
  for (ft::RbTree<ft::pair<const int, int> >::iterator itr = rbtree.begin();
       itr != rbtree.end(); ++itr) {
    std::cout << "hi\n";
    std::cout << (*itr).first << "\n";
  }
  // rbtree.PrintInOrder(rbtree.GetRoot());
}

int main(void) {
  check_leak();
  // system("leaks a.out");
}

// #include <iostream>
// #include <map>
// #include <utility>

// using namespace std;

// int main() {
//   const map<int, int> m;
//   m.insert(make_pair<int, int>(1, 2));
//   cout << (*(m.begin())).second << "\n";
//   (*(m.begin())).second = 7;
//   cout << (*(m.begin())).second << "\n";
// }
