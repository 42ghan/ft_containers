// SECTION - from subject
// #include <deque>
// #include <iostream>
// #include <string>
// #if 1  // CREATE A REAL STL EXAMPLE
// #include <map>
// #include <stack>
// #include <vector>
// namespace ft = std;
// #else
// #include <map.hpp>
// #include <stack.hpp>
// #include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer {
//   int idx;
//   char buff[BUFFER_SIZE];
// };

// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template <typename T>
// class MutantStack : public ft::stack<T> {
//  public:
//   MutantStack() {}
//   MutantStack(const MutantStack<T>& src) { *this = src; }
//   MutantStack<T>& operator=(const MutantStack<T>& rhs) {
//     this->c = rhs.c;
//     return *this;
//   }
//   ~MutantStack() {}

//   typedef typename ft::stack<T>::container_type::iterator iterator;

//   iterator begin() { return this->c.begin(); }
//   iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
//   if (argc != 2) {
//     std::cerr << "Usage: ./test seed" << std::endl;
//     std::cerr << "Provide a seed please" << std::endl;
//     std::cerr << "Count value:" << COUNT << std::endl;
//     return 1;
//   }
//   const int seed = atoi(argv[1]);
//   srand(seed);

//   ft::vector<std::string> vector_str;
//   ft::vector<int> vector_int;
//   ft::stack<int> stack_int;
//   ft::vector<Buffer> vector_buffer;
//   ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
//   ft::map<int, int> map_int;

//   for (int i = 0; i < COUNT; i++) {
//     vector_buffer.push_back(Buffer());
//   }

//   for (int i = 0; i < COUNT; i++) {
//     const int idx = rand() % COUNT;
//     vector_buffer[idx].idx = 5;
//   }
//   ft::vector<Buffer>().swap(vector_buffer);

//   try {
//     for (int i = 0; i < COUNT; i++) {
//       const int idx = rand() % COUNT;
//       vector_buffer.at(idx);
//       std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
//     }
//   } catch (const std::exception& e) {
//     // NORMAL ! :P
//   }

//   for (int i = 0; i < COUNT; ++i) {
//     map_int.insert(ft::make_pair(rand(), rand()));
//   }

//   int sum = 0;
//   for (int i = 0; i < 10000; i++) {
//     int access = rand();
//     sum += map_int[access];
//   }
//   std::cout << "should be constant with the same seed: " << sum << std::endl;

//   { ft::map<int, int> copy = map_int; }
//   MutantStack<char> iterable_stack;
//   for (char letter = 'a'; letter <= 'z'; letter++)
//   iterable_stack.push(letter); for (MutantStack<char>::iterator it =
//   iterable_stack.begin();
//        it != iterable_stack.end(); it++) {
//     std::cout << *it;
//   }
//   std::cout << std::endl;
//   return (0);
// }
// ======================================================================================//

#include <iostream>
#include <string>
#include <vector>

#include "vector.hpp"

// int main(void) {
//   ft::vector<int> s(5, 1);
//   ft::vector<int>::iterator citr;
//   ft::vector<int>::const_iterator itr = s.begin();
//   citr = itr;
//   std::cout << *citr;
//   // ft::vector<int> v(s.begin(), s.end());
//   // v.push_back(1);
//   // v.push_back(2);
//   // v.push_back(3);
//   // v.push_back(4);
//   // v.push_back(5);
//   // for (ft::vector<int>::const_iterator itr = v.begin(); itr != v.end();
//   // itr++)
//   //   std::cout << *itr << "\n";
//   // v.reserve(100);
//   // std::cout << s.size() << " " << v.size() << "\n";
//   // std::cout << s.capacity() << " " << v.capacity() << "\n";
//   // FIXME
// }

int main(void) {
  ft::vector<int> v(5, 1);
  ft::vector<int> copy = v;

  v.clear();

  std::cout << "========== original ===========\n";
  std::cout << "size : " << v.size() << "\n";
  for (ft::vector<int>::iterator itr = v.begin(); itr != v.end(); itr++)
    std::cout << *itr << "\n";
  std::cout << "========== copy ===========\n";
  std::cout << "size : " << copy.size() << "\n";
  for (ft::vector<int>::iterator itr = copy.begin(); itr != copy.end(); itr++)
    std::cout << *itr << "\n";
}
