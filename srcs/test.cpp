#include <iostream>
#include <string>

#ifdef STD
#include <map>
#include <set>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <set.hpp>
#include <stack.hpp>
#include <vector.hpp>
#endif

#include <cstdlib>

#define VECTOR 0
#define STACK 1
#define MAP 2
#define SET 3

template <typename T>
void PrintVector(ft::vector<T>& v) {
  std::cout << "\nSIZE : " << v.size() << "\n";
  std::cout << "Contents :\n";
  for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << "  " << *it << "\n";
  std::cout << "\n========================================\n\n";
}

// SECTION : vector tests
void TestVector(void) {
  ft::vector<std::string> v;
  ft::vector<std::string> v1(10, "hi");

  // assign test
  std::cout << "VECTOR - ASSIGN\n\n";
  v.assign(v1.begin(), v1.end());
  v1.assign(10, "bye");
  PrintVector(v);
  PrintVector(v1);

  // at / subscript test
  std::cout << "VECTOR - AT/[]\n\n";
  std::string& fifth = v.at(5);
  std::cout << "AT(5) : " << fifth << "\n";
  std::string& sixth = v[6];
  std::cout << "[6] : " << fifth << "\n";
  fifth = "hello";
  sixth = "olah";
  std::cout << "after changing values...\n";
  std::cout << "check out of range exception\n";
  try {
    std::cout << "Try accessing AT(-1)\n";
    v.at(-1);
  } catch (const std::out_of_range& e) {
    std::cout << "out_of_range thrown!\n";
  }
  PrintVector(v);

  // front & back
  std::cout << "VECTOR - front & back\n\n";
  std::string& front = v.front();
  std::string& back = v.back();
  front = "front";
  back = "back";
  PrintVector(v);
  // NOTE : accessing empty vector's front/back is UB
  // ft::vector<std::string> v2;
  // v2.back() = "blah";

  // capacity, reserve
  std::cout << "VECTOR - capacity & reserve\n\n";
  {
    ft::vector<std::string> v3(100);
    std::cout << "BEFORE RESERVE : " << v3.capacity() << "\n";
    v3.reserve(50);
    std::cout << "AFTER RESERVE(50) : " << v3.capacity() << "\n";
    v3.reserve(200);
    std::cout << "AFTER RESERVE(200) : " << v3.capacity() << "\n";
    try {
      v3.reserve(v3.max_size() + 1);
    } catch (std::length_error& e) {
      std::cout << "AFTER RESERVE(MAX_SIZE) : length_error thrown"
                << "\n";
    }
  }
}

// SECTION : stack tests
void TestStack(void) {}

// SECTION : map tests
void TestMap(void) {}

// SECTION : set tests
void TestSet(void) {}

int main(void) {
  TestVector();
  TestStack();
  TestMap();
  TestSet();

  // system("leaks ft_containers");
  return EXIT_SUCCESS;
}
