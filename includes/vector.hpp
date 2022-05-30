/**
 * @file vector.hpp
 * @author ghan (ghan@student.42seoul.kr)
 * @brief A header file for vector container
 * @date 2022-05-14
 */

#ifndef FT_CONTAINERS_INCLUDES_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_VECTOR_HPP_

#define FT_NOEXCEPT_ throw()

#include <algorithm>
#include <exception>
#include <iterator>
#include <iterator_traits.hpp>
#include <limits>
#include <memory>
#include <vector>

namespace ft {

// SECTION : vector iterator class
// implementation of random access iterator for ft::vector

template <typename Iterator>
class VectorIterator {
 protected:
  Iterator current_;
  typedef typename ft::iterator_traits<Iterator> traits_type_;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::iterator_category value_type;
  typedef typename traits_type::iterator_category difference_type;
  typedef typename traits_type::iterator_category reference;
  typedef typename traits_type::iterator_category pointer;

  // Constructors
  VectorIterator(void) : current_(Iterator()) {}

  VectorIterator(const Iterator& itr) : current_(itr) {}

  VectorIterator(const VectorIterator<>& original) { *this = original; }

  // Destructor
  ~VectorIterator(void) {}

  // Copy Assignment operator overload
  VectorIterator& operator=(const VectorIterator& rhs) {
    current_ = rhs.current_;
    return *this;
  }

  // increment & decrement
  VectorIterator& operator++(void) FT_NOEXCEPT_ {
    ++current_;
    return *this;
  }

  VectorIterator operator++(int) FT_NOEXCEPT_ {
    return VectorIterator(current_++);
  }

  VectorIterator& operator--(void) FT_NOEXCEPT_ {
    --current_;
    return *this;
  }

  VectorIterator operator--(int) FT_NOEXCEPT_ {
    return VectorIterator(current_--);
  }

  // subscript
  reference operator[](difference_type n) const FT_NOEXCEPT_ {
    return current_[n];
  }

  VectorIterator& operator+=(difference_type n) const FT_NOEXCEPT_ {
    current_ += n;
    return *this;
  }

  VectorIterator operator+(difference_type n) const FT_NOEXCEPT_ {
    return VectorIterator(current_ + n);
  }

  VectorIterator& operator-=(difference_type n) const FT_NOEXCEPT_ {
    current_ -= n;
    return *this;
  }

  VectorIterator operator-(difference_type n) const FT_NOEXCEPT_ {
    return VectorIterator(current_ - n);
  }

