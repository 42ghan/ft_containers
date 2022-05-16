# ft_containers

DIY C++ containers implementation (in C++98 manner)

## Requirements

### Containers

- vector
- map
- stack (DIY vector class as default underlying container)
- set (Red-Black Tree)

### iterators & algorithms

- iterators_traits
- reverse_iterator
- enable_if
- is_integral
- equal, lexicographical_compare
- std::pair
- std::make_pair

## Background Information

### Allocator

- Containers manage storage space for their elements by utilizing `std::allocator` objects to dynamically allocates and deallocate memory.
- `std::allocator` is stateless. ("all instances of the given allocator are interchangeable, compare equal and can deallocate memory allocated by any other instance of the same allocator type.")

## Style Guide

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## References

- [cplusplus.com](http://cplusplus.com/)
- [cppreference.com](https://en.cppreference.com/w/)
- [gnu containers source](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits)
- [llvm containers source](https://github.com/llvm/llvm-project/tree/main/libcxx)
