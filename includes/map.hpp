/**
 * @file map.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for map container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_MAP_HPP_
#define FT_CONTAINERS_INCLUDES_MAP_HPP_

#include <functional>
#include <map>
#include <memory>

#include "iterator_traits.hpp"
#include "rbtree.hpp"
#include "utility.hpp"

namespace ft {
template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<pair<const Key, Value> > >
class map {
 public:
  typedef Key key_type;
  typedef Value mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  //   typedef value_comp; NOTE : name for member function
  typedef typename Alloc::template rebind<value_type>::other alloator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

 private:
  typedef RbTree<value_type, key_compare, allocator_type> Base_;
  key_compare comp_;
  allocator_type alloc_;
  Base_ tree_;

 public:
  typedef RbTreeIterator<typename Base_::NodePtr> iterator;
  typedef RbTreeIterator<const typename Base_::NodePtr> const_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
  typedef iterator_traits<iterator>::difference_type difference_type;
  typedef size_t size_type;

  // Constructors
  // #1 empty : empty container with no element
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : tree_(Base_(comp, alloc)) {}

  // #2 range : construct with as many elements as the range [first, last)
  template <InputIterator>
  map(InputIterator first,
      typename enable_if<is_input_iterator<InputIterator>::value,
                         InputIterator>::type last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : tree_(Base_(comp, alloc)) {
    for (; first != last; first++) tree_.Insert(*first);
  }

  // #3 copy constructor

  // Destructor
  // Assignment operator overload
  // Iterators
  // Capacity
  // Element Access
  // Modifiers
  // Observers
  // Operations
  // Allocator
};
}  // namespace ft

#endif
