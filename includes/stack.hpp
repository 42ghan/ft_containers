/**
 * @file stack.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for stack container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_STACK_HPP_
#define FT_CONTAINERS_INCLUDES_STACK_HPP_

#include "vector.hpp"

namespace ft {
template <typename T, typename Container = vector<T> >
class stack {
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

  // constructors
  explicit stack(const container_type& cont = container_type()) : c(cont) {}

  // public member functions
  reference top(void) { return c.back(); }
  const_reference top(void) const { return c.back(); }
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  void push(const value_type& value) { c.push_back(value); }
  void pop(void) { c.pop_back(); }

  // friend relational operators
  template <typename U, typename V>
  friend bool operator==(const stack<U, V>& lhs, const stack<U, V>& rhs);

  template <typename U, typename V>
  friend bool operator<(const stack<U, V>& lhs, const stack<U, V>& rhs);

 protected:
  container_type c;
};

// relational operators
template <typename T, typename Container>
bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return lhs.c == rhs.c;
}

template <typename T, typename Container>
bool operator!=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return lhs.c < rhs.c;
}

template <typename T, typename Container>
bool operator<=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(rhs < lhs);
}

template <typename T, typename Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
  return rhs < lhs;
}

template <typename T, typename Container>
bool operator>=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif
