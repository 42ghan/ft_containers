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

template <typename T, typename Alloc>
struct VectorBase {
  //typedef ;
};

template <typename T, typename Alloc = std::allocator<T> >
class vector {
 private:
  // SECTION : member types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_traits<allocator_type> alloc_traits;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef Alloc::pointer pointer;
  typedef Alloc::const_pointer const_pointer;
  typedef typename alloc_traits<allocator_type>::pointer iterator;
  typedef typename alloc_traits<allocator_type>::const_pointer const_iterator
  // typedef  reverse_iterator
  // typedef  const_reverse_iterator
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;

 public:
  // SECTION : constructors & destructor
  // #1 default : empty container constructor (no elem)
  vector(const allocator_type& alloc = allocator_type()) {}
  // #2 fill : construct a container with n elements, fill them with val
  vector(size_type n, const value_type& val, const allocator_type& alloc = allocator_type()) {}
  // #3 range : 
  template <typename InputIterator>
  vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {}
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
}  // namespace ft

#endif
