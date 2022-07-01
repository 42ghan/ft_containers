
#include "rbtree.hpp"

#include <list>
#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

void check_leak(void) {
  // ft::RbTree<int> rbtree(11);
  // rbtree.Insert(5);
  // rbtree.Insert(16);

  // SECTION : Delete test
  // std::list<T3> lst;
  // unsigned int lst_size = 10;
  // for (unsigned int i = 0; i < lst_size; ++i)
  //   lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
  // ft::RbTree<ft::pair<const int, std::string> > rbtree;
  // for (std::list<T3>::iterator it = lst.begin(); it != lst.end(); ++it)
  //   rbtree.Insert(*it);
  // // rbtree.Insert(ft::make_pair(1, 42));
  // // rbtree.Insert(ft::make_pair(3, 42));
  // // rbtree.Insert(ft::make_pair(5, 42));
  // rbtree.print_tree("", rbtree.GetRoot(), false);
  // rbtree.Delete((++rbtree.begin()).base());
  // rbtree.print_tree("", rbtree.GetRoot(), false);
  // rbtree.Delete(rbtree.begin().base());
  // rbtree.print_tree("", rbtree.GetRoot(), false);

  // SECTION : Insert test
  ft::RbTree<ft::pair<const int, std::string> > rbtree;
  // FIXME : weird Insert behaviour...
  rbtree.Insert(ft::make_pair(4, "blah"), rbtree.begin().base());
  rbtree.Insert(ft::make_pair(5, "blah"), rbtree.begin().base());
  rbtree.Insert(ft::make_pair(3, "blah"), rbtree.begin().base());
  rbtree.Insert(ft::make_pair(2, "blah"), rbtree.begin().base());
  rbtree.print_tree("", rbtree.GetRoot(), false);
  // rbtree.ClearPostOrder(rbtree.GetRoot());

  // std::cout << (rbtree.begin() != rbtree.end()) << "\n";
  // for (ft::RbTree<ft::pair<const int, int> >::iterator itr = rbtree.begin();
  //      itr != rbtree.end(); ++itr) {
  //   std::cout << "hi\n";
  //   std::cout << (*itr).first << "\n";
  // }
  // rbtree.PrintInOrder(rbtree.GetRoot());
}

int main(void) {
  check_leak();
  system("leaks a.out");
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