  const Iterator& base(void) const FT_NOEXCEPT_ { return current_; }
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lsh.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lsh.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator>(const VectorIterator<IteratorL>& lhs,
                      const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lsh.base() > rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator<(const VectorIterator<IteratorL>& lhs,
                      const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lsh.base() < rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator>=(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lsh.base() >= rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator<=(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lsh.base() <= rhs.base();
}

template <typename Iterator>
inline VectorIterator<Iterator> operator+(
    typename VectorIterator<Iterator>::difference_type n,
    const VectorIterator<Iterator>& itr) FT_NOEXCEPT_ {
  return VectorIterator<Iterator>(itr.base() + n);
}

template <typename Iterator>
inline typename VectorIterator<Iterator>::difference_type operator-(
    const VectorIterator<Iterator>& lhs,
    const VectorIterator<Iterator>& rhs) FT_NOEXCEPT_ {
  return lsh.base() - rhs.base();
}

// SECTION : vector base class (RAII wrapper)
template <typename T, typename Alloc = std::allocator<T> >
class VectorBase {
 protected:
  // member types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_traits<allocator_type> alloc_traits;
  typedef typename alloc_traits::pointer pointer;
  typedef typename alloc_traits::size_type size_type;

  pointer begin_;           // start of alloc
  pointer end_;             // end of sequence
  pointer end_of_storage_;  // end of alloc
  allocator_type alloc_;    // allocator

  void InitPointers_(const size_type n) {
    begin_ = alloc_.allocate(n);
    end_ = begin_;
    end_of_storage_ = begin_ + n;
  }

 private:
 public:
  explicit VectorBase(const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    InitPointers_(0);
  }

  explicit VectorBase(const size_type n,
                      const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    InitPointers_(n);
  }

  virtual ~VectorBase(void) {
    alloc_.deallocate(begin_, end_of_storage_ - begin_);
  }
};

template <typename T>
void swap(VectorBase<T>& a, VectorBase<T>& b) {
  swap(a.alloc_, b.alloc_);
  swap(a.begin_, b.begin_);
  swap(a.end_, b.end_);
  swap(a.end_of_storage_, b.end_of_storage_);
}

template <typename T, typename Alloc = std::allocator<T> >
class vector : private VectorBase<T, Alloc> {
 private:
  typedef VectorBase<T, Alloc> Base_;

  template <typename InputIterator>
  void RangeInitialize_(InputIterator first, InputIterator last, false_type) {
    typename iterator_traits<value_type>::difference_type n =
        std::distance<InputIterator>(first, last);
    InitPointers_(static_cast<size_type>(n));
    for (; first != last; first++) push_back(*first);
  }

  template <typename InputIterator>
  void RangeAssign_(InputIterator first, InputIterator last, false_type) {
    typename iterator_traits<value_type>::difference_type n =
        std::distance<InputIterator>(first, last);
    if (distance > capacity()) {
      vector<value_type, allocator_type> temp(n, alloc_);
      temp.end_ = std::uninitialized_copy<iterator, iterator>(first, last,
                                                              temp.begin());
      swap<value_type>(*this, temp);
    } else {
      clear();
      end_ = std::uninitialized_copy<iterator, iterator>(first, last, begin());
    }
  }

  template <typename InputIterator>
  void RangeInsert_(iterator position, InputIterator first, InputIterator last,
                    false_type) {
    typename iterator_traits<value_type>::difference_type n =
        std::distance<InputIterator>(first, last);
    if (position == end()) {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        temp.end_ = std::uninitialized_copy(begin(), end(), temp.begin());
        swap<value_type>(*this, temp);
      }
      for (iterator itr = first; itr != last; itr++) push_back(*itr);
    } else {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        iterator insert_pos =
            std::uninitialized_copy(begin(), position, temp.begin());
        std::uninitialized_copy(first, last, insert_pos);
        temp.end_ = std::uninitialized_copy(position, end(), insert_pos + n);
        swap<value_type>(*this, temp);
      } else {
        end_ += n;
        for (reverse_iterator ritr = rbegin() - 1; ritr != position + n;
             ritr++) {
          alloc_.destroy(ritr);
          alloc_.construct(ritr, *(ritr + 1));
        }
        for (iterator itr = position; first != last; first++) {
          alloc_.destroy(itr);
          alloc_.construct(itr, *first);
          itr++;
        }
      }
    }
  }

  void insert(iterator position, size_type n, const value_type& val) {
    if (position == end()) {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        temp.end_ = std::uninitialized_copy(begin(), end(), temp.begin());
        swap<value_type>(*this, temp);
      }
      for (size_type cnt = 0; cnt < n; cnt++) push_back(val);
    } else {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        iterator insert_pos =
            std::uninitialized_copy(begin(), position, temp.begin());
        std::uninitialized_fill_n(insert_pos, n, val);
        temp.end_ = std::uninitialized_copy(position, end(), insert_pos + n);
        swap<value_type>(*this, temp);
      } else {
        end_ += n;
        for (reverse_iterator ritr = rbegin() - 1; ritr != position + n;
             ritr++) {
          alloc_.destroy(ritr);
          alloc_.construct(ritr, *(ritr + 1));
        }
        for (iterator itr = position; itr != position + n; itr++;) {
          alloc_.destroy(itr);
          alloc_.construct(itr, val);
        }
      }
    }
  }

 public:
  // SECTION : member types
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

  // SECTION : constructors & destructor
  // #1 default : empty container constructor (no elem)
  explicit vector(const allocator_type& alloc = allocator_type())
      : Base_(alloc) {}

  // #2 fill : construct a container with n elements, fill them with val
  explicit vector(size_type n, const value_type& val,
                  const allocator_type& alloc = allocator_type())
      : Base_(n, alloc) {
    std::uninitialized_fill_n(begin_, n, val);
    end_ = begin_ + n;
  }

