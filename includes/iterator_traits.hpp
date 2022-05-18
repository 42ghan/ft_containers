/**
 * @file iterator_traits.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for iterator traits
 * @date 2022-05-17
 */

#ifndef FT_CONTAINERS_INCLUDES_ITERATOR_TRAITS_HPP_
#define FT_CONTAINERS_INCLUDES_ITERATOR_TRAITS_HPP_

#include <iterator>

template <typename Iter>
struct iterator_traits {
    typedef Iter::difference_type difference_type;
    typedef Iter::value_type value_type;
    typedef Iter::pointer pointer;
    typedef Iter::reference reference;
    typedef Iter::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*> {

};

template <typename T>
struct iterator_traits<const T*> {

};

#endif
