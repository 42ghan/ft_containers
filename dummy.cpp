#include <iostream>
#include <utility>
#include <vector>

int main(void) {
  std::pair<char, std::vector<int> > pair_a('a', std::vector<int>(15));
  std::pair<int, char> pair_b(pair_a);
  std::cout << pair_b.first << " " << pair_b.second << "\n";
  //   std::cout << sizeof(A::number) << "\n";
}