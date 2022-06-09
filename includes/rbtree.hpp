/**
 * @file rbtree.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for template Red Black Tree class
 * @date 2022-06-08
 */

#ifndef FT_CONTAINERS_INCLUDES_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_RBTREE_HPP

#include <functional>
#include <memory>

#include "iterator_traits.hpp"
#include "utility.hpp"

#define FT_NOEXCEPT_ throw()

namespace ft {

enum RbTreeColor { kBlack = true, kRed = false };

template <typename Key, typename Alloc = std::allocator<Key> >
struct RbTreeNode {
  typedef Alloc AllocType;
  typedef RbTreeNode* pointer;

  AllocType alloc;
  RbTreeColor color;
  pointer parent;
  pointer left;
  pointer right;
  Key* key;

  // Constructor
  RbTreeNode(const AllocType& allocator = AllocType())
      : alloc(allocator),
        color(kBlack),
        parent(NULL),
        left(NULL),
        right(NULL),
        key(NULL) {}

  RbTreeNode(const Key& key_value, const AllocType& allocator = AllocType())
      : alloc(allocator), color(kBlack), parent(NULL), left(NULL), right(NULL) {
    key = alloc.allocate(1);
    alloc.construct(key, key_value);
  }

  // Destructor
  ~RbTreeNode(void) {
    alloc.destroy(key);
    alloc.deallocate(key, 1);
  }
};

template <typename Iterator>
class RbTreeIterator {
 private:
  Iterator current_;
  typedef typename ft::iterator_traits<Iterator> traits_type_;

 public:
  typedef Iterator iterator_type;
  typedef bidirectional_iterator_tag iterator_category;
  typedef typename traits_type_::value_type value_type;
  typedef typename traits_type_::difference_type difference_type;
  typedef typename traits_type_::reference reference;
  typedef typename traits_type_::pointer pointer;

  // Constructors
  RbTreeIterator(void) : current_(Iterator()) {}

  RbTreeIterator(Iterator itr) : current_(itr) {}

  RbTreeIterator(const RbTreeIterator& original)
      : current_(original.current_) {}

  // Destructor
  ~RbTreeIterator(void) {}

  // Copy Assignment operator overload
  RbTreeIterator& operator=(const RbTreeIterator& rhs) FT_NOEXCEPT_ {
    current_ = rhs.current_;
    return *this;
  }

  // dereference & reference
  reference operator*(void) const FT_NOEXCEPT_ { return current_->key; }

  pointer operator->(void) const FT_NOEXCEPT_ { return current_; }

  // increment & decrement
  // TODO...
};

// template <typename Iterator>

template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key> >
class RbTree {
 public:
  typedef Alloc AllocType;
  typedef Key KeyType;
  typedef Key* KeyPtr;
  typedef Key& KeyRef;
  typedef RbTreeNode<KeyType, AllocType> Node;
  typedef Node* NodePtr;

 private:
  static Compare comp_;
  NodePtr root_;
  NodePtr min_;
  NodePtr max_;
  Alloc alloc_;

 public:
  // Constructors
  RbTree(const AllocType& alloc = AllocType())
      : root_(new Node()), min_(root_), max_(root_), alloc_(alloc), {}

  RbTree(const KeyType& key, const AllocType& alloc = AllocType())
      : root_(new Node(key, alloc)), min_(root_), max_(root_), alloc_(alloc) {}

  // TODO
  RbTree(const RbTree& original) {}

  // Destructor
  ~RbTree(void) {}

  // search
  NodePtr search(const KeyType& key_value, const NodePtr node = root_) {
    if (node == NULL)
      return NULL;
    else if (key_value == *(node->key))
      return node;
    search(key_value,
           comp_(key_value, *(node->key)) ? node->left : node->right);
  }

  // insert
  // NOTE : will need multiple case specialization
  // TODO : rotation for RB pattern
  void insert(const KeyType& key_value, const NodePtr node = root_) {
    if (node == NULL || key_value == *(node->key)) return;
    if (comp_(key_value, *(node->key))) {
      if (node->left == NULL) {
        node->left = new Node(key_value, alloc_);
        node->left->parent = node;
        return;
      }
      insert(key_Value, node->left);
    } else {
      if (node->right == NULL) {
        node->right = new Node(key_value, alloc_);
        node->right->parent = node;
        return;
      }
      insert(value, node->right);
    }
  }

  // delete
  // NOTE : will need multiple case specialization
  bool delete (const KeyType& key_value) {
    NodePtr target = search(key_value);
    if (target == NULL) return false;
    // TODO : rotate to keep RB rule
  }

  // left rotate
  // right rotate
};
}  // namespace ft

#endif
