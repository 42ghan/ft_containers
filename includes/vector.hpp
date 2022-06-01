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
#include <limits>
#include <memory>

#include "algorithm.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

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
  typedef typename traits_type_::iterator_category iterator_category;
  typedef typename traits_type_::value_type value_type;
  typedef typename traits_type_::difference_type difference_type;
  typedef typename traits_type_::reference reference;
  typedef typename traits_type_::pointer pointer;

  // Constructors
  VectorIterator(void) : current_(Iterator()) {}

  VectorIterator(const Iterator& itr) : current_(itr) {}

  VectorIterator(const VectorIterator& original) { *this = original; }

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
  reference operator[](difference_type n) FT_NOEXCEPT_ { return current_[n]; }

  // dereference & reference

  reference operator*(void) const FT_NOEXCEPT_ { return *current_; }

  pointer operator->(void) const FT_NOEXCEPT_ { return current_; }

  // add or subtract difference
  VectorIterator& operator+=(difference_type n) FT_NOEXCEPT_ {
    current_ += n;
    return *this;
  }

  VectorIterator& operator-=(difference_type n) FT_NOEXCEPT_ {
    current_ -= n;
    return *this;
  }

  VectorIterator operator+(difference_type n) const FT_NOEXCEPT_ {
    return VectorIterator(current_ + n);
  }

  VectorIterator operator-(difference_type n) const FT_NOEXCEPT_ {
    return VectorIterator(current_ - n);
  }

  const Iterator& base(void) const FT_NOEXCEPT_ { return current_; }
};

