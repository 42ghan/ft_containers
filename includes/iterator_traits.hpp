/**
 * @file iterator_traits.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for iterator traits
 * @date 2022-05-17
 */

#ifndef FT_CONTAINERS_INCLUDES_ITERATOR_TRAITS_HPP_
#define FT_CONTAINERS_INCLUDES_ITERATOR_TRAITS_HPP_

namespace ft {
struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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

template <typename Category,              // iterator::iterator_category
          typename T,                     // iterator::value_type
          typename Distance = ptrdiff_t,  // iterator::difference_type
          typename Pointer = T*,          // iterator::pointer
          typename Reference = T&         // iterator::reference
          >
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

template <typename Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference> {
 protected:
  Iterator current_;
  typedef iterator_traits<Iterator> traits_type_;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type_::iterator_category iterator_category;
  typedef typename traits_type_::value_type value_type;
  typedef typename traits_type_::difference_type difference_type;
  typedef typename traits_type_::pointer pointer;
  typedef typename traits_type_::pointer reference;
}
}  // namespace ft

#endif
