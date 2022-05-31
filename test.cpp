#include <unistd.h>

#include <iostream>
#include <vector>

class Base {
 protected:
  typedef int int_custom;
  int_custom num_;

 public:
  Base(void) { std::cout << "Base created\n"; }
  Base(int n) : num_(n) { std::cout << "Base n created\n"; }
  ~Base(void) { std::cout << "Base destroyed\n"; }
  int getNum(void) const { return num_; }
};

class Test : protected Base {
 public:
  Test(int n) : Base(n) {}
  void print(void) { std::cout << num_ << "\n"; }
};

// bool operator==(const Test& lhs, const Base& rhs) {
//   return lhs.getNum() == rhs.getNum();
// }

int main(void) {
  Test base(4242);
  Test derived(42);

  base.print();

  // std::cout << (derived == base);
}

// int main(void) {
//   std::vector<int> a(4, 11);
//   std::vector<int> b(a.begin(), a.end());
//   for (std::vector<int>::iterator itr = b.begin(); itr != b.end(); itr++)
//     std::cout << *itr << "\n";
//   // test_leaks();
//   pause();
// }