template <typename IteratorL, typename IteratorR>
inline bool operator==(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return !(lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator>(const VectorIterator<IteratorL>& lhs,
                      const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() > rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator<(const VectorIterator<IteratorL>& lhs,
                      const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() < rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator>=(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() >= rhs.base();
}

template <typename IteratorL, typename IteratorR>
inline bool operator<=(const VectorIterator<IteratorL>& lhs,
                       const VectorIterator<IteratorR>& rhs) FT_NOEXCEPT_ {
  return lhs.base() <= rhs.base();
}

template <typename Iterator>
inline typename VectorIterator<Iterator>::difference_type operator+(
    const VectorIterator<Iterator>& lhs,
    const VectorIterator<Iterator>& rhs) FT_NOEXCEPT_ {
  return lhs.base() + rhs.base();
}

template <typename Iterator>
inline typename VectorIterator<Iterator>::difference_type operator-(
    const VectorIterator<Iterator>& lhs,
    const VectorIterator<Iterator>& rhs) FT_NOEXCEPT_ {
  return lhs.base() - rhs.base();
}

// SECTION : vector base class (RAII wrapper)
template <typename T, typename Alloc = std::allocator<T> >
class VectorBase {
 protected:
  // member types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;

  pointer begin_;           // start of alloc
  pointer end_;             // end of sequence
  pointer end_of_storage_;  // end of alloc
  allocator_type alloc_;    // allocator

  void InitPointers_(const size_type n) {
    begin_ = alloc_.allocate(n);
    end_ = begin_;
    end_of_storage_ = begin_ + n;
  }

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

template <typename T, typename Alloc = std::allocator<T> >
class vector : protected VectorBase<T, Alloc> {
 private:
  typedef VectorBase<T, Alloc> Base_;
  // NOTE - check why using / this-> is necessary

  template <typename InputIterator>
  void RangeInitialize_(InputIterator first, InputIterator last) {
    typename iterator_traits<InputIterator>::difference_type n =
        std::distance<InputIterator>(first, last);
    this->InitPointers_(static_cast<size_type>(n));
    for (; first != last; first++) push_back(*first);
  }

  template <typename InputIterator>
  void RangeAssign_(InputIterator first, InputIterator last) {
    typename iterator_traits<InputIterator>::difference_type n =
        std::distance<InputIterator>(first, last);
    if (n > capacity()) {
      vector<value_type, allocator_type> temp(n, this->alloc_);
      temp.end_ = std::uninitialized_copy(first, last, temp.begin());
      swap(temp);
    } else {
      clear();
      this->end_ = std::uninitialized_copy(first, last, begin());
    }
  }

  template <typename iterator, typename InputIterator>
  void RangeInsert_(iterator position, InputIterator first,
                    InputIterator last) {
    typename iterator_traits<InputIterator>::difference_type n =
        std::distance<InputIterator>(first, last);
    if (position == end()) {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        temp.end_ =
            std::uninitialized_copy(begin(), end(), temp.begin()).base();
        swap(temp);
      }
      for (iterator itr = first; itr != last; itr++) push_back(*itr);
    } else {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        iterator insert_pos =
            std::uninitialized_copy(begin(), position, temp.begin());
        std::uninitialized_copy(first, last, insert_pos);
        temp.end_ = std::uninitialized_copy(position, end(), insert_pos + n);
        swap(temp);
      } else {
        this->end_ += n;
        for (reverse_iterator ritr = rbegin() - 1; ritr != position + n;
             ritr++) {
          this->alloc_.destroy(ritr);
          this->alloc_.construct(ritr, *(ritr + 1));
        }
        for (iterator itr = position; first != last; first++) {
          this->alloc_.destroy(itr.base());
          this->alloc_.construct(itr.base(), *first);
          itr++;
        }
      }
    }
  }

 public:
  // SECTION : member types
  typedef T value_type;
  typedef typename Base_::allocator_type allocator_type;
  typedef typename Base_::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename Base_::pointer pointer;
  typedef typename Base_::const_pointer const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef VectorIterator<const_pointer> const_iterator;
  typedef VectorIterator<pointer> iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;

  // SECTION : constructors & destructor
  // #1 default : empty container constructor (no elem)
  explicit vector(const allocator_type& alloc = allocator_type())
      : Base_(alloc) {}

  // #2 fill : construct a container with n elements, fill them with val
  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type())
      : Base_(n, alloc) {
    std::uninitialized_fill_n(begin(), n, val);
    this->end_ = this->begin_ + n;
  }

  // #3 range : construct a container that will contain the same values in the
  // range [first, last)  template <typename InputIterator>
  template <typename InputIterator>
  vector(typename enable_if<!is_integral<InputIterator>::value,
                            InputIterator>::type first,
         InputIterator last, const allocator_type& alloc = allocator_type())
      : Base_(alloc) {
    RangeInitialize_(first, last);
  }

  // #4 copy constructor (keeps and uses a copy of x's alloc)
  vector(const vector& x) : Base_(x.size(), x.alloc_) {
    this->end_ = std::uninitialized_copy(x.begin(), x.end(), begin()).base();
  }

  // destructor
  ~vector(void) FT_NOEXCEPT_ { clear(); }

  // SECTION : operator=
  // preserves the current allocator
  vector& operator=(const vector& x) {
    vector temp(x);
    swap(temp);
    return *this;
  }

  // SECTION : iterators
  iterator begin(void) FT_NOEXCEPT_ { return iterator(this->begin_); }

  const_iterator begin(void) const FT_NOEXCEPT_ {
    return const_iterator(this->begin_);
  }

  iterator end(void) FT_NOEXCEPT_ { return iterator(this->end_); }

  const_iterator end(void) const FT_NOEXCEPT_ {
    return const_iterator(this->end_);
  }

  reverse_iterator rbegin(void) FT_NOEXCEPT_ { return reverse_iterator(end()); }

  const_reverse_iterator rbegin(void) const FT_NOEXCEPT_ {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend(void) FT_NOEXCEPT_ { return reverse_iterator(begin()); }

  const_reverse_iterator rend(void) const FT_NOEXCEPT_ {
    return const_reverse_iterator(begin());
  }

  // SECTION : capacity
  size_type size(void) const FT_NOEXCEPT_ {
    return size_type(this->end_ - this->begin_);
  }

  size_type max_size(void) const FT_NOEXCEPT_ {
    const size_type diff_max =
        std::numeric_limits<size_type>::max() / sizeof(value_type);
    const size_type alloc_max = this->alloc_.max_size();
    return std::min(diff_max, alloc_max);
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n <= size())
      for (iterator itr = begin() + n; itr != end(); itr++)
        this->alloc_.destroy(itr.base());
    else {
      if (n > capacity()) reserve(n);
      std::uninitialized_fill_n(end(), n - size(), val);
    }
    this->end_ = this->begin_ + n;
  }

  size_type capacity(void) const FT_NOEXCEPT_ {
    return size_type(this->end_of_storage_ - this->begin_);
  }

  bool empty(void) const FT_NOEXCEPT_ { return begin() == end(); }

  void reserve(size_type n) {
    if (n > max_size())
      throw std::length_error("cannot reserve capacity larger than max_size");
    if (n > capacity()) {
      vector temp(n, value_type(), this->alloc_);
      temp.end_ = std::uninitialized_copy(begin(), end(), temp.begin()).base();
      swap(temp);
    }
  }

  // SECTION : element access
  reference operator[](size_type n) FT_NOEXCEPT_ { return *(begin() + n); }

  const_reference operator[](size_type n) const FT_NOEXCEPT_ {
    return *(begin() + n);
  }

  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range("exceeds the vector's size");
    return (*this)[n];
  }

  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range("exceeds the vector's size");
    return (*this)[n];
  }

  reference front(void) FT_NOEXCEPT_ { return *begin(); }

  const_reference front(void) const FT_NOEXCEPT_ { return *begin(); }

  reference back(void) FT_NOEXCEPT_ { return *(end() - 1); }

  const_reference back(void) const FT_NOEXCEPT_ { return *(end() - 1); }

  // SECTION : modifiers
  // range
  template <typename InputIterator>
  void assign(typename enable_if<!is_integral<InputIterator>::value,
                                 InputIterator>::type first,
              InputIterator last) {
    RangeAssign_(first, last);
  }

  // fill
  void assign(size_type n, const value_type& val) {
    if (n > capacity()) {
      vector<value_type, allocator_type> temp(n, val, this->alloc_);
      swap(temp);
    } else {
      clear();
      std::uninitialized_fill_n<iterator, size_type, value_type>(begin(), n,
                                                                 val);
      this->end_ = this->begin_ + n;
    }
  }

  void push_back(const value_type& val) {
    if (this->end_ != this->end_of_storage_) {
      this->alloc_.construct(this->end_, val);
      ++this->end_;
    } else {
      vector temp(size() + 1);
      std::uninitialized_copy(begin(), end(), temp.begin());
      temp.end_ = temp.begin_ + difference_type(end() - begin());
      this->alloc_.construct(temp.end_, val);
      temp.end_++;
      swap(temp);
    }
  }

  void pop_back(void) FT_NOEXCEPT_ {
    this->end_--;
    this->alloc_.destroy(this->end_);
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
        this->alloc_.construct(insert_pos, val);
        temp.end_ =
            std::uninitialized_copy(position + 1, end(), insert_pos + 1);
        swap(temp);
      } else {
        for (reverse_iterator ritr = rbegin(); ritr != position; ritr++) {
          if (ritr != rbegin()) this->alloc_.destroy(ritr);
          this->alloc_.construct(ritr, *(ritr + 1));
        }
        this->end_++;
        this->alloc_.construct(position, val);
      }
    }
  }

  // fill
  void insert(iterator position, size_type n, const value_type& val) {
    if (position == end()) {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        temp.end_ =
            std::uninitialized_copy(begin(), end(), temp.begin()).base();
        swap(temp);
      }
      for (size_type cnt = 0; cnt < n; cnt++) push_back(val);
    } else {
      if (size() + n > capacity()) {
        vector temp(size() + n);
        iterator insert_pos =
            std::uninitialized_copy(begin(), position, temp.begin());
        std::uninitialized_fill_n(insert_pos, n, val);
        temp.end_ = std::uninitialized_copy(position, end(), insert_pos + n);
        swap(temp);
      } else {
        this->end_ += n;
        for (reverse_iterator ritr = rbegin() - 1; ritr != position + n;
             ritr++) {
          this->alloc_.destroy(ritr);
          this->alloc_.construct(ritr, *(ritr + 1));
        }
        for (iterator itr = position; itr != position + n; itr++) {
          this->alloc_.destroy(itr.base());
          this->alloc_.construct(itr.base(), val);
        }
      }
    }
  }

  // range
  template <typename InputIterator>
  void insert(iterator position,
              typename enable_if<!is_integral<InputIterator>::value,
                                 InputIterator>::type first,
              InputIterator last) {
    RangeInsert_(position, first, last);
  }

  // single element
  iterator erase(iterator position) {
    if (position + 1 == end())
      pop_back();
    else {
      for (iterator itr = position; itr + 1 != end(); itr++) {
        this->alloc_.destroy(itr.base());
        this->alloc_.construct(itr.base(), *(itr + 1));
      }
      this->end_--;
    }
  }

  // range
  iterator erase(iterator first, iterator last) {
    size_type n = 0;
    size_type move_cnt = 0;
    for (iterator itr = first; itr != last; itr++) {
      this->alloc_.destroy(itr.base());
      n++;
    }
    for (iterator itr = first; itr + n < end(); itr++) {
      if (move_cnt >= n) this->alloc_.destroy(itr.base());
      this->alloc_.construct(itr.base(), *(itr + n));
      move_cnt++;
    }
    this->end_ -= n;
  }

  void swap(vector& x) {
    pointer temp_attr[3] = {this->begin_, this->end_, this->end_of_storage_};

    this->begin_ = x.begin().base();
    this->end_ = x.end().base();
    this->end_of_storage_ = x.end_of_storage_;
    x.begin_ = temp_attr[0];
    x.end_ = temp_attr[1];
    x.end_of_storage_ = temp_attr[2];
  }

  void clear(void) FT_NOEXCEPT_ {
    for (iterator itr = begin(); itr != end(); itr++)
      this->alloc_.destroy(itr.base());
  }

  // SECTION : get_allocator
  allocator_type get_allocator(void) const FT_NOEXCEPT_ {
    return allocator_type(this->alloc_);
  }
};

// SECTION : non-member function overloads (relational operators & swap)
template <class T, class Alloc>
inline bool operator==(const vector<T, Alloc>& lhs,
                       const vector<T, Alloc>& rhs) {
  return (lhs.size() == rhs.size() &&
          equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
inline bool operator!=(const vector<T, Alloc>& lhs,
                       const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
inline bool operator<(const vector<T, Alloc>& lhs,
                      const vector<T, Alloc>& rhs) {
  return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                 rhs.end());
}

template <class T, class Alloc>
inline bool operator<=(const vector<T, Alloc>& lhs,
                       const vector<T, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class T, class Alloc>
inline bool operator>(const vector<T, Alloc>& lhs,
                      const vector<T, Alloc>& rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
inline bool operator>=(const vector<T, Alloc>& lhs,
                       const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
  x.swap(y);
}

}  // namespace ft

#endif
