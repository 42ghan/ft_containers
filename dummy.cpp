#include <functional>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

// class TestSize {
//   char b;
//   char c;
//   char d;
//   int nbr;

//  public:
//   void printNbr(void) {
//     std::cout << nbr << "\n";
//     std::cout << nbr << "\n";
//     std::cout << nbr << "\n";
//     std::cout << nbr << "\n";
//     std::cout << nbr << "\n";
//     std::cout << nbr << "\n";
//     std::cout << nbr << "\n";
//   }
// };

// int main(void) {
//   // std::pair<char, std::vector<int> > pair_a('a', std::vector<int>(15));
//   // std::pair<int, char> pair_b(pair_a);
//   // std::cout << pair_b.first << " " << pair_b.second << "\n";
//   TestSize ts;
//   std::cout << sizeof(ts) << "\n";
//   //   std::cout << sizeof(A::number) << "\n";
// }

int main(void) {
  // std::less<int> comp;
  // std::cout << comp(1, 2);
  std::map<int, int> a;
  a.insert(std::make_pair<int, int>(1, 12));
  std::map<int, int>::iterator itr = a.begin();
  itr--;
}