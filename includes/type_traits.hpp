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
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

// is integral
template <typename T>
struct is_integral : public std::false_type {};

template <>
struct is_integral<bool> : public std::true_type {};

template <>
struct is_integral<char> : public std::true_type {};

template <>
struct is_integral<char16_t> : public std::true_type {};

template <>
struct is_integral<char32_t> : public std::true_type {};

template <>
struct is_integral<wchar_t> : public std::true_type {};

template <>
struct is_integral<signed char> : public std::true_type {};

template <>
struct is_integral<short int> : public std::true_type {};

template <>
struct is_integral<int> : public std::true_type {};

template <>
struct is_integral<long int> : public std::true_type {};

template <>
struct is_integral<long long int> : public std::true_type {};

template <>
struct is_integral<unsigned char> : public std::true_type {};

template <>
struct is_integral<unsigned short int> : public std::true_type {};

template <>
struct is_integral<unsigned int> : public std::true_type {};

template <>
struct is_integral<unsigned long int> : public std::true_type {};

template <>
struct is_integral<unsigned long long int> : public std::true_type {};
}  // namespace ft

#endif
