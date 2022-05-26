/**
 * @file type_traits.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief Implementations of enable_if, is_integral
 * @date 2022-05-26
 */

#ifndef FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP_
#define FT_CONTAINERS_INCLUDES_TYPE_TRAITS_HPP_

#include <type_traits>

namespace ft {
// enable if
template <bool, typename T = void>
struct enable_if {
}

template <typename T>
struct enable_if<true, T> {
  typedef T type;
}

// is integral
template <typename T>
struct is_integral : public false_type {
}

template <typename T>
struct is_integral<bool> : public true_type {
}

template <typename T>
struct is_integral<char> : public true_type {
}

template <typename T>
struct is_integral<char16_t> : public true_type {
}

template <typename T>
struct is_integral<char32_t> : public true_type {
}

template <typename T>
struct is_integral<wchar_t> : public true_type {
}

template <typename T>
struct is_integral<signed char> : public true_type {
}

template <typename T>
struct is_integral<short int> : public true_type {
}

template <typename T>
struct is_integral<int> : public true_type {
}

template <typename T>
struct is_integral<long int> : public false_type {
}

template <typename T>
struct is_integral<long long int> : public false_type {
}

template <typename T>
struct is_integral<unsigned signed char> : public true_type {
}

template <typename T>
struct is_integral<unsigned short int> : public true_type {
}

template <typename T>
struct is_integral<unsigned int> : public true_type {
}

template <typename T>
struct is_integral<unsigned long int> : public false_type {
}

template <typename T>
struct is_integral<unsigned long long int> : public false_type {
}
}  // namespace ft

#endif
