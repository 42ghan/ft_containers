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

// integral_constant
template <typename T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, value> type;
  operator value_type(void) const FT_NOEXCEPT_ { return value; }
};

// is integral
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

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

// is_same
template <typename, typename>
struct is_same : public false_type {};

template <typename T>
struct is_same<T, T> : public true_type {};

// is_void
template <typename>
struct is_void : public false_type {};

template <>
struct is_void<void> : public true_type {};

// remove_cv
template <typename T>
struct remove_cv {
  typedef T type;
};

template <typename T>
struct remove_cv<const T> {
  typedef T type;
};

template <typename T>
struct remove_cv<volatile T> {
  typedef T type;
};

template <typename T>
struct remove_cv<const volatile T> {
  typedef T type;
};

// is_base_of
// template <typename Base>
// true_type test_base_and_derived_conversion(Base *);

// template <typename>
// false_type test_base_and_derived_conversion(void *);

// template <typename Base, typename Derived>
// struct is_base_of
//     : public integral_constant<bool,
//                                decltype(test_base_and_derived_conversion<
//                                         typename remove_cv<Base>::type>(
//                                    static_cast<Derived *>(NULL)))::value> {};
}  // namespace ft

#endif
