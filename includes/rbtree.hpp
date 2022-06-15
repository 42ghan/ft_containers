/**
 * @file rbtree.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for template Red Black Tree class
 * @date 2022-06-08
 */

#ifndef FT_CONTAINERS_INCLUDES_RBTREE_HPP
#define FT_CONTAINERS_INCLUDES_RBTREE_HPP

#include <functional>
#include <iostream>
#include <memory>

// #include "iterator_traits.hpp"
#include "utility.hpp"

#define FT_NOEXCEPT_ throw()

namespace ft {

enum RbTreeColor { kBlack = true, kRed = false };

enum RbTreeLeftOrRight { kLeft = 0, kRight };

template <typename Key>
struct RbTreeNode {
  typedef Key KeyType;
  typedef RbTreeNode* pointer;

  RbTreeColor color;
  pointer parent;
  pointer left;
  pointer right;
  KeyType key;

  // Constructor
  RbTreeNode(const KeyType& key_value = KeyType())
      : color(kRed), parent(NULL), left(NULL), right(NULL), key(key_value) {}
};

// template <typename Iterator>
// class RbTreeIterator {
//  private:
//   Iterator current_;
//   typedef typename ft::iterator_traits<Iterator> traits_type_;

//  public:
//   typedef Iterator iterator_type;
//   typedef bidirectional_iterator_tag iterator_category;
//   typedef typename traits_type_::value_type value_type;
//   typedef typename traits_type_::difference_type difference_type;
//   typedef typename traits_type_::reference reference;
//   typedef typename traits_type_::pointer pointer;

//   // Constructors
//   RbTreeIterator(void) : current_(Iterator()) {}

//   RbTreeIterator(Iterator itr) : current_(itr) {}

//   RbTreeIterator(const RbTreeIterator& original)
//       : current_(original.current_) {}

//   // Destructor
//   ~RbTreeIterator(void) {}

//   // Copy Assignment operator overload
//   RbTreeIterator& operator=(const RbTreeIterator& rhs) FT_NOEXCEPT_ {
//     current_ = rhs.current_;
//     return *this;
//   }

//   // dereference & reference
//   reference operator*(void) const FT_NOEXCEPT_ { return current_->key; }

//   pointer operator->(void) const FT_NOEXCEPT_ { return current_; }

//   // increment & decrement
//   // TODO...
// };

// template <typename Iterator>

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

 private:
  static Compare comp_;
  NodePtr root_;
  AllocNodeType alloc_;

