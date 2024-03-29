/**
 * @file rbtree.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for template Red Black Tree class
 * @date 2022-06-08
 */

#ifndef FT_CONTAINERS_INCLUDES_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_RBTREE_HPP

// #include <iostream>
#include <functional>
#include <memory>

#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#define R "\033[1;31m"
#define B "\033[1;34m"
#define RESET "\033[0m"

#define FT_NOEXCEPT_ throw()

namespace ft {

enum RbTreeColor { kBlack = true, kRed = false };

enum RbTreeLeftOrRight { kLeft = 0, kRight };

template <typename Key>
struct RbTreeNode {
  typedef Key KeyType;
  typedef Key& KeyRef;
  typedef RbTreeNode* pointer;

  RbTreeColor color;
  pointer parent;
  pointer left;
  pointer right;
  KeyType key;
  pointer end;
  bool is_nil;

  // Constructor
  RbTreeNode(const pointer nil_node = NULL, const bool is_nil_flag = false,
             const RbTreeColor black_or_red = kRed,
             const KeyType& key_value = KeyType(),
             const pointer end_node = NULL)
      : color(black_or_red),
        parent(nil_node),
        left(nil_node),
        right(nil_node),
        key(key_value),
        end(end_node),
        is_nil(is_nil_flag) {}

  // find predecessor / successor of a node
  pointer FindPredecessor(void) const {
    const RbTreeNode* node = this;
    if (!node->left->is_nil) return Max(node->left);
    pointer p = node->parent;
    while (!p->is_nil && node == p->left) {
      node = p;
      p = node->parent;
    }
    return p;
  }

  pointer FindSuccessor(void) const {
    const RbTreeNode* node = this;
    if (node->is_nil) return node->end;
    if (!node->right->is_nil) {
      pointer ret = Min(node->right);
      return (ret->is_nil) ? ret->end : ret;
    };
    pointer p = node->parent;
    while (!p->is_nil && node == p->right) {
      node = p;
      p = node->parent;
    }
    if (p->is_nil) return p->end;
    return p;
  }

  // min & max
  static pointer Min(pointer node) {
    while (!node->is_nil && !node->left->is_nil) node = node->left;
    return node;
  }

  static pointer Max(pointer node) {
    while (!node->is_nil && !node->right->is_nil) node = node->right;
    return node;
  }
};

template <typename Value>
class RbTreeIterator;

template <typename Value>
class RbTreeConstIterator {
 private:
  typedef RbTreeNode<Value>* NodePtr_;

  NodePtr_ current_;

 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef typename remove_cv<Value>::type value_type;
  typedef const value_type& reference;
  typedef const value_type* pointer;
  typedef ptrdiff_t difference_type;

  // Constructors
  RbTreeConstIterator(void) : current_() {}

  RbTreeConstIterator(NodePtr_ itr) : current_(itr) {}

  RbTreeConstIterator(const RbTreeConstIterator& original)
      : current_(original.current_) {}

  RbTreeConstIterator(const RbTreeIterator<Value>& itr)
      : current_(itr.base()) {}

  // Destructor
  ~RbTreeConstIterator(void) {}

  // Copy Assignment operator overload
  RbTreeConstIterator& operator=(const RbTreeConstIterator& rhs) {
    current_ = rhs.current_;
    return *this;
  }

  // dereference & reference
  reference operator*(void) const { return current_->key; }

  pointer operator->(void) const { return &(current_->key); }

  // increment & decrement
  RbTreeConstIterator& operator++(void) {
    current_ = current_->FindSuccessor();
    return *this;
  }

  RbTreeConstIterator operator++(int) {
    RbTreeConstIterator tmp = *this;
    this->operator++();
    return tmp;
  }

  RbTreeConstIterator& operator--(void) {
    current_ = current_->FindPredecessor();
    return *this;
  }

  RbTreeConstIterator operator--(int) {
    RbTreeConstIterator tmp = *this;
    this->operator--();
    return tmp;
  }

