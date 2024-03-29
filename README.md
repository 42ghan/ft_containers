# ft_containers

DIY C++ containers implementation (C++98)

## Index

- [Index](#index)
- [Style Guide](#style-guide)
- [STL Containers](#stl-containers)
- [Background Information](#background-information)
  - [Allocator](#allocator)
  - [`noexcept`/`throw()`](#-noexcept---throw---)
  - [`explicit` specifier](#-explicit--specifier)
  - [Iterators](#iterators)
    - [iterator_traits](#iterator-traits)
    - [Categories](#categories)
  - [Exception Safety](#exception-safety)
  - [RAII](#raii)
  - [SFINAE & `enable_if`](#sfinae----enable-if-)
  - [`is_base_of`](#-is-base-of-)
  - [Red-Black Tree](#red-black-tree)
    - [Why Red-Black Tree?](#why-red-black-tree-)
    - [Rotations](#rotations)
    - [Insertion Cases](#insertion-cases)
    - [Deletion Cases](#deletion-cases)
    - [`RbTreeImpl_` & `RbTreeIterator`](#-rbtreeimpl------rbtreeiterator-)
- [Vector](#vector)
  - [Class Template](#class-template)
  - [Features](#features)
  - [Why is there `__vector_base` class?](#why-is-there----vector-base--class-)
  - [Implementation of container specific iterator](#implementation-of-container-specific-iterator)
  - [Member Types](#member-types)
  - [Member Functions](#member-functions)
    - [Constructors & Destructors](#constructors---destructors)
    - [Iterators](#iterators-1)
    - [Capacity](#capacity)
    - [Element Access](#element-access)
    - [Modifiers](#modifiers)
    - [Getter](#getter)
- [Stack](#stack)
  - [Features](#features-1)
  - [Member Types](#member-types-1)
  - [Member Functions](#member-functions-1)
  - [Non-Member Functions (Relation Operators)](#non-member-functions--relation-operators-)
- [Map & Set](#map---set)
  - [Class Templates](#class-templates)
  - [Features](#features-2)
  - [Member Types](#member-types-2)
  - [Allocator Rebind](#allocator-rebind)
  - [Member Functions](#member-functions-2)
    - [Constructors & Destructors](#constructors---destructors-1)
    - [Iterators](#iterators-2)
    - [Capacity](#capacity-1)
    - [Element Access (MAP ONLY)](#element-access--map-only-)
    - [Modifiers](#modifiers-1)
    - [Observers](#observers)
    - [Operations](#operations)
    - [Getter](#getter-1)
  - [Non-Member Functions](#non-member-functions)
- [Algorithm & Utility](#algorithm---utility)
  - [`lexicographical_compare`](#-lexicographical-compare-)
  - [`equal`](#-equal-)
  - [`pair` & `make_pair`](#-pair-----make-pair-)
- [References](#references)

## Style Guide

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## STL Containers

STL Containers library provide a collection of class templates and algorithms so that programmers can easily implement comman data structures and manipulate them. The container manages its storage space by allocating and/or deallocating memory depending on how many elements are present in it. Its elements are accessed either directly or through iterators by using member functions.

There are two types of containers, sequence containers and assiciative containers. In sequence containers, data structures can be accessed sequentially. Associative containers provide sorted data structures that can be quickly searched (`O(log n`) complexity). There also are three container adaptors, stack (LIFO), queue (FIFO), and priority queue, that are not pure containers, but provide different interfaces of sequential containers by utilizing them in their implementations.

- Sequence containers
  - [vector](https://cplusplus.com/reference/vector/vector/)
  - [deque](https://cplusplus.com/reference/deque/deque/)
  - [list](https://cplusplus.com/reference/list/list/)
- Associative containers
  - [set](https://cplusplus.com/reference/set/set/)
  - [multiset](https://cplusplus.com/reference/set/multiset/)
  - [map](https://cplusplus.com/reference/map/map/)
  - [multimap](https://cplusplus.com/reference/map/multimap/)
- Container adaptors
  - [stack](https://cplusplus.com/reference/stack/stack/)
  - [queue](https://cplusplus.com/reference/queue/queue/)
  - [priority_queue](https://cplusplus.com/reference/queue/priority_queue/)

## Background Information

### Allocator

- Containers manage storage space for their elements by utilizing [`std::allocator`](https://cplusplus.com/reference/memory/allocator/) objects to dynamically allocates and deallocate memory.
- `std::allocator` is stateless. ("all instances of the given allocator are interchangeable, compare equal and can deallocate memory allocated by any other instance of the same allocator type.")
- Why use `std::allocator` instead of using `new` and `delete` directly?
  - By using `std::allocator` allocation and construction, and deallocation and destruction can be performed separately.
  - [StackOverflow discussion](https://stackoverflow.com/questions/31358804/whats-the-advantage-of-using-stdallocator-instead-of-new-in-c#:~:text=new%20and%20delete%20are%20the,then%20finally%20deallocate%20the%20memory.)
- When deallocating memory space by using `std::allocator::deallocate`, the pointer that is being deallocated must be the one allocated by `std::allocator::allocate`, and the size argument must be equal to the one used by the allocator.

### `noexcept`/`throw()`

- A lot of member functions of STL Containers' declarations are followed by `noexcept` specifier.
- It is used to let the compiler know that the function will not throw exception.
- When an exception is thrown from a **NON-THROWING** function, `std::unexpected` is called, which will terminate the program by calling `std::terminate`.
- It is used for two main reasons: [(from Modernes C++)](https://www.modernescpp.com/index.php/c-core-guidelines-the-noexcept-specifier-and-operator)
  - documents the behaviour of the function (which means the function can be safely used in a non-throwing function)
  - optimises compilation
- In C++98 standard, only the dynamic exception specification using `throw()` is available instead of `noexcept`. Since such method does not improve performance like the `noexcept` does, a question arises whether `throw()` should be utilized in this implementation [(ref. StackOverflow)](https://stackoverflow.com/questions/13841559/deprecated-throw-list-in-c11). However, `throw()` was used for exiting the program by calling `std::unexpected -> std::terminate` when exception is thrown from a **NON-THROWING** function was deemed more important than slight performance improvement.

### `explicit` specifier

- `explicit` specifiers in front of constructors specify that the constructors cannot be used for implicit conversions and copy-initialization. The specifier can be used to prevent unwanted and unexpected conversions.
- A constructor without `explicit` specifier is called a converting constructor.

```c++
#include <iostream>

template <typename T>
void PrintNum(T t) {
  std::cout << t.n << "\n";
}

class Implicit {
 public:
  int n;
  Implicit(int x) : n(x) {}
};

class Explicit {
 public:
  int n;
  explicit Explicit(int x) : n(x) {}
};

int main(void) {
  int a = 42;
  PrintNum<Implicit>(a); // OK - uses Implicit's constructor for implicit conversion
  PrintNum<Explicit>(a); // error - compile error occurs
}
```

### Iterators

- An iterator is an object that points to some element in a range of elements (e.g. a pointer). By using operators (at least ++ and \*), it can iterate through the elements of that range.
- Each container type has its specific iterator type.
- All iterators, regardless of their categories, are at least:
  - copy-constructible
  - copy-assignable
  - destructible
  - can be incremented using `operator++`
  - can be dereferenced using `operator\*`

#### iterator_traits

- `iterator_traits` is a class that defines properties of iterators.
- For every iterator type, at least the following member types are defined to correspond its properties.
  - `difference_type`
  - `value_type`
  - `pointer`
  - `reference`
  - `iterator_category`
- These member types are checked by STL algorithms to determine properties of the iterators passed to them and the range they represent.

#### Categories

- There exist five different categories of iterators and their hierarchy is like the diagram below.
<figure>
<p align="center">
  <img src="assets/iterator_categories.png" style="width: 60%; height: 60%; "></p>
  <figcaption align="center" style="font-weight: bold;">hierarchy between each iterator category (refer to the table in <a href="https://www.cplusplus.com/reference/iterator/">cplusplus.com</a> for further details)</figcaption>
  </figure>

- Random Access Iterator
  - access elements at an arbitrary offset position relative to the element they point to (same functionality as pointers)
  - access ranges non-sequentially
- Bidirectional Iterator
  - iterate through a range sequentially in both directions
- Forward Iterator
  - iterate through a range sequentially in one direction (beginning to end)
- Input Iterator
  - read only once, and the iterator is incremented
- Output Iterator
  - each element pointed by the iterator is written a value only once, and the iterator is incremented

### Exception Safety

- "An operation on an object is said to be exception safe if that operation leaves the object in a valid
  state when the operation is terminated by throwing an exception." (Bjarne Stroustrup, 2000)
- A set of C++ STL's exception-safety guarantees:
  - **Basic guarantee** (for all ops)
    - The basic invariants are maintained, no resources are leaked.
  - **Strong guarantee** (for key ops)
    - The object being manipulated remains in the same state as it was before the operation took place when an exception is thrown.
    - key ops e.g. : `push_back()`, `insert()`.
  - **Nothrow guarantee** (for some)
    - some ops such as destructors, `swap()`, `pop_back()` do not throw exceptions.
- "In OOP, an invariant is a set of assertions that must always hold true during the life of an object for the program to be valid." (from [StackExchange](https://softwareengineering.stackexchange.com/questions/32727/what-are-invariants-how-can-they-be-used-and-have-you-ever-used-it-in-your-pro), by Xavier Nodet) In the example below, `Safe` class requires successful allocation of `T`, an invariant, in order to be constructed. Therefore, `Safe` class is exception safe (basic guarantee).

```c++
template <typename T>
class Safe {
    T *p;
  public:
    Safe() : p(new T) {}
    ~Safe() { delete p; }
}
```

- It is recommended to aim for the strong exception-safety guarantee while providing the basic guarantee when writing a library. At the same time, it is better to keep templates exception-transparent (not handling all exceptions) so that the user can find the exact cause of a problem.
- Below are exception-safe implementation techniques:
  - try-block
  - [RAII](#raii)
  - do not let go of data before its replacement is stored.
  - leave objects in valid states when throwing/re-throwing an exception.

### RAII

- RAII stands for "resource acquisition is initialization." (Bjarne Stroustrup, 2000)
- RAII is a technique that "binds the life cycle of a resource that must be acquired before use (allocated heap memory, thread of execution, open socket, open file, locked mutex, disk space, database connection—anything that exists in limited supply) to the lifetime of an object." (from [cppreference.com](https://en.cppreference.com/w/cpp/language/raii))
- Such technique guarantees availability (while the holder object is alive) and relief (when the object is destroyed) of resources.
- In practice, RAII: (from [cppreference.com](https://en.cppreference.com/w/cpp/language/raii))
  - encapsulate each resource into a class, where
    - the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
    - the destructor releases the resource and never throws exceptions;
  - always use the resource via an instance of a RAII-class that either - has automatic storage duration or temporary lifetime itself, or - has lifetime that is bounded by the lifetime of an automatic or temporary object

### SFINAE & `enable_if`

- SFINAE is an acronym for "Substitiution Is Not An Error."
- This is a rule applied to avoid a compile error when substituting the explicitly specifed or deduced type for the template parametar fails. Type deduction fails only when invalid types and expressions have been used in the immediate context of the function type and its template parameter types.
- An example of SFINAE error is when a member of a type was used where the type does not contain the member.

```C++
template<typename T>
typename T::value_type negate(const T& t) {
  retrn -T(t;)
}
// a function call to negate(42) will substitue the return type to
// `int::value_type`, and since `int` type does not have the member, `value_type`,
// SFINAE error
```

- `enable_if`, accompanied by `type_traits`, is an useful tool that differentiate template functions for different kinds of types. It can be easily implemented by using metafunctions as following code.

```C++
template <bool, typename T = void>
struct enable_if {
}

template <typename T>
struct enable_if<true, T> {
  typedef T type;
}
```

- Using `enable_if` in the template parameter as the example below only enables the declared overload for type that are input iterators. Without `enable_if` the typename `_InputIterator` does not have any semantic meaning.

```C++
template <class _InputIterator>
vector(_InputIterator __first,
       typename enable_if<__is_input_iterator<_InputIterator>::value &&
                          !__is_forward_iterator<_InputIterator>::value &&
                          ... more conditions ...
                          _InputIterator>::type __last);
```

### `is_base_of`

- `is_base_of<Base, Derived>` is a template class that is used to determine whether the `Base` type is the base class of the `Derived` class. It inherits `integral_constant` and its value is set to either true/false depending on inheritance relationship between `Base` and `Dervied`.
- In order to distinguish whether the passed argument's type to `InputIterator` parameter of `vector`'s member functions is indeed a kind of `InputIterator`, implementation of DIY `is_base_of` was tried since it is not supported in C++98 standard.
- Using the concept of [overload resolution](https://en.cppreference.com/w/cpp/language/overload_resolution) (conversion to `Base *` comes before `void *`) was attempted (code below) as [is_base_of implementation on MODERNES C++](https://www.modernescpp.com/index.php/the-type-traits-library-std-is-base-of) suggests, however, without using `decltype()` keyword (C++11), the code became way too complicated.

```C++
template <typename Base>
true_type test_base_and_derived_conversion(Base *);

template <typename>
false_type test_base_and_derived_conversion(void *);

template <typename Base, typename Derived>
struct is_base_of
    : public integral_constant<bool,
                               decltype(test_base_and_derived_conversion<
                                        typename remove_cv<Base>::type>(
                                   static_cast<Derived *>(NULL)))::value> {};
```

- Therefore, using unique `is_{type of iterator}` classes was used as a filter for `InputIterator`.

### Red-Black Tree

- Red-Black Tree is a form of Binary Search Tree, which keeps the tree structure balanced by continually rotating and/or recoloring nodes to preserve following properties:
  - #1 Every node is either red/black.
  - #2 The root node is black.
  - #3 Every leaf (NIL) is black.
  - #4 If a parent node is red, both its children are black.
  - #5 All simple paths from any node to its descendant leaves contain the same number of black nodes (same black heights).
- For three basic operations of BST, Search, Insert, and Delete, time complexity of `O(log n)` is guaranteed for the worst cases.
- It was invented by Rudolf Bayer, a German computer scientist, in 1972.

#### Why Red-Black Tree?

- Most of the BST operations take `O(h)`, where h is the height of the tree. However, if the elements are inserted in sorted order, the tree becomes skewed, and in the worst case, the cost of operations become `O(n)`. Balanced tree structures such as Red-Black Tree or AVL Tree are preferred for they internally balance the tree to preserve the height of the tree to `log n`.
- Both Red-Black Tree and AVL Tree are balanced, then in what case is Red-Black Tree preferred? Since AVL Tree rebalances every time the left-right height difference is greater than 1, AVL Tree remains more balanced than Red-Black Tree. But AVL Tree may cause more rotations during insertion and deletion. So if frequent insertions and deletions are expected, Red-Black Tree is the better option.

#### Rotations

- Red-Black Tree's properties are kept by rotating and/or recoloring nodes. There are two types of rotations (Left Rotate/ Right Rotate).
<figure>
<p align="center">
  <img src="assets/rotation.png" style="width: 60%; height: 60%; "></p>
  <figcaption align="center" style="font-weight: bold;">Left Rotation & Right Rotation of binary tree</figcaption>
  </figure>

#### Insertion Cases

- The inserted node is initially colored red.
- If the tree is empty, at time of insertion, just recolor the root to black.
- If the inserted node's parent is black, no properties have been violated.
- Else, there are three cases (six actually, but three are symmmetrical to the other three) that require fixup after normal BST insertion.
- **CASE 1** : The inserted node `z`'s uncle is red (Only recoloring)
  - The property #4 is violated.
  - Color both `z.parent` and `y` black, and `z.parent.parent` red.
  - Now call `z.parent.parent` a new `z` and check its uncle's color, if it is red, repeat the process up the tree until all properties are met.
- **CASE 2** : `z`'s uncle y is black and `z` is a right child
- **CASE 3** : `z`'s uncle y is black and `z` is a left child
  - The property #4 is violated.
  - In case 2, left rotation on the inserted node is userd to transform the situation into case 3.
  - Color `z.parent` black and `z.parent.parent` red and then right rotate on the `z.parent.parent`.
- Refer to pseudo-code from [section 13.3 of Introduction to Algorithms](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf) for details

#### Deletion Cases

- The first step is the same as normal BST.
  - if no child, remove the node
  - if one child, elevate the child to take the deleted node's position
  - if two children, find the successor and let the successor replace the deleted node's position
- The deletion operation of normal BST may not preserve Red-Black Tree's properties. If the removed node is red, the properties are kept, but if the removed node is black, three problems may arise. (let's call the removed node `y`, the node that will move into `y`'s original position `x`)
  - if `y` had been the root, and a red child of `y` becomes the new root (violation of property #2)
  - `x` and `x.parent` are red (violation of property #4)
  - removing `y` causes any simple path that contained `y` lack a black node (violation of property #5)
    - by saying that `x` is 'extra black' or 'doubly black' (see it as `y`'s blackness has been pushed to `x`), this violation can be corrected. Yet, a node has to be either black or red and this problem is solved in fixup procedure.
- Following are cases that require fixup after normal BST deletion required.
- **CASE 1** `x`'s sibling `w` is red
  - `w` must have black children.
  - Switch colors of `w` and `x.parent`, then perform left rotation on `x.parent`.
  - Now, the new sibling of `x` is black, thus CASE 1 -> CASE 2
- **CASE 2** `x`'s sibling `w` is black, both `w`'s children are black

  - Take one black off both `x` and `w` (`x` becomes singly black, `w` becomes red).
  - Pass the blackness to `x.parent` and repeat the fixup procedure with `x.parent` as the new `x`.

- **CASE 3** `x`'s sibling `w` is black, `w`'s left is red, right is black
  - Switch colors of `w` and `w.left`, then perform right rotation on `w`.
  - CASE 3 -> CASE 4
- **CASE 4** `x`'s sibling `w` is black, `w`'s right is red
  - Switch colors of `w` and `x.parent`.
  - Make `w.right` black, then left rotate on `x.parent`.
- Refer to pseudo-code from [section 13.4 of Introduction to Algorithms](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf) for details

#### `RbTreeImpl_` & `RbTreeIterator`

- `map` and `set` have `bidirectional iterator`, therefore their base data structure `RbTree`'s iterator has been implemented to meet [`bidirectional iterator`'s requirements](https://cplusplus.com/reference/iterator/BidirectionalIterator/) (see the properties table).
- `begin()` of the both containers point to the left-most/min key, and `end()` point to the position next to the right-most/max key. These positions need to be accessed at constant time complexity.
- Therefore, a struct `RbTreeImpl_` was implemented in a private scope of `RbTree` in order to store meta data of the tree such as `min` node (for `begin()`), `max` node and `end` node (for `end()`), and the sentinel `nil` node.
- The sentinel `nil` node was implemented, instead of just using `NULL` pointer, in order to make the nil node act as a black leaf node.

## Vector

### Class Template

```c++
template < class T, class Alloc = allocator<T> > class vector : protected VectorBase<T, Alloc>;
```

### Features

- A vector container is an array that can change its size dynamically (using allocator object).
- It is a sequence container.
- Like arrays, data elements in a vector are stored in contiguous locations. Therefore, elements can be directly accessed, and the last element can be easily added or removed.

### Why is there `__vector_base` class?

- In STL Containers `std::vector` implementation, `vector_base` class functions as a [RAII](#raii) (exception-safety technique) wrapper.
- Aquisition of resources occur in the `vector_base` wrapper's instantiation and the resources are released when the wrapper is destroyed (after the instance of the inherited class is destroyed), so the `std::vector` instance can safely access the resources during its lifetime.

### Implementation of container specific iterator

- Each container needs its own specific iterator type that meets its special requirements. E.g. `vector`'s iterator must meet requirements of `random_access_iterator` category while `list`'s iterator must meet requirements of `bidirectional_iterator` category.
- In gcc implementation, `random_access_iterator` for the vector was implemented using `std::__normal_iterator` template class, which seems like a generic iterator template for any randomly accessible iterable objects such as `vector`, `array`, `std::string`.
- However, since only `vector` is the randomly accessible iterable object, the container's specific iterator, `VectorIterator`, has been implemented.
- `random_access_iterator` inherits characteristics of `bidirectional_iterator`. In order to support iteration in reverse way, a generic `reverse_iterator` class template was implemented.

### Member Types

```C++
// Base_ is VectorBase
typedef T value_type;
typedef typename Base_::allocator_type allocator_type;
typedef typename Base_::alloc_traits alloc_traits;
typedef typename Base_::size_type size_type;
typedef typename alloc_traits::difference_type difference_type;
typedef typename Base_::pointer pointer;
typedef typename alloc_traits::const_pointer const_pointer;
typedef typename alloc_traits::reference reference;
typedef typename alloc_traits::const_reference const_reference;
typedef VectorIterator<pointer> iterator;
typedef VectorIterator<const_pointer> const_iterator;
typedef reverse_iterator<iterator> reverse_iterator;
typedef reverse_iterator<const_iterator> const_reverse_iterator;
```

### Member Functions

#### Constructors & Destructors

```C++
// Constructors
// #1 default : empty container constructor (no elem)
explicit vector(const allocator_type& alloc = allocator_type());

// #2 fill : construct a container with n elements, fill them with val
explicit vector(size_type n, const value_type& val,
                const allocator_type& alloc = allocator_type());

// #3 range : construct a container that will contain the same values in the range [first, last)
template <typename InputIterator>
vector(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type());

// #4 copy constructor (keeps and uses a copy of x's alloc)
vector(const vector& x);

// Destructor
~vector(void) FT_NOEXCEPT_

```

- **Exception Safety** : strong guarantee for the constructors & non-throwing for the destructor

- **UB** if inappropriate arguments have been passed to `allocator::construct` for the element constructions, or the range specified by [first,last) is not valid.

- `explicit` specifier specifies that the constructors followed by the keyword cannot be used for implicit conversions and copy-initialization.

#### Iterators

```C++
// Iterators
iterator begin(void) FT_NOEXCEPT_;
const_iterator begin(void) const FT_NOEXCEPT_;
reverse_iterator rbegin(void) FT_NOEXCEPT_;
const_reverse_iterator rbegin(void) const FT_NOEXCEPT_;
iterator end(void) FT_NOEXCEPT_;
const_iterator end(void) const FT_NOEXCEPT_;
reverse_iterator rend(void) FT_NOEXCEPT_;
const_reverse_iterator rend(void) const FT_NOEXCEPT_;
```

- **Exception Safety** : non-throwing

#### Capacity

```C++
// size : returns a number of elements in the vector
size_type size(void) const FT_NOEXCEPT_;

// max_size : returns the max number of elements the vector can hold theoretically
// (depends on the system limit)
size_type max_size(void) const FT_NOEXCEPT_;

// resize : resizes the container so that it contains n elements
// If n < size(), elements beyond the first n elements are destroyed.
// If n > size(), elements(val) are inserted at the end until n == size().
// If n > capacity(), reallocation takes place.
void resize(size_type n, value_type val = value_type());

// capacity : returns the size of allocated storage capacity
size_type capacity(void) const FT_NOEXCEPT_;

// empty : returns whether the vector is empty
bool empty(void) const FT_NOEXCEPT_;

// reserve : only when n is greater than capacity(), reallocation to increase space capacity to n takes place.
void reserve(size_type n);
```

- **Exception Safety** :

  - `vector::resize`

    - `n` <= `size()`, no-throw guarantee
    - `n` > `size()` & reallocation, strong guarantee if the type of the elements is either copyable or no-throw moveable
    - else basic guarantee

  - `vector::reserve`
    - strong guarantee if no reallocations happens / the elements has either a non-throwing move constructor or a copy constructor
    - else basic guarantee.
    - `std::length_error` is thrown if n is greater than `max_size()`

#### Element Access

```C++
// Subscript & at
// returns reference of n-th element of the vector
reference operator[](size_type n) FT_NOEXCEPT_;
const_reference operator[](size_type n) const FT_NOEXCEPT_;
reference at(size_type n);
const_reference at(size_type n) const;

// front & back
// front returns the reference of the first element
// back returns the reference of the last element
reference front(void) FT_NOEXCEPT_;
const_reference front(void) const FT_NOEXCEPT_;
reference back(void) FT_NOEXCEPT_;
const_reference back(void) const FT_NOEXCEPT_;
```

- **Exception Safety** :
  - `operator[]`
    - non-throwing, if `n` >= `size()`, UB
  - `at`
    - strong guarantee
    - checks whether `n` is in range, if not throws `std::out_of_range`
  - `front` & `back`
    - non-throwing, if empty, UB

#### Modifiers

```C++
// assign : assigns new contents to the vector, destroying and replacing current contents
// modifies the vector's size iff the new vector's size() > the current vector's capacity()
// #1 range : new contents from [first, last)
template <typename InputIterator>
void assign(InputIterator first, InputIterator last);

// #2 fill : n elements, initialized to a copy of val
void assign(size_type n, const value_type& val);

// push_back : add element at the end
// reallocation takes place iff the new vector's size() > the current vector's capacity()
void push_back(const value_type& val);

// pop_back : removes the last element
void pop_back(void) FT_NOEXCEPT_;

// insert : inserts new elements before the element at the specified position
// reallocation takes place iff the new vector's size() > the current vector's capacity()
// #1 single element : insert single element, initialized to a copy of val, in front of the position
iterator insert(iterator position, const value_type& val);

// #2 fill : insert n copies of the val before position
void insert(iterator position, size_type n, const value_type& val);

// #3 range : inserts elements from [first, last) before position
template <typename InputIterator>
void insert(iterator position, InputIterator first, InputIterator last);

// erase
// #1 single element : removes a single element at the position from the vector
iterator erase(iterator position);

// #2 range : removes a range of elements([first, last)) from the vector
iterator erase(iterator first, iterator last);

// swap : swap contents with x
void swap(vector& x);

// clear : removes all elements from the vector
void clear(void) FT_NOEXCEPT_;
```

- **Exception Safety** :
  - `assign`
    - basic guarantee
    - UB if inappropriate arguments have been passed to `allocator::construct` for the element constructions, or the range specified by [first,last) is not valid.
  - `push_back`
    - if no reallocation, strong guarantee
    - else if the type of the elements is either copyable or no-throw moveable, strong guarantee
    - else, basic guarantee
    - UB if `allocator::construct` is not supported with `val` as argument
  - `pop_back`
    - non-throwing, if empty, UB
  - `insert`
    - if single element at the end & no reallocation, strong guarantee
    - if reallocation takes place and the type of the elements is either copyable or no-throw moveable, strong guarantee
    - else, basic guarantee
  - `erase`
    - if the last element is also removed, non-throwing
    - else, basic guarantee
    - UB if position/range is invalid
  - `swap`
    - if the same `allocator` / allocator traits indicate that the allocators can propagate, non-throwing
    - else, UB
  - `clear`
    - non-throwing

#### Getter

```c++
// get_allocator : returns a copy of the allocator object.
allocator_type get_allocator(void) const FT_NOEXCEPT_;
```

- **Exception Safety** :
  - non-throwing

## Stack

### Features

```C++
template <typename T, typename Container = vector<T> >
class stack;
```

- `stack` is a container adaptor that operates in a LIFO(Last In First Out) context. Elements are insereted and extracted via one end of the container.
- The underlying container must support:
  - `empty`
  - `size`
  - `back`
  - `push_back`
  - `pop_back`
- Among STD Containers, `vector`, `deque`, and `list` meet these requirements.
- In STD Library version, `deque` is used as the underlying container of `stack`. However, in this implementation, `ft::stack` is utilized.

### Member Types

```C++
typedef Container container_type;
typedef typename Container::value_type value_type;
typedef typename Container::size_type size_type;
typedef typename Container::reference reference;
typedef typename Container::const_reference const_reference;
```

### Member Functions

- All member functions of `stack`, except for the constructor, execute their operations by utilizing its underlying containers' member functions. Therefore, complexity and exception safety of the member funtions are the same as them of the underlying container's member functions.

```C++
// note that `c` is the underlying container object

// top : returns a reference to the top element (last-in)
reference top(void) { return c.back(); }
const_reference top(void) const { return c.back(); }

// empty : checks if the stack is empty
bool empty() const { return c.empty(); }

// size : returns the stack's size
size_type size() const { return c.size(); }

// push : adds value to the top
// pop : extracts current top element
void push(const value_type& value) { c.push_back(value); }
void pop(void) { c.pop_back(); }
```

- Constructor instantiates its underlying container. Implicit implementations of copy constructor, assignment operator overload, destructor are used.

```C++
  explicit stack(const container_type& cont = container_type()) : c(cont) {}
```

### Non-Member Functions (Relation Operators)

- Comparison of two different `stack` objects are performed by calling the same relation operator overload of the underlying container object.
- In this implementation, only `operator==` and `operator<` of the underlying container object are called. Since they are comparing the protected container object `c`, `friend` declaration of `operator==` and `operator<` are used inside the class.

```C++
template <typename T, typename Container>
bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs);

template <typename T, typename Container>
bool operator!=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs);

template <typename T, typename Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

template <typename T, typename Container>
bool operator<=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs);

template <typename T, typename Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

template <typename T, typename Container>
bool operator>=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs);
```

## Map & Set

### Class Templates

```C++
template <typename Key,
          typename Value,
          typename Compare = std::less<Key>,
          typename Alloc = std::allocator<pair<const Key, Value> >
          >
class map;

template <typename Key,
          typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key>
          >
class set;
```

### Features

- `map` and `set` are associative containers that contain a set of either `pair<Key, Value>` objects (map) or `Key` objects (set) in a specific order defined by the `Compare` object.
- The default comparison object is `std::less<Key>`.
- Keys are unique.
- The internal data structure is usually implemented by a form of balanced BST such as AVL Tree and Red-Black Tree.

### Member Types

```c++
// Base_ is RbTree
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
typedef typename allocator_type::const_reference x;
typedef typename allocator_type::pointer pointer;
typedef typename allocator_type::const_pointer const_pointer;
typedef typename Base_::iterator iterator;
typedef typename Base_::const_iterator const_iterator;
typedef typename Base_::const_reverse_iterator const_reverse_iterator;
typedef typename Base_::reverse_iterator reverse_iterator;
typedef typename iterator_traits<iterator>::difference_type difference_type;
typedef size_t size_type;
```

```c++
// Base_ is RbTree
typedef Key key_type;
typedef Key value_type;
typedef Compare key_compare;
typedef Compare value_compare;
typedef Alloc allocator_type;
typedef typename allocator_type::reference reference;
typedef typename allocator_type::const_reference const_reference;
typedef typename allocator_type::pointer pointer;
typedef typename allocator_type::const_pointer const_pointer;
typedef typename Base_::const_iterator iterator;
typedef typename Base_::const_iterator const_iterator;
typedef typename Base_::const_reverse_iterator const_reverse_iterator;
typedef typename Base_::const_reverse_iterator reverse_iterator;
typedef typename iterator_traits<iterator>::difference_type difference_type;
typedef size_t size_type;
```

- `Key` of each node in a `set` is constant. Note that both `set::iterator` and `set::const_iterator` are aliased to the same type, `RbTree::const_iterator`.

### Allocator Rebind

- Unlike `vector`, data in `set` or `map` are stored inside node wrappers. Data need to be allocated in the 'node' unit, not by `Key` unit.
- `allocator::rebind` is utilized to use the same `allocator` type passed as the third template parameter for different `value_type` (node).

### Member Functions

#### Constructors & Destructors

- When both `map` & `set` are constructed, internal copies of `alloc` and `comp` are kept.

```c++
// Constructors
// #1 default : empty container constructor (no elem)
explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
// #2 range : construct a container that will contain the same values in the range [first, last)
template <class InputIterator>
map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type());

// #3 copy
map(const map& x);

// Destructor
~map(void) FT_NOEXCEPT_;
```

```c++
// Constructors
// #1 default : empty container constructor (no elem)
explicit set(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
// #2 range : construct a container that will contain the same values in the range [first, last)
template <class InputIterator>
set(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type());

// #3 copy
set(const set& x);

// Destructor
~set(void) FT_NOEXCEPT_;
```

- **Exception Safety** :
  - strong guarantee for the constructors, non-throwing for the destructors
  - **UB** if inappropriate arguments have been passed to `allocator::construct` for the element constructions, or the range specified by [first,last) is not valid.

#### Iterators

```c++
// set's iterator member functions
// For set only iterator version,
// no separate const_iterator version
// for iterator and const_iterator are aliased to the same type.
iterator begin(void) const FT_NOEXCEPT_;
iterator end(void) const FT_NOEXCEPT_;
reverse_iterator rbegin(void) const FT_NOEXCEPT_;
reverse_iterator rend(void) const FT_NOEXCEPT_;
```

```c++
// map's iterator member functions
iterator begin(void) FT_NOEXCEPT_;
const_iterator begin(void) const FT_NOEXCEPT_;
iterator end(void) FT_NOEXCEPT_;
const_iterator end(void) const FT_NOEXCEPT_;
reverse_iterator rbegin(void) FT_NOEXCEPT_;
const_reverse_iterator rbegin(void) const FT_NOEXCEPT_;
reverse_iterator rend(void) FT_NOEXCEPT_;
const_reverse_iterator rend(void) const FT_NOEXCEPT_;
```

#### Capacity

```c++
// same prototypes and functionalities for both set and map
// empty : returns true if the container is empty (size == 0)
bool empty() const FT_NOEXCEPT_;

// size : returns number of elements
size_type size() const FT_NOEXCEPT_;

// max_size : returns the max number of elements the container can hold (system dependent)
size_type max_size() const FT_NOEXCEPT_;
```

#### Element Access (MAP ONLY)

```c++
// subscript operator overload :
// if k == the key of an element,
// returns a reference to its mapped value
// even if k does not match the key of any element in the container,
// a new element with that key is inserted with default mapped value
// equivalent to
//(*((this->insert(make_pair(k,mapped_type()))).first)).second
mapped_type& operator[](const key_type& key);
```

- **Exception Safety** :
  - strong guarantee
  - **UB** if inappropriate arguments have been passed to `allocator::construct` for the element constructions, or the range specified by [first,last) is not valid.

#### Modifiers

```c++
// same prototypes and functionalities for both set and map

// insert : insert elements, sorted after insertion
// #1 single element : returns a pair of iterator and insertion check
// the first element iterator points to either the inserted/already existing node
// the second element is false if the key already exists
pair<iterator, bool> insert(const value_type& val);

// #2 hint : single element at a hinted position
// optimal if the position given precedes the inserted key
iterator insert(iterator position, const value_type& val);

// #3 range : inserts [first, last)
template <typename InputIterator>
void insert(InputIterator first,
            typename enable_if<is_input_iterator<InputIterator>::value,
                                InputIterator>::type last);

// erase : delete elements
// #1 single element : removes the element at the given position
// cannot erase end() position
void erase(iterator position);

// # 2 single element with a given key : if erased returns 1, else 0
size_type erase(const key_type& key);

// range : erases [first, last)
void erase(iterator first, iterator last);

// swap : contents are exchanged, iterators, pointers, and references remain valid
void swap(map& x);

// clear : removes all elements
void clear(void);
```

- **Exception Safety** :
  - `insert`
    - strong guarantee, for #1
    - else basic guarantee
    - **UB** if inappropriate arguments have been passed to `allocator::construct` for the element constructions, or the range specified by [first,last) is not valid.
  - `erase`
    - Unless the container's comparison object throws, non-throwing
    - else if a single element, strong guarantee
    - else basic guarantee
    - **UB** if inappropriate arguments have been passed to `allocator::construct` for the element constructions, or the range specified by [first,last) is not valid.
  - `swap`
    - non-throwing
  - `clear`
    - non-throwing

#### Observers

```c++
// same prototypes and functionalities for both set and map
// each function returns a copy of `key_compare` object and `value_compare` object
// for set, both `key_compare` and `value_compare` are defined the same
// note that `value_compare` type for map is a comparison object for
// the key of pair<Key, Value>, not for comparison of Value

key_compare key_comp(void) const;
value_compare value_comp(void) const;
```

- **Exception Safety** :
  - strong guarantee

#### Operations

```c++
// same prototypes and functionalities for both set and map
// set's iterator == const_ierator, therefore no separate const version is implemented

// find : searches the element with the key the same as k, returns iterator pointing to it
// end is returned if there is no matching
iterator find(const key_type& k);
const_iterator find(const key_type& k) const;

// count : returns how many of the elements with the key, k, exist
size_type count(const key_type& k) const;

// lower_bound : returns the first element that is equal or goes after the element with the key
iterator lower_bound(const key_type& key);
const_iterator lower_bound(const key_type& key) const;

// upper_bound : returns the first element that goes after the element with the key
iterator upper_bound(const key_type& key);
const_iterator upper_bound(const key_type& key);

// equal_range : returns bounds of elements that have the same key as the key
// if no match is found, length of the bound is 0
pair<const_iterator, const_iterator> equal_range(const key_type& key) const;
pair<iterator, iterator> equal_range(const key_type& key);
```

- **Exception Safety** :
  - strong guarantee

#### Getter

```C++
// get_allocator : returns a copy of the allocator object.
allocator_type get_allocator(void) const FT_NOEXCEPT_;
```

- **Exception Safety** :
  - non-throwing

### Non-Member Functions

```c++
template <typename Key, typename Compare, typename Alloc>
bool operator==(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) ;
}

template <typename Key, typename Compare, typename Alloc>
bool operator!=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) ;

template <typename Key, typename Compare, typename Alloc>
bool operator<(const set<Key, Compare, Alloc>& lhs,
               const set<Key, Compare, Alloc>& rhs) ;
}

template <typename Key, typename Compare, typename Alloc>
bool operator<=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) ;

template <typename Key, typename Compare, typename Alloc>
bool operator>(const set<Key, Compare, Alloc>& lhs,
               const set<Key, Compare, Alloc>& rhs) ;

template <typename Key, typename Compare, typename Alloc>
bool operator>=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) ;

template <typename Key, typename Compare, typename Alloc>
void swap(set<Key, Compare, Alloc>& x, set<Key, Compare, Alloc>& y) ;
```

```c++
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) ;
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs);

template <typename Key, typename T, typename Compare, typename Alloc>
void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y);
```

## Algorithm & Utility

### `lexicographical_compare`

- Returns ture if [first1, last1) compares lexicographically less than [first2, last2)

```c++
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2);

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2,
                             Compare comp);
```

### `equal`

- Test whether the elements in two ranges are equal.

```c++
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2);

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred);
```

### `pair` & `make_pair`

- `pair` couples a pair of values(`pair::first`, `pair::second`), of two same or different types, in a class.

## References

- [cplusplus.com](http://cplusplus.com/)
- [cppreference.com](https://en.cppreference.com/w/)
- [gnu containers source](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits)
- [llvm containers source](https://github.com/llvm/llvm-project/tree/main/libcxx)
- [SFINAE and enable_if by Eli Bendersky](https://eli.thegreenplace.net/2014/sfinae-and-enable_if/)
- [What is C++ metafunction and how to use it?
  by Sorush Khajepor](https://iamsorush.com/posts/cpp-meta-function/)
- [Bjarne Stroustrup (2000). The C++ programming language. Boston: Addison-Wesley.](https://www.stroustrup.com/3rd_safe.pdf)
- [H, T. (2009). Introduction to algorithms. Cambridge, Mass.: Mit Press.](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)
