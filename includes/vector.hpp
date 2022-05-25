/**
 * @file vector.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for vector container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP_

#define FT_NOEXCEPT_ throw()

#include <algorithm>
#include <exception>
#include <iterator>
#include <iterator_traits.hpp>
#include <limits>
#include <memory>
#include <vector>

namespace ft {

// SECTION : vector iterator class
// implementation of random access iterator for ft::vector

template <typename Iterator, typaname Container>
class __VectorIterator {
 protected:
  Iterator current_;
  typedef typename ft::iterator_traits<Iterator> traits_type_;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::iterator_category value_type;
  typedef typename traits_type::iterator_category difference_type;
  typedef typename traits_type::iterator_category reference;
  typedef typename traits_type::iterator_category pointer;
}

// SECTION : vector base class (RAII wrapper)
template <typename T, typename Alloc = std::allocator<T> >
class VectorBase {
 protected:
  // member types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_traits<allocator_type> alloc_traits;
  typedef typename alloc_traits::pointer pointer;
  typedef typename alloc_traits::size_type size_type;

  pointer begin_;           // start of alloc
  pointer end_;             // end of sequence
  pointer end_of_storage_;  // end of alloc
  allocator_type alloc_;    // allocator

 private:
  void InitPointers_(const size_type n) {
    begin_ = alloc_.allocate(n);
    end_ = begin_;
    end_of_storage_ = begin_ + n;
  }

 public:
  explicit VectorBase(const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    InitPointers_(0);
  }

  explicit VectorBase(const size_type n,
                      const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    InitPointers_(n);
  }

  virtual ~VectorBase(void) {
    alloc_.deallocate(begin_, end_of_storage_ - begin_);
  }
};

template <typename T>
void swap(VectorBase<T>& a, VectorBase<T>& b) {
  swap(a.alloc_, b.alloc_);
  swap(a.begin_, b.begin_);
  swap(a.end_, b.end_);
  swap(a.end_of_storage_, b.end_of_storage_);
}

template <typename T, typename Alloc = std::allocator<T> >
class vector : private VectorBase<T, Alloc> {
 private:
  typedef VectorBase<T, Alloc> Base_;
  Base_ base_;

  // FIXME : Unnecessary...?
  // template <typename InputIterator>
  // InitCopyRange_(InputIterator first, InputIterator last) {
  //   for (; first != last; first++)
  //     ;
  // }

 public:
  // SECTION : member types
  typedef T value_type;
  typedef typename Base_::allocator_type allocator_type;
  typedef typename Base_::alloc_traits alloc_traits;
  typedef typename Base_::size_type size_type;
  typedef typename alloc_traits::difference_type difference_type;
  typedef typename Base_::pointer pointer;
  typedef typename alloc_traits::const_pointer const_pointer;
  typedef typename alloc_traits::reference reference;
  typedef typename alloc_traits::const_reference const_reference;
  typedef pointer iterator;                                  // FIXME
  typedef const_pointer const_iterator;                      // FIXME
  typedef std::reverse_iterator<iterator> reverse_iterator;  // FIXME
  typedef std::reverse_iterator<const_iterator>
      const_reverse_iterator;  // FIXME

  // SECTION : constructors & destructor
  // #1 default : empty container constructor (no elem)
  explicit vector(const allocator_type& alloc = allocator_type())
      : base_(alloc) {}

  // #2 fill : construct a container with n elements, fill them with val
  explicit vector(size_type n, const value_type& val,
                  const allocator_type& alloc = allocator_type())
      : base_(n, alloc) {
    end_ = std::uninitialized_fill_n<iterator, size_type, value_type>(begin_, n,
                                                                      val);
  }

  // #3 range : construct a container that will contain the same values in the
  // range [first, last)  template <typename InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type())
      : base_(alloc) {
    // FIXME : gcc uses push_back
  }

  // #4 copy constructor (keeps and uses a copy of x's alloc)
  vector(const vector& x) : base_(x.size(), x.alloc_) {
    end_ = std::uninitialized_copy<iterator, iterator, iterator>(
        x.begin(), x.end(), begin_);
  }

  // destructor
  ~vector(void) FT_NOEXCEPT_ { clear(); }

  // SECTION : operator=
  // preserves the current allocator
  vector& operator=(const vector& x) {
    vector temp(alloc_);
    swap<T>(*this, temp);
    return *this;
  }

  // SECTION : iterators
  iterator begin(void) FT_NOEXCEPT_ { return iterator(begin_); }

  const_iterator begin(void) const FT_NOEXCEPT_ {
    return const_cast<const_pointer> begin_;
  }

  reverse_iterator rbegin(void) FT_NOEXCEPT_ {}

  const_reverse_iterator rbegin(void) const FT_NOEXCEPT_ {}

  iterator end(void) FT_NOEXCEPT_ { return end_; }

  const_iterator end(void) const FT_NOEXCEPT_ {
    return const_cast<const_pointer> end_;
  }

  reverse_iterator rend(void) FT_NOEXCEPT_ {}

  const_reverse_iterator rend(void) const FT_NOEXCEPT_ {}

  // SECTION : capacity
  size_type size(void) const FT_NOEXCEPT_ { return size_type(end_ - begin_); }

  size_type max_size(void) const FT_NOEXCEPT_ {
    const size_type diff_max =
        std::numeric_limits<ptrdiff_t>::max() / sizeof(value_type);
    const size_type alloc_max = alloc_traits::max_size(alloc_);
    return std::min(diff_max, alloc_max);
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n <= size()) {
      for (iterator itr = begin() + n; itr != end(); itr++) alloc_.destory(itr);
      end_ = begin() + n;
    } else {
      if (n > capacity()) reserve(n);
      end_ = std::uninitialized_fill_n<iterator, size_type, value_type>(
          end(), n - size(), val);
    }
  }

  size_type capacity(void) const FT_NOEXCEPT_ {
    return size_type(end_of_storage_ - begin_);
  }

  bool empty(void) const FT_NOEXCEPT_ { return begin() == end(); }

  void reserve(size_type n) {
    if (n > max_size()) throw std::length_error();
    if (n > capacity()) {
      vector<value_type, allocator_type> temp(n, alloc_);
      temp.end() = std::uninitialized_copy<iterator, iterator, iterator>(
          begin(), end(), temp.begin());
      swap<value_type>(*this, temp);
    }
  }

  // SECTION : element access
  reference operator[](size_type n) FT_NOEXCEPT_ { return *(begin_ + n); }

  const_reference operator[](size_type n) const FT_NOEXCEPT_ {
    return *(begin_ + n);
  }

  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range();
    return (*this)[n];
  }

  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range();
    return (*this)[n];
  }

  reference front(void) FT_NOEXCEPT_ { return *begin(); }

  const_reference front(void) const FT_NOEXCEPT_ { return *begin(); }

  reference back(void) FT_NOEXCEPT_ { return *(end() - 1); }

  const_reference back(void) const FT_NOEXCEPT_ { return *(end() - 1); }

  // SECTION : modifiers
  // range
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last) {
    typename iterator_traits<value_type>::difference_type n =
        std::distance<InputIterator>(first, last);
    if (distance > capacity()) {
      vector<value_type, allocator_type> temp(n, alloc_);
      temp.end() = std::uninitialized_copy<iterator, iterator>(first, last,
                                                               temp() begin());
      swap<value_type>(*this, temp);
    } else {
      clear();
      end_ = std::uninitialized_copy<iterator, iterator>(first, last, begin());
    }
  }

  // fill
  void assign(size_type n, const value_type& val) {
    if (n > capacity()) {
      vector<value_type, allocator_type> temp(n, val, alloc_);
      swap<value_type>(*this, temp);
    } else {
      clear();
      end_ = std::uninitialized_fill_n<iterator, size_type, value_type>(begin(),
                                                                        n, val);
    }
  }

  void push_back(const value_type& val) {
    if (end_ != end_of_storage_) {
      alloc_.construct(end_, val);
      ++end_;
    } else {
      // FIXME : gcc reallocs and inserts
    }
  }

  void pop_back(void) {
    end_--;
    alloc_.destroy(end_);
  }

  // single element
  iterator insert(iterator position, const value_type& val) {}

  // fill
  void insert(iterator position, size_type n, const value_type& val) {}

  // range
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {}

  iterator erase(iterator position) {
    if (position == end_)
      pop_back();
    else {
      // FIXME
    }
  }

  iterator erase(iterator first, iterator last) {}

  void swap(vector& x) {}

  void clear(void) FT_NOEXCEPT_ {
    for (iterator itr = begin(); itr != end(); itr++) alloc_.destroy(itr);
  }

  // SECTION : get_allocator
  allocator_type get_allocator(void) const {}
};
};  // namespace ft

#endif
