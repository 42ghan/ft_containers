/**
 * @file vector.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for vector container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP_

#include <algorithm>
#include <exception>
#include <iterator_traits.hpp>
#include <limits>
#include <memory>
#include <vector>

namespace ft {
// SECTION : vector base class (RAII wrapper)
template <typename T, typename Alloc = std::allocator<T> >
class VectorBase {
 protected:
  // type definitions
  typedef T value_type;
  typedef typename _alloc_traits::pointer pointer;

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
  typedef typename allocator_traits<allocator_type> alloc_traits;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef typename alloc_traits::reference reference;
  typedef typename alloc_traits::const_reference const_reference;
  typedef typename Base_::pointer pointer;
  typedef typename alloc_traits::const_pointer const_pointer;
  typedef pointer iterator;              // FIXME
  typedef const_pointer const_iterator;  // FIXME
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
    // FIXME : gcc uses push_back
  }

  // #4 copy constructor (keeps and uses a copy of x's alloc)
  vector(const vector& x) : base_(x.size(), x.alloc_) {
    uninitialized_copy(x.begin(), x.end(), begin_);
  }

  // destructor
  ~vector(void)  // NON-THROWING
  {
    for (iterator itr = begin(); itr != end(); itr++) alloc_.destroy(itr);
  }

  // SECTION : operator=
  // preserves the current allocator
  vector& operator=(const vector& x) {
    vector temp(a);
    swap<T>(*this, temp);
    return *this;
  }

  // SECTION : iterators
  iterator begin(void)  // NON-THROWING
  {
    return iterator(begin_);
  }

  const_iterator begin(void) const  // NON-THROWING
  {
    return const_cast<const_pointer> begin_;
  }

  reverse_iterator rbegin(void)  // NON-THROWING
  {}

  const_reverse_iterator rbegin(void) const  // NON-THROWING
  {}

  iterator end(void)  // NON-THROWING
  {
    return end_;
  }

  const_iterator end(void) const  // NON-THROWING
  {
    return const_cast<const_pointer> end_;
  }

  reverse_iterator rend(void)  // NON-THROWING
  {}

  const_reverse_iterator rend(void) const  // NON-THROWING
  {}

  // SECTION : capacity
  size_type size(void) const  // NON-THROWING
  {
    return size_type(end_ - begin_);
  }

  size_type max_size(void) const  // NON-THROWING
  {
    const size_type diff_max =
        std::numeric_limits<ptrdiff_t>::max() / sizeof(value_type);
    const size_type alloc_max = alloc_traits::max_size(alloc_);
    return std::min(diff_max, alloc_max);
  }

  void resize(size_type n, value_type val = value_type()) {}

  size_type capacity(void) const  // NON-THROWING
  {
    return size_type(end_of_storage_ - begin_);
  }

  bool empty(void) const  // NON-THROWING
  {
    return begin() == end();
  }

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
