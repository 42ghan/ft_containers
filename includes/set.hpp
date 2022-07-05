/**
 * @file set.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for set container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_SET_HPP_
#define FT_CONTAINERS_INCLUDES_SET_HPP_

#define FT_NOEXCEPT_ throw()

#include <functional>
#include <memory>

#include "algorithm.hpp"
#include "iterator_traits.hpp"
#include "rbtree.hpp"
#include "utility.hpp"

namespace ft {
template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key> >
class set {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

 private:
  typedef RbTree<key_type, key_compare, allocator_type> Base_;
  typedef typename Base_::Node Node_;
  typedef typename Base_::NodePtr NodePtr_;

  key_compare comp_;
  allocator_type alloc_;
  Base_ tree_;

 public:
  typedef typename Base_::const_iterator iterator;
  typedef typename Base_::const_iterator const_iterator;
  typedef typename Base_::const_reverse_iterator const_reverse_iterator;
  typedef typename Base_::const_reverse_iterator reverse_iterator;
  typedef typename iterator_traits<iterator>::difference_type difference_type;
  typedef size_t size_type;

  // Constructors
  // #1 empty : empty container with no element
  explicit set(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : comp_(comp), alloc_(alloc), tree_(Base_(comp_, alloc_)) {}

  // #2 range : constructs with as many elements as the range [first, last)
  template <typename InputIterator>
  set(InputIterator first,
      typename enable_if<is_input_iterator<InputIterator>::value,
                         InputIterator>::type last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : comp_(comp), alloc_(alloc), tree_(Base_(comp_, alloc_)) {
    for (; first != last; ++first) insert(*first);
  }

  // #3 copy constructor
  set(const set& original)
      : comp_(original.comp_),
        alloc_(original.alloc_),
        tree_(Base_(original.tree_)) {}

  // Destructor
  ~set(void) {}

  // Assignment operator overload (Deep copy)
  set& operator=(const set& rhs) {
    comp_ = rhs.comp_;
    alloc_ = rhs.alloc_;
    tree_.~Base_();
    tree_ = Base_(rhs.tree_);
    return *this;
  }

  // Iterators
  // NOTE : check dereferencing when empty
  iterator begin(void) const FT_NOEXCEPT_ { return tree_.begin(); }

  iterator end(void) const FT_NOEXCEPT_ { return tree_.end(); }

  reverse_iterator rbegin(void) const FT_NOEXCEPT_ { return tree_.rbegin(); }

  reverse_iterator rend(void) const FT_NOEXCEPT_ { return tree_.rend(); }

  // Capacity
  bool empty(void) const FT_NOEXCEPT_ { return (tree_.GetSize() == 0); }

  size_type size(void) const FT_NOEXCEPT_ { return tree_.GetSize(); }

  size_type max_size(void) const FT_NOEXCEPT_ { return tree_.MaxSize(); }

  // Modifiers
  // single element
  pair<iterator, bool> insert(const value_type& val) {
    return tree_.Insert(val);
  }

  // single element at a given position
  iterator insert(iterator position, const value_type& val) {
    return (position != end() && val > *position)
               ? tree_.Insert(val, position.base()).first
               : insert(val).first;
  }

  // range
  template <typename InputIterator>
  void insert(InputIterator first,
              typename enable_if<is_input_iterator<InputIterator>::value,
                                 InputIterator>::type last) {
    for (; first != last; ++first) insert(*first);
  }

  // single element at a given position
  void erase(iterator position) { tree_.Delete(position.base()); }

  // single element with a given key
  size_type erase(const value_type& val) {
    size_type original = size();
    tree_.Delete(NULL, val);
    return original - size();
  }

  // range
  void erase(iterator first, iterator last) {
    for (; first != last;) {
      iterator tmp = first;
      ++tmp;
      tree_.Delete(first.base());
      first = tmp;
    }
  }

  void swap(set& x) { tree_.swap(x.tree_); }

  void clear(void) {
    // FIXME : LEAK...
    tree_.ClearPostOrder(tree_.GetRoot());
  }

  // Observers
  key_compare key_comp(void) const { return comp_; }

  value_compare value_comp(void) const { return comp_; }

  // Operations
  iterator find(const value_type& val) const { return tree_.Search(val); }

  size_type count(const value_type& val) const {
    return iterator(tree_.Search(val)) == tree_.end() ? 0 : 1;
  }

  iterator lower_bound(const value_type& val) const {
    return tree_.LowerBound(val);
  }

  iterator upper_bound(const value_type& val) const {
    return tree_.UpperBound(val);
  }

  pair<iterator, iterator> equal_range(const value_type& val) const {
    return ft::make_pair(lower_bound(val), upper_bound(val));
  }

  // Allocator
  allocator_type get_allocator(void) const FT_NOEXCEPT_ { return alloc_; }
};

template <typename Key, typename Compare, typename Alloc>
bool operator==(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return (lhs.size() == rhs.size() &&
          equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename Key, typename Compare, typename Alloc>
bool operator!=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <typename Key, typename Compare, typename Alloc>
bool operator<(const set<Key, Compare, Alloc>& lhs,
               const set<Key, Compare, Alloc>& rhs) {
  return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                 rhs.end());
}

template <typename Key, typename Compare, typename Alloc>
bool operator<=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <typename Key, typename Compare, typename Alloc>
bool operator>(const set<Key, Compare, Alloc>& lhs,
               const set<Key, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

template <typename Key, typename Compare, typename Alloc>
bool operator>=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <typename Key, typename Compare, typename Alloc>
void swap(set<Key, Compare, Alloc>& x, set<Key, Compare, Alloc>& y) {
  x.swap(y);
}
}  // namespace ft

#endif
