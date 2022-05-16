/**
 * @file vector.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for vector container
 * @date 2022-05-14
 */

#include <iterator>
#include <vector>

#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP_

namespace ft {
template <typename T, typename Alloc = std::allocator<T>>
class vector {
  // SECTION : member types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef Alloc::pointer pointer;
  typedef Alloc::const_pointer const_pointer;
  // typedef  iterator;

 private:
 public:
  // SECTION : constructors
  vector(void) vector(void)
  // SECTION : operator=
  // SECTION : iterators
  // SECTION : capacity
  // SECTION : element access
  // SECTION : modifiers
  // SECTION : get_allocator
};
}  // namespace ft

#endif
