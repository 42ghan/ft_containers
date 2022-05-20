/**
 * @file vector.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for vector container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP_

#include <memory>
#include <vector>

namespace ft {
// SECTION : vector base class (RAII wrapper)
template <typename T, typename Alloc = std::allocator<T> >
class VectorBase {
 protected:
  // type definitions
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename _alloc_traits::difference_type difference_type;
  typedef typename _alloc_traits::pointer pointer;
  typedef typename _alloc_traits::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;

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
  typedef Alloc allocator_type;
  typedef allocator_traits<allocator_type> _alloc_traits;
  typedef typename _alloc_traits::size_type size_type;

  explicit VectorBase(const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    InitPointers_(0);
  }

  explicit VectorBase(const size_type n,
                      const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    InitPointers_(n);
  }

  virtual ~VectorBase(void) { delete begin_; }
};

template <typename T, typename Alloc = std::allocator<T> >
class vector : private VectorBase<T, Alloc> {
 private:
  typedef VectorBase<T, Alloc> Base_;
  Base_ base_;

  template <typename InputIterator>
  InitCopyRange_(InputIterator first, InputIterator last) {
    for (; first != last; first++)
      ;
  }

 public:
  // SECTION : member types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_traits<allocator_type> alloc_traits;
  typedef typename Base_::size_type size_type;
  typedef typename Base_::difference_type difference_type;
  typedef typename Base_::reference reference;
  typedef typename Base_::const_reference const_reference;
  typedef typename Base_::pointer pointer;
  typedef typename Base_::const_pointer const_pointer;
  typedef typename Base_::pointer iterator;
  typedef typename Base_::const_pointer const_iterator;
  // typedef  reverse_iterator
  // typedef  const_reverse_iterator

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

  // #3 range :
  template <typename InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type())
      : base_(alloc) {
    // gcc uses push_back
  }

  // #4 copy constructor (keeps and uses a copy of x's alloc)
  vector(const vector& x) {}
  // destructor
  ~vector(void) {}

  // SECTION : operator=
  // preserves the current allocator
  vector& operator=(const vector& x) {}

  // SECTION : iterators
  iterator begin(void) {}

  const_iterator begin(void) const {}

  reverse_iterator rbegin(void) {}

  const_reverse_iterator rbegin(void) const {}

  // SECTION : capacity
  size_type size(void) const {}

  size_type max_size(void) const {}

  void resize(size_type n, value_type val = value_type()) {}

  size_type capacity(void) const {}

  bool empty(void) const {}

  void reserve(size_type n) {}

  // SECTION : element access
  reference operator[](size_type n) {}

  const_reference operator[](size_type n) const {}

  reference at(size_type n) {}

  const_reference at(size_type n) const {}

  reference front(void) {}

  const_reference front(void) const {}

  reference back(void) {}

  const_reference back(void) const {}

  // SECTION : modifiers
  // range
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last) {}

  // fill
  void assign(size_type n, const value_type& val) {}

  void push_back(const value_type& val) {}

  void pop_back(void) {}

  // single element
  iterator insert(iterator position, const value_type& val) {}

  // fill
  void insert(iterator position, size_type n, const value_type& val) {}

  // range
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {}

  iterator erase(iterator position) {}

  iterator erase(iterator first, iterator last) {}

  void swap(vector& x) {}

  void clear(void) {}

  // SECTION : get_allocator
  allocator_type get_allocator(void) const {}
};
};  // namespace ft

#endif
