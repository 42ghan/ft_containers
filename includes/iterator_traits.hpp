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
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
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

  // Constructors
  reverse_iterator(void) : current_(Iterator()) {}

  reverse_iterator(const iterator_type& itr) : current_(itr) {}

  reverse_iterator(const reverse_iterator& original) { *this = original; }

  // Destructor
  ~reverse_iterator(void) {}

  // Copy Assignment operator overload
  reverse_iterator& operator=(const reverse_iterator& rhs) {
    current_ = rhs.current_;
    return *this;
  }

  // increment & decrement
  reverse_iterator& operator++(void) FT_NOEXCEPT_ {
    --current_;
    return *this;
  }

  reverse_iterator operator++(int) FT_NOEXCEPT_ {
    return reverse_iterator(current_--);
  }

  reverse_iterator& operator--(void) FT_NOEXCEPT_ {
    ++current_;
    return *this;
  }

  reverse_iterator operator--(int) FT_NOEXCEPT_ {
    return reverse_iterator(current_++);
  }

  // subscript
  reference operator[](difference_type n) const FT_NOEXCEPT_ {
    return *(*this + n);
  }

  // dereference & reference
  reference operator*(void) const FT_NOEXCEPT_ { return *current_; }

  pointer operator->(void) const FT_NOEXCEPT_ { return current_; }

  // add or subtract difference
  reverse_iterator& operator+=(difference_type n) const FT_NOEXCEPT_ {
    current_ -= n;
    return *this;
  }

  reverse_iterator operator+(difference_type n) const FT_NOEXCEPT_ {
    return reverse_iterator(current_ - n);
  }

  reverse_iterator& operator-=(difference_type n) const FT_NOEXCEPT_ {
    current_ += n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const FT_NOEXCEPT_ {
    return reverse_iterator(current_ + n);
  }

  const Iterator& base(void) const FT_NOEXCEPT_ { return current_; }
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const reverse_iterator<IteratorL>& lhs,
                       const reverse_iterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const reverse_iterator<IteratorL>& lhs,
                       const reverse_iterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator>(const reverse_iterator<IteratorL>& lhs,
                      const reverse_iterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() < rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator<(const reverse_iterator<IteratorL>& lhs,
                      const reverse_iterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() > rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator>=(const reverse_iterator<IteratorL>& lhs,
                       const reverse_iterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() <= rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator<=(const reverse_iterator<IteratorL>& lhs,
                       const reverse_iterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() >= rhs.base();
}

template <typename Iterator>
inline reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& itr) FT_NOEXCEPT_ {
  return reverse_iterator<Iterator>(itr.base() - n);
}

template <typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) FT_NOEXCEPT_ {
  return rhs.base() - lhs.base();
}
}  // namespace ft

#endif