  // #3 range : construct a container that will contain the same values in the
  // range [first, last)  template <typename InputIterator>
  template <InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type())
      : Base_(alloc) {
    // NOTE : gcc uses __is_integer to check whether the InputIterator is indeed
    // an iterator
    typedef typename is_integral<InputIterator>::type Integral;
    RangeInitialize_(first, last, Integral());
  }

  // #4 copy constructor (keeps and uses a copy of x's alloc)
  vector(const vector& x) : Base_(x.size(), x.alloc_) {
    end_ = std::uninitialized_copy<iterator, iterator, iterator>(
        x.begin(), x.end(), begin_);
  }

  // destructor
  ~vector(void) FT_NOEXCEPT_ { clear(); }

  // SECTION : operator=
  // preserves the current allocator
  vector& operator=(const vector& x) {
    vector temp(alloc_);
    swap<T>(*this, temp);
    return *this;
  }

  // SECTION : iterators
  iterator begin(void) FT_NOEXCEPT_ { return iterator(begin_); }

  const_iterator begin(void) const FT_NOEXCEPT_ {
    return const_iterator(begin_);
  }

  reverse_iterator rbegin(void) FT_NOEXCEPT_ { return reverse_iterator(end()); }

  const_reverse_iterator rbegin(void) const FT_NOEXCEPT_ {
    return const_reverse_iterator(end());
  }

  iterator end(void) FT_NOEXCEPT_ { return iterator(end_); }

  const_iterator end(void) const FT_NOEXCEPT_ { return const_iterator(end_); }

  reverse_iterator rend(void) FT_NOEXCEPT_ { return reverse_iterator(begin()); }

  const_reverse_iterator rend(void) const FT_NOEXCEPT_ {
    return const_reverse_iterator(begin());
  }

  // SECTION : capacity
  size_type size(void) const FT_NOEXCEPT_ { return size_type(end_ - begin_); }

