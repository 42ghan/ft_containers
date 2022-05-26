#include <unistd.h>

#include <iostream>
#include <vector>

// class Base {
//  protected:
//   int num;

//  public:
//   Base(void) { std::cout << "Base created\n"; }
//   Base(int n) { std::cout << "Base n created\n"; }
//   ~Base(void) { std::cout << "Base destroyed\n"; }
// };

// class Derived : public Base {
//  private:
//   Base base_;

//  public:
//   Derived(void) : base_(1) { std::cout << "Derived created\n"; }
//   Derived(int n) : base_(n) { std::cout << "Derived created\n"; }
//   ~Derived(void) { std::cout << "Derived destroyed\n"; }
//   int getNum(void) { return num; }
// };

// template <typename T, typename U>

class Base {
 protected:
  int num_;

 public:
  Base(void) { std::cout << "Base created\n"; }
  Base(int n) : num_(n) { std::cout << "Base n created\n"; }
  ~Base(void) { std::cout << "Base destroyed\n"; }
  int getNum(void) const { return num_; }
};

class Test : public Base {
 public:
  Test(int n) : Base(n) {}
};

bool operator==(const Test& lhs, const Base& rhs) {
  return lhs.getNum() == rhs.getNum();
}

int main(void) {
  Test base(4242);
  Test derived(42);

  std::cout << (derived == base);
}

// int main(void) {
//   std::vector<int> a(4, 11);
//   std::vector<int> b(a.begin(), a.end());
//   for (std::vector<int>::iterator itr = b.begin(); itr != b.end(); itr++)
//     std::cout << *itr << "\n";
//   // test_leaks();
//   pause();
// }
