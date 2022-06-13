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
        color(kRed),
        parent(NULL),
        left(NULL),
        right(NULL),
        key(NULL) {}

  RbTreeNode(const Key& key_value, const AllocType& allocator = AllocType())
      : alloc(allocator), color(kRed), parent(NULL), left(NULL), right(NULL) {
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

  // Recolor case after insert
  // NOTE : Inserted node is red by default
  // After insertion, if the parent && uncle node are red, change them to black
  // and grandfather to red
  void RecolorAfterInsert_(NodePtr node) {
    if (node->parent && node->parent->color == kRed &&
        node->parent->parent->left->color ==
            node->parent->parent->right->color) {
      node->parent->parent->left->color = kBlack;
      node->parent->parent->right->color = kBlack;
      node->parent->parent = kRed;
      RecolorAfterInsert_(node->parent->parent);
    }
  }

  // Left or Right Rotation
  void LeftRotate_(NodePtr node) {
    NodePtr temp = node->right;
    node->right = node->right->left;
    node->right->parent = node;
    if (node->parent->left = node)
      node->parent->left = temp;
    else
      node->parent->right = temp;
    temp->parent = node->parent;
    temp->left = node;
    node->parent = temp;
  }

  void RightRotate_(NodePtr node) {
    NodePtr temp = node->left;
    node->left = node->left->right;
    node->left->parent = node;
    if (node->parent->left == node)
      node->parent->left = temp;
    else
      node->parent->right = temp;
    temp->parent = node->parent;
    temp->right = node;
    node->parent = temp;
  }

  // Balance after insert
  void BalanceAfterInsert_(NodePtr node) {
    if (node->parent->parent->left->color == node->parent->parent->right->color)
      RecolorAfterInsert_(node);
    else {
      if (node->parent->parent->left = node->parent) {
        if (node->parent->left == node) {  // LL CASE
          RightRotate_(node->parent->parent);
          node->parent->color = kBlack;
          node->parent->right->color = kRed;
        } else {  // LR CASE
          LeftRotate_(node->parent);
          RightRotate_(node->parent);
          node->color = kBlack;
          node->right->color = kRed;
        }
      } else {
        if (node->parent->right == node) {  // RR CASE
          LeftRotate_(node->parent->parent);
          node->parent->color = kBlack;
          node->parent->left->color = kRed;
        } else {  // RL CASE
          RightRotate_(node->parent);
          LeftRotate_(node->parent);
          node->color = kBlack;
          node->left->color = kRed;
        }
      }
    }
  }

  // Find min value
  NodePtr FindMinNode_(NodePtr node) {
    if (node == NULL) return NULL;
    while (node->left) node = node->left;
    return node;
  }

 public:
  // Constructors
  RbTree(const AllocType& alloc = AllocType())
      : root_(NULL), min_(NULL), max_(NULL), alloc_(alloc), {}

  RbTree(const KeyType& key, const AllocType& alloc = AllocType())
      : root_(new Node(key, alloc)), min_(root_), max_(root_), alloc_(alloc) {
    root_->color = kBlack;
  }

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
  void insert(const KeyType& key_value, NodePtr node = root_) {
    if (node == NULL && node == root_) {
      root_ = new Node(key_value, alloc_);
      root_->color = kBlack;
    }
    if (node == NULL || key_value == *(node->key)) return;
    if (comp_(key_value, *(node->key))) {
      if (node->left == NULL) {
        node->left = new Node(key_value, alloc_);
        node->left->parent = node;
        if (node->color == kRed) BalanceAfterInsert_(node->left);
        return;
      }
      insert(key_Value, node->left);
    } else {
      if (node->right == NULL) {
        node->right = new Node(key_value, alloc_);
        node->right->parent = node;
        if (node->color == kRed) BalanceAfterInsert_(node->right);
        return;
      }
      insert(value, node->right);
    }
  }

  // delete
  // NOTE : will need multiple case specialization
  bool delete (const KeyType& key_value) {
    NodePtr target = search(key_value);
    int original_color;
    int replacement_color;

    if (target == NULL) return false;
    original_color = target->color;
    if (target->left == NULL && target->right == NULL) {
      NodePtr parent = target->parent;
      if (parent->left == target) {
        delete target;
        parent->left = NULL;
      } else {
        delete target;
        parent->right = NULL;
      }
      target = parent;
      original_color = target->color;
      replacement_color = kBlack;
    } else if (target->left == NULL) {
      target->key = target->right->key;
      replacement_color = target->right->color;
      delete target->right;
      target->right = NULL;
    } else if (target->right == NULL) {
      target->key = target->left->key;
      replacement_color = target->left->color;
      delete target->left;
      target->left = NULL;
    } else {
      NodePtr min_node = FindMinNode_(target->right);
      NodePtr min_parent = min_node->parent;
      target->key = min_node->key;
      delete min_node;
      min_parent->left = NULL;
      return true;
    }
    if (original_color == kRed || replacement_color == kRed) {
      target->color = kBlack;
    } else {
      if (target != root_) {
        if (target->parent->left != target) {
        }
      }
    }
    // TODO : rotate to keep RB rule
  }

  // left rotate
  // right rotate
};
}  // namespace ft

#endif