  NodePtr_ base(void) const { return current_; }
};

template <typename Value>
bool operator==(const RbTreeConstIterator<Value>& lhs,
                const RbTreeConstIterator<Value>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value>
bool operator==(const RbTreeConstIterator<Value>& lhs,
                const RbTreeIterator<Value>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value>
bool operator!=(const RbTreeConstIterator<Value>& lhs,
                const RbTreeConstIterator<Value>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Value>
bool operator!=(const RbTreeConstIterator<Value>& lhs,
                const RbTreeIterator<Value>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Value>
class RbTreeIterator {
 private:
  typedef RbTreeNode<Value>* NodePtr_;

  NodePtr_ current_;

 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef Value value_type;
  typedef Value& reference;
  typedef Value* pointer;
  typedef ptrdiff_t difference_type;

  // Constructors
  RbTreeIterator(void) : current_() {}

  RbTreeIterator(NodePtr_ itr) : current_(itr) {}

  RbTreeIterator(const RbTreeIterator& original)
      : current_(original.current_) {}

  // Destructor
  ~RbTreeIterator(void) {}

  // Assignment operator overload
  RbTreeIterator& operator=(const RbTreeIterator& rhs) {
    current_ = rhs.current_;
    return *this;
  }

  // dereference & reference
  reference operator*(void) const { return current_->key; }

  pointer operator->(void) const { return &(current_->key); }

  // increment & decrement
  RbTreeIterator& operator++(void) {
    current_ = current_->FindSuccessor();
    return *this;
  }

  RbTreeIterator operator++(int) {
    RbTreeIterator tmp = *this;
    this->operator++();
    return tmp;
  }

  RbTreeIterator& operator--(void) {
    current_ = current_->FindPredecessor();
    return *this;
  }

  RbTreeIterator operator--(int) {
    RbTreeIterator tmp = *this;
    this->operator--();
    return tmp;
  }

  NodePtr_ base(void) const { return current_; }
};

template <typename Value>
bool operator==(const RbTreeIterator<Value>& lhs,
                const RbTreeIterator<Value>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value>
bool operator==(const RbTreeIterator<Value>& lhs,
                const RbTreeConstIterator<Value>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value>
bool operator!=(const RbTreeIterator<Value>& lhs,
                const RbTreeIterator<Value>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Value>
bool operator!=(const RbTreeIterator<Value>& lhs,
                const RbTreeConstIterator<Value>& rhs) {
  return lhs.base() != rhs.base();
}

// SECTION : Red-Black Tree
template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key> >
class RbTree {
 public:
  typedef Alloc AllocType;
  typedef Key KeyType;
  typedef Key* KeyPtr;
  typedef Key& KeyRef;
  typedef RbTreeNode<KeyType> Node;
  typedef Node* NodePtr;
  typedef typename AllocType::template rebind<Node>::other AllocNodeType;
  typedef typename AllocNodeType::const_pointer ConstNodePtr;
  typedef RbTreeIterator<KeyType> iterator;
  typedef RbTreeConstIterator<KeyType> const_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
  typedef size_t size_type;

 private:
  struct RbTreeImpl_ {
    AllocNodeType alloc_;
    NodePtr nil;
    NodePtr end;
    NodePtr min;
    NodePtr max;

    // Default constructor
    explicit RbTreeImpl_(const AllocNodeType& alloc = AllocNodeType())
        : alloc_(alloc), min(NULL), max(NULL) {
      try {
        nil = alloc_.allocate(1);
        alloc_.construct(nil, Node(NULL, true, kBlack));
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        end = alloc_.allocate(1);
        alloc_.construct(end, Node(nil));
        nil->end = end;
      } catch (const std::exception& e) {
        alloc_.destroy(nil);
        alloc_.deallocate(nil, 1);
        throw e;
      }
    }

    RbTreeImpl_(const RbTreeImpl_& original)
        : alloc_(original.alloc_),
          nil(original.nil),
          end(original.end),
          min(original.min),
          max(original.max) {}

    RbTreeImpl_& operator=(const RbTreeImpl_& rhs) {
      nil = rhs.nil;
      end = rhs.end;
      min = rhs.min;
      max = rhs.max;
      return *this;
    }

    // Destructor
    ~RbTreeImpl_(void) {}
  };

  RbTreeImpl_ impl_;
  NodePtr root_;
  Compare comp_;
  AllocNodeType alloc_;
  size_type size_;

 public:
  // Constructors
  RbTree(const Compare& comp = Compare(),
         const AllocType& alloc = AllocNodeType())
      : impl_(RbTreeImpl_(alloc)),
        root_(impl_.nil),
        comp_(comp),
        alloc_(alloc),
        size_(0) {
    impl_.end->parent = root_;
    impl_.min = root_;
    impl_.max = root_;
  }

  // Copy constructor (Deep copy)
  RbTree(const RbTree& original)
      : impl_(RbTreeImpl_(original.alloc_)),
        root_(impl_.nil),
        comp_(original.comp_),
        alloc_(original.alloc_),
        size_(0) {
    const_iterator itr = original.begin();
    const_iterator itre = original.end();
    for (; itr != itre; ++itr) Insert(*itr);
  }

  RbTree& operator=(const RbTree& rhs) {
    ClearPostOrder(root_);
    impl_ = RbTreeImpl_(rhs.alloc_);
    root_ = impl_.nil;
    comp_ = rhs.comp_;
    alloc_ = rhs.alloc_;
    size_ = 0;
    const_iterator itr = rhs.begin();
    const_iterator itre = rhs.end();
    for (; itr != itre; ++itr) Insert(*itr);
    return *this;
  }

  // Destructor
  ~RbTree(void) {
    ClearPostOrder(root_);
    FreeResource_(impl_.nil);
    if (impl_.nil != impl_.end) FreeResource_(impl_.end);
  }

 private:
  // Rotations
  void LeftRotate_(NodePtr node) {
    NodePtr right_child = node->right;
    node->right = right_child->left;
    if (right_child->left != impl_.nil) right_child->left->parent = node;
    right_child->parent = node->parent;
    if (node->parent == impl_.nil)
      root_ = right_child;
    else if (node == node->parent->left)
      node->parent->left = right_child;
    else
      node->parent->right = right_child;
    right_child->left = node;
    node->parent = right_child;
  }

  void RightRotate_(NodePtr node) {
    NodePtr left_child = node->left;
    node->left = left_child->right;
    if (left_child->right != impl_.nil) left_child->right->parent = node;
    left_child->parent = node->parent;
    if (node->parent == impl_.nil)
      root_ = left_child;
    else if (node == node->parent->right)
      node->parent->right = left_child;
    else
      node->parent->left = left_child;
    left_child->right = node;
    node->parent = left_child;
  }

  // SECTION : insert utils
  // Roate or recolor nodes to keep RB-properties
  NodePtr RecolorRedUncleInsert_(NodePtr node, NodePtr uncle) {
    node->parent->color = kBlack;
    uncle->color = kBlack;
    node->parent->parent->color = kRed;
    return node->parent->parent;
  }

  void AdjustAfterInsert_(NodePtr node) {
    NodePtr uncle = impl_.nil;
    while (node->parent->color == kRed) {
      if (node->parent == node->parent->parent->left) {
        uncle = node->parent->parent->right;
        if (uncle->color == kRed)
          node = RecolorRedUncleInsert_(node, uncle);
        else {
          if (node == node->parent->right) {
            node = node->parent;
            LeftRotate_(node);
          }
          node->parent->color = kBlack;
          node->parent->parent->color = kRed;
          RightRotate_(node->parent->parent);
        }
      } else {
        uncle = node->parent->parent->left;
        if (uncle->color == kRed)
          node = RecolorRedUncleInsert_(node, uncle);
        else {
          if (node == node->parent->left) {
            node = node->parent;
            RightRotate_(node);
          }
          node->parent->color = kBlack;
          node->parent->parent->color = kRed;
          LeftRotate_(node->parent->parent);
        }
      }
    }
    root_->color = kBlack;
  }

  // SECTION : delete utils
  template <typename T>
  void FreeResource_(T* ptr) {
    alloc_.destroy(ptr);
    alloc_.deallocate(ptr, 1);
  }

  void DeleteLastNode_(void) {
    FreeResource_(root_);
    FreeResource_(impl_.end);
    root_ = impl_.nil;
    impl_.end = impl_.nil;
    impl_.min = impl_.nil;
    impl_.max = impl_.nil;
    impl_.nil->end = impl_.nil;
    --size_;
  }

  void Transplant_(NodePtr original, NodePtr replacement) {
    if (!comp_(impl_.min->key, original->key) &&
        !comp_(original->key, impl_.min->key))
      impl_.min = original->parent;
    else if (!comp_(impl_.max->key, original->key) &&
             !comp_(original->key, impl_.max->key)) {
      impl_.max = original->parent;
      impl_.end->parent = impl_.max;
    }
    if (original->parent == impl_.nil)
      root_ = replacement;
    else if (original == original->parent->left)
      original->parent->left = replacement;
    else
      original->parent->right = replacement;
    replacement->parent = original->parent;
  }

  void AdjustAfterDelete_(NodePtr node) {
    NodePtr sibling = impl_.nil;
    while (node != root_ && node->color == kBlack) {
      if (node == node->parent->left) {
        sibling = node->parent->right;
        if (sibling->color == kRed) {
          sibling->color = kBlack;
          node->parent->color = kRed;
          LeftRotate_(node->parent);
          sibling = node->parent->right;
        }
        if (sibling->left->color == kBlack && sibling->right->color == kBlack) {
          sibling->color = kRed;
          node = node->parent;
        } else {
          if (sibling->right->color == kBlack) {
            sibling->left->color = kBlack;
            sibling->color = kRed;
            RightRotate_(sibling);
            sibling = node->parent->right;
          }
          sibling->color = node->parent->color;
          node->parent->color = kBlack;
          sibling->right->color = kBlack;
          LeftRotate_(node->parent);
          node = root_;
        }
      } else {
        if (node == node->parent->right) {
          sibling = node->parent->left;
          if (sibling->color == kRed) {
            sibling->color = kBlack;
            node->parent->color = kRed;
            RightRotate_(node->parent);
            sibling = node->parent->left;
          }
          if (sibling->right->color == kBlack &&
              sibling->right->color == kBlack) {
            sibling->color = kRed;
            node = node->parent;
          } else {
            if (sibling->left->color == kBlack) {
              sibling->right->color = kBlack;
              sibling->color = kRed;
              LeftRotate_(sibling);
              sibling = node->parent->left;
            }
            sibling->color = node->parent->color;
            node->parent->color = kBlack;
            sibling->left->color = kBlack;
            RightRotate_(node->parent);
            node = root_;
          }
        }
      }
    }
    node->color = kBlack;
  }

 public:
  // SECTION : clear post-order
  void ClearPostOrder(NodePtr node) {
    if (node == impl_.nil) return;
    ClearPostOrder(node->left);
    ClearPostOrder(node->right);
    FreeResource_(node);
    --size_;
    if (size_ == 0) {
      root_ = impl_.nil;
      impl_.min = impl_.nil;
      impl_.max = impl_.nil;
      if (impl_.nil != impl_.end) FreeResource_(impl_.end);
      impl_.end = impl_.nil;
    }
  }

  // search
  iterator Search(const KeyType& key_value) const {
    NodePtr node = root_;
    while (node != impl_.nil &&
           (comp_(node->key, key_value) || comp_(key_value, node->key)))
      node = comp_(key_value, node->key) ? node->left : node->right;
    return (node == impl_.nil) ? iterator(impl_.end) : iterator(node);
  }

  // insert
  // The inserted node is colored red initially, if the Red-Black tree's
  // properties are not kept by inserting the new node, rotations and/or
  // recoloring take place in AdjustAfterInsert_
  // NOTE : the new Node's color is initialized to red in the Node's
  // constructor
  pair<iterator, bool> Insert(const KeyType& key_value, NodePtr cursor = NULL) {
    NodePtr trailing = impl_.nil;
    if (cursor == NULL) {
      cursor = root_;
      while (cursor != impl_.nil) {
        trailing = cursor;
        if (!comp_(key_value, cursor->key) && !comp_(cursor->key, key_value))
          return ft::make_pair(iterator(cursor), false);
        cursor = comp_(key_value, cursor->key) ? cursor->left : cursor->right;
      }
    } else {
      NodePtr successor = cursor->FindSuccessor();
      while (successor != impl_.end && !(comp_(cursor->key, key_value) &&
                                         comp_(key_value, successor->key))) {
        cursor = successor;
        successor = cursor->FindSuccessor();
      }
      trailing = cursor;
    }
    NodePtr node = alloc_.allocate(1);
    alloc_.construct(node, Node(impl_.nil, false, kRed, key_value));
    node->parent = trailing;
    if (trailing == impl_.nil) {
      node->color = kBlack;
      root_ = node;
    } else if (comp_(node->key, trailing->key))
      trailing->left = node;
    else
      trailing->right = node;
    AdjustAfterInsert_(node);
    ++size_;
    if (!(size_ == 1 && node == root_)) {
      if (comp_(node->key, impl_.min->key))
        impl_.min = node;
      else if (comp_(impl_.max->key, node->key)) {
        impl_.max = node;
        impl_.end->parent = node;
      }
    } else {
      impl_.min = root_;
      impl_.max = root_;
      impl_.end->parent = node;
    }
    return ft::make_pair(iterator(node), true);
  }

  // delete
  // NOTE : will need multiple case specialization
  // x : replacement, y : check_color, z : node
  void Delete(NodePtr node, const KeyType& key_value = KeyType()) {
    if (node == NULL) node = Search(key_value).base();
    if (size_ == 1 && node == root_) {
      DeleteLastNode_();
      return;
    }
    if (node == impl_.end) return;
    NodePtr x = impl_.nil;
    bool original_color = node->color;
    if (node->left == impl_.nil) {
      x = node->right;
      Transplant_(node, node->right);
    } else if (node->right == impl_.nil) {
      x = node->left;
      Transplant_(node, node->left);
    } else {
      NodePtr y = node;
      y = Node::Min(node->right);
      original_color = y->color;
      x = y->right;
      if (y->parent == node)
        x->parent = y;
      else {
        x = y->right;
        Transplant_(y, y->right);
        y->right = node->right;
        y->right->parent = y;
      }
      Transplant_(node, y);
      y->left = node->left;
      y->left->parent = y;
      y->color = node->color;
    }
    FreeResource_(node);
    --size_;
    if (original_color == kBlack) AdjustAfterDelete_(x);
  }

  // print
  // void PrintInOrder(NodePtr node, int depth = 0) {
  //   if (node == impl_.nil) return;
  //   PrintInOrder(node->left, depth + 1);
  //   std::cout << node->key << " ";
  //   PrintInOrder(node->right, depth + 1);
  // }

  // iterators
  iterator begin(void) FT_NOEXCEPT_ { return iterator(impl_.min); }

  const_iterator begin(void) const FT_NOEXCEPT_ {
    return const_iterator(impl_.min);
  }

  iterator end(void) FT_NOEXCEPT_ { return iterator(impl_.end); }

  const_iterator end(void) const FT_NOEXCEPT_ {
    return const_iterator(impl_.end);
  }

  reverse_iterator rbegin(void) FT_NOEXCEPT_ { return reverse_iterator(end()); }

  const_reverse_iterator rbegin(void) const FT_NOEXCEPT_ {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend(void) FT_NOEXCEPT_ { return reverse_iterator(begin()); }

  const_reverse_iterator rend(void) const FT_NOEXCEPT_ {
    return const_reverse_iterator(begin());
  }

  // Operations
  iterator LowerBound(const KeyType& key) {
    NodePtr node = root_;
    NodePtr ret = impl_.end;
    while (node != impl_.nil) {
      if (!comp_(node->key, key)) {
        ret = node;
        node = node->left;
      } else
        node = node->right;
    }
    return iterator(ret);
  }

  const_iterator LowerBound(const KeyType& key) const {
    NodePtr node = root_;
    NodePtr ret = impl_.end;
    while (node != impl_.nil) {
      if (!comp_(node->key, key)) {
        ret = node;
        node = node->left;
      } else
        node = node->right;
    }
    return const_iterator(ret);
  }

  iterator UpperBound(const KeyType& key) {
    NodePtr node = root_;
    NodePtr ret = impl_.end;
    while (node != impl_.nil) {
      if (comp_(key, node->key)) {
        ret = node;
        node = node->left;
      } else
        node = node->right;
    }
    return iterator(ret);
  }

  const_iterator UpperBound(const KeyType& key) const {
    NodePtr node = root_;
    NodePtr ret = impl_.end;
    while (node != impl_.nil) {
      if (comp_(key, node->key)) {
        ret = node;
        node = node->left;
      } else
        node = node->right;
    }
    return const_iterator(ret);
  }

  // getter
  NodePtr GetRoot(void) const { return root_; }

  size_type GetSize(void) const { return size_; }

  // swap
  void Swap(RbTree& x) {
    NodePtr root_temp = root_;
    RbTreeImpl_ impl_temp = impl_;
    size_type size_temp = size_;
    root_ = x.root_;
    impl_ = x.impl_;
    size_ = x.size_;
    x.root_ = root_temp;
    x.impl_ = impl_temp;
    x.size_ = size_temp;
  }

  // max allocation size
  size_type MaxSize(void) const { return alloc_.max_size(); }

  // void print_tree(const std::string& prefix, NodePtr x, bool isLeft) {
  //   if (x != impl_.nil) {
  //     std::cout << prefix;
  //     std::cout << (isLeft ? "L├──" : "R└──");
  //     if (x->color == kRed) {
  //       std::cout << R << x->key.first << RESET << "\n";
  //     } else {
  //       std::cout << B << x->key.first << RESET << "\n";
  //     }
  //     print_tree(prefix + (isLeft ? " │   " : "     "), x->left, true);
  //     print_tree(prefix + (isLeft ? " │   " : "     "), x->right, false);
  //   };
  // }
};
}  // namespace ft

#endif
