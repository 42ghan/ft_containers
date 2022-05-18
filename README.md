# ft_containers

DIY C++ containers implementation (C++98)

## Index
- [Index](#index)
- [Style Guide](#style-guide)
- [STL Containers](#stl-containers)
- [Background Information](#background-information)
    - [Allocator](#allocator)
    - [Iterators](#iterators)
        - [`iterator_traits`](#iterator-traits)
        - [Categories](#categories)
    - [Exception Safety](#exception-safety)
- [Vector](#vector)

## Style Guide

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)


## STL Containers
STL Containers library provide a collection of class templates and algorithms so that programmers can easily implement comman data structures and manipulate them. The container manages its storage space by allocating and/or deallocating memory depending on how many elements are present in it. Its elements are accessed either directly or through iterators by using member functions.

There are two types of containers, sequence containers and assiciative containers. In sequence containers, data structures can be accessed sequentially. Associative containers provide sorted data structures that can be quickly searched (O(log n) complexity). There also are three container adaptors, stack (LIFO), queue (FIFO), and priority queue, that are not pure containers, but provide different interfaces of sequential containers by utilizing them in their implementations.
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

### Iterators
#### iterator_traits
#### Categories
- Random Access Iterator
- Bidirectional Iteraotr
- Forward Iterator
- Input Iterator
- Output Iterator

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

## Vector
### Features
- A vector container is an array that can change its size dynamically (using allocator object).
- It is a sequence container.
- Like arrays, data elements in a vector are stored in contiguous locations. Therefore, elements can be directly accessed, and the last element can be easily added or removed.
### Why is there `__vector_base` class?
- 

## TODO
### STL Containers

- [ ] vector
- [ ] map
- [ ] stack (DIY vector class as default underlying container)
- [ ] set (Red-Black Tree)

### iterators & algorithms

- [ ] iterators_traits
- [ ] reverse_iterator
- [ ] enable_if
- [ ] is_integral
- [ ] equal, lexicographical_compare
- [ ] std::pair
- [ ] std::make_pair

## References

- [cplusplus.com](http://cplusplus.com/)
- [cppreference.com](https://en.cppreference.com/w/)
- [gnu containers source](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits)
- [llvm containers source](https://github.com/llvm/llvm-project/tree/main/libcxx)
- [Bjarne Stroustrup (2000). The C++ programming language. Boston: Addison-Wesley.](https://www.stroustrup.com/3rd_safe.pdf)

‌
