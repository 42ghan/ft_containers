#include <iostream>

struct A {
  //   typedef int number;
  typedef char character;
  typedef double point;
};

int main(void) {
  A a;
  std::cout << sizeof(A::number) << "\n";
}