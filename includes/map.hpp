/**
 * @file map.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for map container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_MAP_HPP_
#define FT_CONTAINERS_INCLUDES_MAP_HPP_

#define FT_NOEXCEPT_ throw()

#include <functional>
#include <memory>

#include "algorithm.hpp"
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

  class value_compare {
   private:
    Compare v_comp_;

   public:
    value_compare(Compare c) : v_comp_(c) {}
    bool operator()(const value_type& x, const value_type& y) const {
      return v_comp_(x.first, y.first);
    }
  };

  typedef Compare key_compare;
  typedef typename Alloc::template rebind<value_type>::other allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

 private:
  typedef RbTree<value_type, value_compare, allocator_type> Base_;
  typedef typename Base_::Node Node_;
  typedef typename Base_::NodePtr NodePtr_;

  key_compare comp_;
  allocator_type alloc_;
  Base_ tree_;

 public:
  typedef typename Base_::iterator iterator;
  typedef typename Base_::const_iterator const_iterator;
  typedef typename Base_::const_reverse_iterator const_reverse_iterator;
  typedef typename Base_::reverse_iterator reverse_iterator;
  typedef typename iterator_traits<iterator>::difference_type difference_type;
  typedef size_t size_type;

  // Constructors
  // #1 empty : empty container with no element
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : comp_(comp), alloc_(alloc), tree_(Base_(value_compare(comp), alloc)) {}

  // #2 range : construct with as many elements as the range [first, last)
  template <typename InputIterator>
  map(InputIterator first,
      typename enable_if<is_input_iterator<InputIterator>::value,
                         InputIterator>::type last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : comp_(comp), alloc_(alloc), tree_(Base_(value_compare(comp), alloc)) {
    for (; first != last; first++) insert(*first);
  }

  // #3 copy constructor
  map(const map& original)
      : comp_(original.comp_),
        alloc_(original.alloc_),
        tree_(Base_(original.tree_)) {}

  // Destructor
  ~map(void) {}

  // Assignment operator overload
  map& operator=(const map& rhs) {
    clear();
    comp_ = rhs.comp_;
    alloc_ = rhs.alloc_;
    tree_ = Base_(rhs.tree_);
    return *this;
  }

  // Iterators
  iterator begin(void) FT_NOEXCEPT_ { return tree_.begin(); }

  const_iterator begin(void) const FT_NOEXCEPT_ { return tree_.begin(); }

  iterator end(void) FT_NOEXCEPT_ { return tree_.end(); }

  const_iterator end(void) const FT_NOEXCEPT_ { return tree_.end(); }

  reverse_iterator rbegin(void) FT_NOEXCEPT_ { return tree_.rbegin(); }

  const_reverse_iterator rbegin(void) const FT_NOEXCEPT_ {
    return tree_.rbegin();
  }

  reverse_iterator rend(void) FT_NOEXCEPT_ { return tree_.rend(); }

  const_reverse_iterator rend(void) const FT_NOEXCEPT_ { return tree_.rend(); }

  // Capacity
  bool empty(void) const FT_NOEXCEPT_ { return (tree_.GetSize() == 0); }

  size_type size(void) const FT_NOEXCEPT_ { return tree_.GetSize(); }

  size_type max_size(void) const FT_NOEXCEPT_ {
    // const size_type diff_max =
    //     std::numeric_limits<size_type>::max() / sizeof(Node_);
    // const size_type alloc_max = tree_.MaxSize();
    // return std::min(diff_max, alloc_max);
    return tree_.MaxSize();
  }

  // Element Access
  // NOTE: after making insert, replace tree_.insert to insert
  mapped_type& operator[](const key_type& key) {
    NodePtr_ node = tree_.Search(ft::make_pair(key, mapped_type())).base();
    return (node->is_nil)
               ? (*(insert(ft::make_pair(key, mapped_type())).first)).second
               : node->key.second;
  }

  // single element
  pair<iterator, bool> insert(const value_type& val) {
    return tree_.Insert(val);
  }

  // single element at a given position
  iterator insert(iterator position, const value_type& val) {
    return (val.first > (*position).first)
               ? tree_.Insert(val, position.base()).first
               : insert(val).first;
  }

  // range
  template <typename InputIterator>
  void insert(InputIterator first,
              typename enable_if<is_input_iterator<InputIterator>::value,
                                 InputIterator>::type last) {
    for (; first != last; first++) insert(*first);
  }

  // sigle element at a given position
  void erase(iterator position) { tree_.Delete(position.base()); }

  // single element with a given key
  size_type erase(const key_type& key) {
    size_type original = size();
    tree_.Delete(NULL, ft::make_pair(key, mapped_type()));
    return original - size();
  }

  // range
  void erase(iterator first, iterator last) {
    for (; first != last; ++first) tree_.Delete(first.base());
  }

  void swap(map& x) { tree_.swap(x.tree_); }

  void clear(void) { tree_.ClearPreOrder(tree_.GetRoot()); }

  // Observers
  key_compare key_comp(void) const { return comp_; }

  value_compare value_comp(void) const { return value_compare(comp_); }

  // Operations
  iterator find(const key_type& k) {
    return tree_.Search(ft::make_pair(k, mapped_type()));
  }

  const_iterator find(const key_type& k) const {
    return const_iterator(tree_.Search(ft::make_pair(k, mapped_type())).base());
  }
  size_type count(const key_type& k) const {
    return tree_.Search(ft::make_pair(k, mapped_type())).base()->is_nil ? 0 : 1;
  }

  iterator lower_bound(const key_type& key) {
    return tree_.LowerBound(ft::make_pair(key, mapped_type()));
  }

  const_iterator lower_bound(const key_type& key) const {
    return tree_.LowerBound(ft::make_pair(key, mapped_type()));
  }

  iterator upper_bound(const key_type& key) {
    return tree_.UpperBound(ft::make_pair(key, mapped_type()));
  }

  const_iterator upper_bound(const key_type& key) const {
    return tree_.UpperBound(ft::make_pair(key, mapped_type()));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  pair<iterator, iterator> equal_range(const key_type& key) {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  // Allocator
  allocator_type get_allocator(void) const FT_NOEXCEPT_ { return alloc_; }
};

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  return (lhs.size() == rhs.size() &&
          equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs) {
  return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                 rhs.end());
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
  x.swap(y);
}

}  // namespace ft

#endif