  // Rotations
  void LeftRotate_(NodePtr node) {
    NodePtr right_child = node->right;
    node->right = right_child->left;
    if (right_child->left != NULL) right_child->left->parent = node;
    right_child->parent = node->parent;
    if (node->parent == NULL)
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
    if (left_child->right != NULL) left_child->right->parent = node;
    left_child->parent = node->parent;
    if (node->parent == NULL)
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
    NodePtr uncle = NULL;
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
  void Transplant_(NodePtr original, NodePtr replacement) {
    if (original->parent == NULL)
      root_ = replacement;
    else if (original == original->parent->left)
      original->parent->left = replacement;
    else
      original->parent->right = replacement;
    replacement->parent = original->parent;
  }

  void AdjustAfterDelete_(NodePtr node) {
    NodePtr sibling = NULL;
    while (node != root_ && node->color == kBlack) {
      if (node == node->parent->left) {
        sibling = node->parent->right;
        if (sibling->color == kRed) {
          sibling->color = kBlack;
          node->parent->color = kRed;
          LeftRotate_(node->parent);
          sibling = node->parent->right;
        }
        if (sibling->left->color == kBlack && sibling->rihgt->color == kBlack) {
          sibling->color == kRed;
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
              sibling->rihgt->color == kBlack) {
            sibling->color == kRed;
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

  // SECTION : clear pre-order
  void ClearPreOrder_(NodePtr node) {
    if (node == NULL) return;
    ClearPreOrder_(node->left);
    ClearPreOrder_(node->right);
    alloc_.destroy(node);
    alloc_.deallocate(node, 1);
  }

 public:
  // Constructors
  RbTree(const AllocType& alloc = AllocNodeType())
      : root_(NULL), alloc_(alloc) {}

  RbTree(const KeyType& key, const AllocType& alloc = AllocNodeType())
      : root_(NULL), alloc_(alloc) {
    root_ = alloc_.allocate(1);
    alloc_.construct(root_, Node(key));
    root_->color = kBlack;
  }

  // TODO
  RbTree(const RbTree& original) {}

  // Destructor
  ~RbTree(void) { ClearPreOrder_(root_); }

  // min & max
  NodePtr Min(NodePtr node) {
    if (node == NULL) return NULL;
    while (node->left) node = node->left;
    return node;
  }

  NodePtr Max(NodePtr node) {
    if (node == NULL) return NULL;
    while (node->right) node = node->right;
    return node;
  }

  // find predecessor / successor of a node
  NodePtr FindPredecessor(NodePtr node) {
    if (node->left != NULL) return Max(node->left);
    NodePtr parent = node->parent;
    while (parent != NULL && node == parent->left) {
      node = parent;
      parent = node->parent;
    }
    return parent;
  }

  NodePtr FindSuccessor(NodePtr node) {
    if (node->right != NULL) return Min(node->right);
    NodePtr parent = node->parent;
    while (parent != NULL && node == parent->right) {
      node = parent;
      parent = node->parent;
    }
    return parent;
  }

  // search
  NodePtr Search(const KeyType& key_value) {
    NodePtr node = root_;
    while (node != NULL && node->key != key_value)
      node = comp_(key_value, node->key) ? node->left : node->right;
    return node;
  }

  // insert
  // The inserted node is colored red initially, if the Red-Black tree's
  // properties are not kept by inserting the new node, rotations and/or
  // recoloring take place in AdjustAfterInsert_
  // NOTE : the new Node's color is initialized to red in the Node's
  // constructor
  // TODO : rotation for RB pattern
  void Insert(const KeyType& key_value) {
    NodePtr trailing = NULL;
    NodePtr cursor = root_;
    while (cursor != NULL) {
      trailing = cursor;
      if (!comp_(key_value, cursor->key) && !comp(cursor->key, key_value))
        return;
      cursor = comp_(key_value, cursor->key) ? cursor->left : cursor->right;
    }
    NodePtr node = alloc_.allocate(1);
    alloc_.construct(node, Node(key_value));
    node->parent = trailing;
    if (trailing == NULL) {
      node->color = kBlack;
      root_ = node;
    } else if (comp(node->key, trailing->key))
      trailing->left = node;
    else
      trailing->right = node;
    AdjustAfterInsert_(node);
  }

  // delete
  // NOTE : will need multiple case specialization
  void Delete(NodePtr node) {
    NodePtr replacement = NULL;
    NodePtr check_color = node;
    bool original_color = node->color;
    if (node->left == NULL) {
      replacement = node->right;
      Transplant_(node, node->right);
    } else if (node->right == NULL) {
      replacement = node->left;
      Transplant_(node, node->left);
    } else {
      check_color = Min(node->right);
      original_color = check_color->color;
      replacement = check_color->right;
      if (check_color->parent != node) {
        NodePtr temp = check_color;
        check_color = check_color->right;
        Transplant_(temp, check_color->right);
        check_color->right = node->right;
        check_color->right->parent = check_color;
        alloc_.destroy(temp);
        alloc_.deallocate(temp, 1);
      }
      Transplant_(node, check_color);
      check_color->left = node->left;
      check_color->left->parent = check_color;
      check_color->color = node->color;
    }
    alloc_.destroy(node);
    alloc_.deallocate(node, 1);
    if (original_color == kBlack) AdjustAfterDelete_(replacement);
  }

  // print
  void PrintInOrder(NodePtr node, int depth = 0) {
    if (node == NULL) return;
    PrintInOrder(node->left, depth + 1);
    std::cout << node->key << " ";
    PrintInOrder(node->right, depth + 1);
  }

  // getter
  NodePtr GetRoot(void) const { return root_; }
};
}  // namespace ft

#endif
