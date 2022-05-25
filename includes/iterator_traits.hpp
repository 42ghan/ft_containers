/**
 * @file iterator_traits.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for iterator traits
 * @date 2022-05-17
 */

#ifndef FT_CONTAINERS_INCLUDES_ITERATOR_TRAITS_HPP_
#define FT_CONTAINERS_INCLUDES_ITERATOR_TRAITS_HPP_

namespace ft {
template <typename Iter>
struct iterator_traits {
  typedef Iter::difference_type difference_type;
  typedef Iter::value_type value_type;
  typedef Iter::pointer pointer;
  typedef Iter::reference reference;
  typedef Iter::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};
}  // namespace ft

#endif
