/**
 * @file utility.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief Implementations of pair & make_pair
 * @date 2022-05-27
 */

#ifndef FT_CONTAINERS_INCLUDES_UTILITY_HPP_
#define FT_CONTAINERS_INCLUDES_UTILITY_HPP_

namespace ft {
// pair
template <typename T, typename U>
struct pair {
  typedef T first_type;
  typedef U second_type;

  first_type first;
  second_type second;

  // Constructors
  // default (1)
  pair(void) : first(first_type()), second(second_type()) {}

  // copy (2)
  template <typename V, typename W>
  pair(const pair<V, W>& original)
      : first(original.first), second(original.second) {}

  // initialization (3)
  pair(const first_type& a, const second_type& b) : first(a), second(b) {}
};

// pair relational operators
template <typename T, typename U>
bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs) {
  return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <typename T, typename U>
bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename U>
bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <typename T, typename U>
bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
  return !(rhs < lhs);
}

template <typename T, typename U>
bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs) {
  return rhs < lhs;
}

template <typename T, typename U>
bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
  return !(lhs < rhs);
}

// make_pair
template <typename T, typename U>
pair<T, U> make_pair(T x, U y) {
  return pair<T, U>(x, y);
}
}  // namespace ft

#endif
