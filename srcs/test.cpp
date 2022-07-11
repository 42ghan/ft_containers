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
  std::cout << "VECTOR - FRONT & BACK\n\n";
  std::string& front = v.front();
  std::string& back = v.back();
  front = "front";
  back = "back";
  PrintVector(v);
  // NOTE : accessing empty vector's front/back is UB
  // ft::vector<std::string> v2;
  // v2.back() = "blah";

  // capacity, reserve
  std::cout << "VECTOR - CAPACITY & RESERVE\n\n";
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
    std::cout << "\n========================================\n\n";
  }

  // clear & empty
  std::cout << "VECTOR - CLEAR & EMPTY\n\n";
  {
    ft::vector<int> v4(10000000);
    std::cout << "SIZE BEFORE CLEAR : " << v4.size()
              << ", EMPTY? : " << (v4.empty() ? "YES" : "NO") << "\n";
    v4.clear();
    std::cout << "SIZE AFTER CLEAR : " << v4.size()
              << ", EMPTY? : " << (v4.empty() ? "YES" : "NO") << "\n";
    std::cout << "\n========================================\n\n";
  }

  // insert, erase, push_back & pop_back
  std::cout << "VECTOR - INSERT, ERASE, PUSH_BACK & POP_BACK";
  PrintVector(v);
  v.insert(v.begin() + 2, "single inserted!");
  PrintVector(v);
  v.insert(v.end() - 4, 7, "multiple inserted!");
  PrintVector(v);
  v.insert(v.begin() + 1, v1.begin(), v1.end());
  PrintVector(v);
  v.erase(v.begin());
  PrintVector(v);
  v.erase(v.end() - 1);
  PrintVector(v);
  v.erase(v.begin() + 3, v.end() - 7);
  PrintVector(v);
  v.push_back("push_back");
  PrintVector(v);
  v.pop_back();
  PrintVector(v);

  // swap
  std::cout << "VECTOR - SWAP";
  PrintVector(v);
  PrintVector(v1);
  ft::swap(v, v1);
  PrintVector(v);
  PrintVector(v1);
}

// SECTION : stack tests
void TestStack(void) {
  ft::vector<int> v(20);
  ft::vector<int>::iterator it = v.begin(), ite = v.end();
  for (int i = 0; it != ite; ++it, ++i) *it = i;
  ft::stack<int, ft::vector<int> > st;
  ft::stack<int, ft::vector<int> > st1(v);

  // empty & size
  std::cout << "STACK - EMPTY & SIZE\n\n";
  std::cout << "SIZE : " << st.size()
            << ", EMPTY? : " << (st.empty() ? "YES" : "NO") << "\n";
  std::cout << "SIZE : " << st1.size()
            << ", EMPTY? : " << (st1.empty() ? "YES" : "NO") << "\n";
  std::cout << "\n========================================\n\n";

  // push, pop & top
  std::cout << "STACK - PUSH, POP & TOP\n\n";
  st.push(4);
  st.push(2);
  st.push(42);
  std::cout << "TOP : " << st.top() << ", SIZE : " << st.size() << "\n";
  st.top() = 24;
  std::cout << "TOP AFTER CHANGE : " << st.top() << ", SIZE : " << st.size()
            << "\n";
  st.pop();
  st.pop();
  st.pop();
  std::cout << "SIZE : " << st.size()
            << ", EMPTY? : " << (st.empty() ? "YES" : "NO") << "\n";
  std::cout << "\n========================================\n\n";
}

// SECTION : map tests
void TestMap(void) {
  ft::vector<ft::pair<int, char> > v;
  v.reserve(10);
  for (int i = 0; i < 10; ++i) v.push_back(ft::make_pair(i, 'a' + i));
  ft::map<int, char> m;
  ft::map<int, char> m1(v.begin(), v.end());
  ft::map<int, char> m1_copy(m1);

  // assignment operator, empty, size, find & count
  std::cout << "MAP - ASSIGNMENT OPERATOR, EMPTY, SIZE, FIND & COUNT\n\n";
  std::cout << "SIZE : " << m.size()
            << ", EMPTY? : " << (m.empty() ? "YES" : "NO") << "\n";
  std::cout << "SIZE : " << m1.size()
            << ", EMPTY? : " << (m1.empty() ? "YES" : "NO") << "\n";
  m = m1;
  std::cout << "SIZE : " << m.size()
            << ", EMPTY? : " << (m.empty() ? "YES" : "NO") << "\n";
  ft::pair<int, char> p = *(m.find(0));
  std::cout << "FIRST : " << p.first << ", SECOND : " << p.second
            << ", COUNT : " << m.count(0) << "\n";
  std::cout << "FOUND? : " << ((m.find(10) == m.end()) ? "NO" : "YES")
            << ", COUNT : " << m.count(10) << "\n";
  std::cout << "\n========================================\n\n";

  // random order sorting, accessing, insert, erase
  std::cout << "SET - SORTING, ACCESSING, INSERT, ERASE\n\n";
  {
    ft::map<int, int> m2;
    for (int i = 0; i < 100; ++i) {
      int k = rand();
      m2.insert(ft::make_pair(k, k));
    }
    ft::map<int, int>::iterator it = m2.begin(), ite = m2.end();
    for (; it != ite; ++it) std::cout << (*it).first << "\n";
    --(--(--it));
    std::cout << "CHECK [] ACCESS FOR " << (*it).first << " : "
              << m2[(*it).first] << "\n";
    m2.insert(++(++(++m2.begin())), ft::make_pair(24075629, -42));
    it = m2.begin();
    ite = m2.end();
    for (; it != ite; ++it) std::cout << (*it).first << "\n";
    ft::vector<ft::pair<int, int> > v1;
    v1.reserve(700);
    for (int i = 0; i < 700; ++i) v.push_back(ft::make_pair(i, i));
    m2.insert(v.begin(), v.end());
    it = m2.begin();
    for (; it != ite; ++it) std::cout << (*it).first << "\n";
    std::cout << "SIZE : " << m2.size() << "\n";
    std::cout << "ERASED? : " << m2.erase(700) << ", SIZE : " << m2.size()
              << "\n";
    std::cout << "ERASED? : " << m2.erase(699) << ", SIZE : " << m2.size()
              << "\n";
    m2.erase(m2.begin());
    m2.erase(--m2.end());
    std::cout << "SIZE : " << m2.size() << "\n";
    m2.erase(m2.begin(), m2.end());
    std::cout << "SIZE : " << m2.size() << "\n";
  }

  // swap & clear
  std::cout << "SET - SWAP & CLEAR\n\n";
  {
    ft::map<int, int> m3;
    ft::map<int, int> m4;
    for (int i = 0; i < 10; ++i) m3.insert(ft::make_pair(i, i));
    for (int i = 10; i < 20; ++i) m4.insert(ft::make_pair(i, i));
    ft::swap(m3, m4);
    ft::map<int, int>::iterator it3 = m3.begin(), ite3 = m3.end(),
                                it4 = m4.begin(), ite4 = m4.end();
    for (; it3 != ite3; ++it3) std::cout << (*it3).first << "\n";
    for (; it4 != ite4; ++it4) std::cout << (*it4).first << "\n";
    m3.clear();
    std::cout << "SIZE AFTER CLEAR : " << m3.size() << "\n";
  }
}

// SECTION : set tests
void TestSet(void) {
  ft::vector<int> v;
  v.reserve(10);
  for (int i = 0; i < 10; ++i) v.push_back(i);
  ft::set<int> s;
  ft::set<int> s1(v.begin(), v.end());
  ft::set<int> s1_copy(s1);

  // assignment operator, empty, size, find & count
  std::cout << "SET - ASSIGNMENT OPERATOR, EMPTY, SIZE, FIND & COUNT\n\n";
  std::cout << "SIZE : " << s.size()
            << ", EMPTY? : " << (s.empty() ? "YES" : "NO") << "\n";
  std::cout << "SIZE : " << s1.size()
            << ", EMPTY? : " << (s1.empty() ? "YES" : "NO") << "\n";
  s = s1;
  std::cout << "SIZE : " << s.size()
            << ", EMPTY? : " << (s.empty() ? "YES" : "NO") << "\n";
  int p = *(s.find(0));
  std::cout << "KEY : " << p << ", COUNT : " << s.count(0) << "\n";
  std::cout << "FOUND? : " << ((s.find(10) == s.end()) ? "NO" : "YES")
            << ", COUNT : " << s.count(10) << "\n";
  std::cout << "\n========================================\n\n";

  // random order sorting, accessing, insert, erase
  std::cout << "SET - SORTING, ACCESSING, INSERT, ERASE\n\n";
  {
    ft::set<int> s2;
    for (int i = 0; i < 100; ++i) {
      int k = rand();
      s2.insert(k);
    }
    ft::set<int, int>::iterator it = s2.begin(), ite = s2.end();
    for (; it != ite; ++it) std::cout << *it << "\n";
    s2.insert(++(++(++s2.begin())), 24075629);
    it = s2.begin();
    ite = s2.end();
    for (; it != ite; ++it) std::cout << *it << "\n";
    ft::vector<int> v1;
    v1.reserve(700);
    for (int i = 0; i < 700; ++i) v.push_back(i);
    s2.insert(v.begin(), v.end());
    it = s2.begin();
    for (; it != ite; ++it) std::cout << *it << "\n";
    std::cout << "SIZE : " << s2.size() << "\n";
    std::cout << "ERASED? : " << s2.erase(700) << ", SIZE : " << s2.size()
              << "\n";
    std::cout << "ERASED? : " << s2.erase(699) << ", SIZE : " << s2.size()
              << "\n";
    s2.erase(s2.begin());
    s2.erase(--s2.end());
    std::cout << "SIZE : " << s2.size() << "\n";
    s2.erase(s2.begin(), s2.end());
    std::cout << "SIZE : " << s2.size() << "\n";
  }

  // swap, clear
  std::cout << "SET - SWAP & CLEAR\n\n";
  {
    ft::set<int> s3;
    ft::set<int> s4;
    for (int i = 0; i < 10; ++i) s3.insert(i);
    for (int i = 10; i < 20; ++i) s4.insert(i);
    ft::swap(s3, s4);
    ft::set<int>::iterator it3 = s3.begin(), ite3 = s3.end(), it4 = s4.begin(),
                           ite4 = s4.end();
    for (; it3 != ite3; ++it3) std::cout << *it3 << "\n";
    for (; it4 != ite4; ++it4) std::cout << *it4 << "\n";
    s3.clear();
    std::cout << "SIZE AFTER CLEAR : " << s3.size() << "\n";
  }
}

int main(void) {
  TestVector();
  TestStack();
  TestMap();
  TestSet();

  // system("leaks ft_containers");
  return EXIT_SUCCESS;
}
