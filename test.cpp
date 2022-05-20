#include <unistd.h>

#include <iostream>
#include <vector>

int main(void) {
  std::vector<int> a(4, 11);
  std::vector<int> b(a.begin(), a.end());
  for (std::vector<int>::iterator itr = b.begin(); itr != b.end(); itr++)
    std::cout << *itr << "\n";
  // test_leaks();
  pause();
}
