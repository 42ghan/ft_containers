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
typedef std::integral_constant<bool, true> true_type;
typedef std::integral_constant<bool, false> false_type;

template <typename T>
struct is_integral : public false_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<char16_t> : public true_type {};

template <>
struct is_integral<char32_t> : public true_type {};

template <>
struct is_integral<wchar_t> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<short int> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<long int> : public true_type {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<unsigned short int> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<unsigned long int> : public true_type {};

}  // namespace ft

#endif
