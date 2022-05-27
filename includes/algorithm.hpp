/**
 * @file algorithm.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief Implementations of lexicographical_compare & equal
 * @date 2022-05-27
 */

#ifndef FT_CONTAINERS_INCLUDES_ALGORITHM_HPP_
#define FT_CONTAINERS_INCLUDES_ALGORITHM_HPP_

namespace ft {
// lexicographical comparison
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1)
      return false;
    else if (*first1 < *first2)
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2,
                             Compare comp) {
  while (first1 != last1) {
    if (first2 == last2 || !comp(*first1, *first2))
      return false;
    else if (comp(*first1, *first2))
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

// equal
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
           BinaryPredicate pred) {}
}  // namespace ft

#endif