  size_type max_size(void) const FT_NOEXCEPT_ {
    const size_type diff_max =
        std::numeric_limits<ptrdiff_t>::max() / sizeof(value_type);
    const size_type alloc_max = alloc_traits::max_size(alloc_);
    return std::min(diff_max, alloc_max);
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n <= size())
      for (iterator itr = begin() + n; itr != end(); itr++) alloc_.destory(itr);
    else {
      if (n > capacity()) reserve(n);
      std::uninitialized_fill_n(end(), n - size(), val);
    }
    end_ = begin() + n;
  }

  size_type capacity(void) const FT_NOEXCEPT_ {
    return size_type(end_of_storage_ - begin_);
  }

  bool empty(void) const FT_NOEXCEPT_ { return begin() == end(); }

  void reserve(size_type n) {
    if (n > max_size()) throw std::length_error();
    if (n > capacity()) {
      vector<value_type, allocator_type> temp(n, alloc_);
      temp.end_ = std::uninitialized_copy<iterator, iterator, iterator>(
          begin(), end(), temp.begin());
      swap<value_type>(*this, temp);
    }
  }

  // SECTION : element access
  reference operator[](size_type n) FT_NOEXCEPT_ { return *(begin_ + n); }

  const_reference operator[](size_type n) const FT_NOEXCEPT_ {
    return *(begin_ + n);
  }

  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range();
    return (*this)[n];
  }

  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range();
    return (*this)[n];
  }

  reference front(void) FT_NOEXCEPT_ { return *begin(); }

  const_reference front(void) const FT_NOEXCEPT_ { return *begin(); }

  reference back(void) FT_NOEXCEPT_ { return *(end() - 1); }

  const_reference back(void) const FT_NOEXCEPT_ { return *(end() - 1); }

  // SECTION : modifiers
  // range
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last) {
    // NOTE : gcc uses __is_integer to check whether the InputIterator is indeed
    // an iterator
    typedef typename is_integral<InputIterator>::type Integral;
    RangeAssign_(first, last, Integral());
  }

  // fill
  void assign(size_type n, const value_type& val) {
    if (n > capacity()) {
      vector<value_type, allocator_type> temp(n, val, alloc_);
      swap<value_type>(*this, temp);
    } else {
      clear();
      std::uninitialized_fill_n<iterator, size_type, value_type>(begin(), n,
                                                                 val);
      end_ = begin() + n;
    }
  }

  void push_back(const value_type& val) {
    if (end_ != end_of_storage_) {
      alloc_.construct(end_, val);
      ++end_;
    } else {
      vector temp(size() + 1);
      temp.end_ = std::uninitialized_copy(begin(), end(), temp.begin());
      alloc_.construct(temp.end_, val);
      temp.end_++;
      swap<value_type>(*this, temp);
    }
  }

  void pop_back(void) FT_NOEXCEPT_ {
    end_--;
    alloc_.destroy(end_);
  }

  // single element
  iterator insert(iterator position, const value_type& val) {
    if (position == end())
      push_back(val);
    else {
      if (size() + 1 > capacity()) {
        vector temp(size() + 1);
        iterator insert_pos =
            std::uninitialized_copy(begin(), position, temp.begin());
        alloc_.construct(insert_pos, val);
        temp.end_ =
            std::uninitialized_copy(position + 1, end(), insert_pos + 1);
        swap<value_type>(*this, temp);
      } else {
        for (reverse_iterator ritr = rbegin(); ritr != position; ritr++) {
          if (ritr != rbegin()) alloc_.destroy(ritr);
          alloc_.construct(ritr, *(ritr + 1));
        }
        end_++;
        alloc_.construct(position, val);
      }
    }
  }

  // fill
  void insert(iterator position, size_type n, const value_type& val) {
    if (position == end()) {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        temp.end_ = std::uninitialized_copy(begin(), end(), temp.begin());
        swap<value_type>(*this, temp);
      }
      for (size_type cnt = 0; cnt < n; cnt++) push_back(val);
    } else {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        iterator insert_pos =
            std::uninitialized_copy(begin(), position, temp.begin());
        std::uninitialized_fill_n(insert_pos, n, val);
        temp.end_ = std::uninitialized_copy(position, end(), insert_pos + n);
        swap<value_type>(*this, temp);
      } else {
        end_ += n;
        for (reverse_iterator ritr = rbegin() - 1; ritr != position + n;
             ritr++) {
          alloc_.destroy(ritr);
          alloc_.construct(ritr, *(ritr + 1));
        }
        for (iterator itr = position; itr != position + n; itr++;) {
          alloc_.destroy(itr);
          alloc_.construct(itr, val);
        }
      }
    }
  }

  // range
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    // NOTE : gcc uses __is_integer to check whether the InputIterator is indeed
    // an iterator
    typedef typename is_integral<InputIterator>::type Integral;
    RangeInsert_(position, first, last, Integral());
  }

  // single element
  iterator erase(iterator position) {
    if (position + 1 == end_)
      pop_back();
    else {
      for (iterator itr = position; itr + 1 != end(); itr++) {
        alloc_.destroy(itr);
        alloc_.construct(itr, *(itr + 1));
      }
      end_--;
    }
  }

  // range
  iterator erase(iterator first, iterator last) {
    size_type n = 0;
    size_type move_cnt = 0;
    for (iterator itr = first; itr != last; itr++) {
      alloc_.destroy(itr);
      n++;
    }
    for (iterator itr = first; itr + n < end(); itr++) {
      if (move_cnt >= n) alloc_.destroy(itr);
      alloc_.construct(itr, *(itr + n));
      move_cnt++;
    }
    end_ -= n;
  }

  void swap(vector& x) {
    pointer temp_attr[3] = {begin_, end_, end_of_storage_};

    begin_ = x.begin();
    end_ = x.end();
    end_of_storage_ = x.end_of_storage_;
    x.begin_ = temp_attr[0];
    x.end_ = temp_attr[1];
    x.end_of_storage_ = temp_attr[2];
  }

  void clear(void) FT_NOEXCEPT_ {
    for (iterator itr = begin(); itr != end(); itr++) alloc_.destroy(itr);
  }

  // SECTION : get_allocator
  allocator_type get_allocator(void) const {}
};
};  // namespace ft

#endif
