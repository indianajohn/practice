#pragma once
#include <iostream>
#include <iterator>
#include <stddef.h>

namespace prac {
/*
 * A dynamically-sized container with contiguous storage.
 * Insertion in O(1) amortized time, random O(1) access.
 */
template <typename T> class vector {
public:
  /// Construction from size and default value.
  /*
   * @param num_elements - The initial size of the container.
   * @param end - The value to which to set all elements.
   */
  vector(size_t num_elements = 0, T default_value = T())
      : m_num_elements(num_elements) {
    m_num_allocated = 10 + num_elements;
    m_storage = new T[m_num_allocated];
    for (size_t i = 0; i < m_num_elements; i++) {
      m_storage[i] = default_value;
    }
  }

  /// Construction from STL container iterators.
  /*
   * @param begin - the beginning iterator.
   * @param end - the ending iterator.
   */
  template <typename Other> vector(const Other &begin, const Other &end) {
    m_num_allocated = 10;
    m_num_elements = 0;
    m_storage = new T[m_num_allocated];
    for (auto itr = begin; itr != end; itr++) {
      this->push_back(*itr);
    }
  }

  /// Push back a new element to the container.
  /*
   * This can result in a reallocation if we haven't
   * already allocated enough storage. This amortizes
   * to O(1).
   * @param new_elem - the new element to add.
   */
  void push_back(const T &new_elem) {
    if (m_num_elements >= m_num_allocated) {
      this->allocate(m_num_allocated * 2);
    }
    m_storage[m_num_elements] = new_elem;
    m_num_elements++;
  }

  /// Retrieve an element.
  /*
   * O(1) random access.
   *
   * This method does not check bounds for performance. If you
   * access greater than size() index, you will get a segmentation
   * fault.
   * @param i - the index at which to retrieve the element.
   * @return a reference to the element.
   *
   */
  const T &operator[](const size_t &i) const { return m_storage[i]; }

  /// Retrieve an element.
  /*
   * O(1) random access.
   *
   * This method does not check bounds for performance. If you
   * access greater than size() index, you will get a segmentation
   * fault.
   * @param i - the index at which to retrieve the element.
   * @return a reference to the element.
   *
   */
  T &operator[](const size_t &i) { return m_storage[i]; }

  // Retrieve the size of the container.
  /*
   * @return the number of elements that have been stored.
   */
  size_t size() const { return m_num_elements; }

  // Resize the container.
  /*
   * Up to O(n)
   * If the container size requested is larger than the current
   * value, default_value (or the default value of the class) will
   * be added to the end. If the requested size is smaller, there
   * will obviously be a loss of elements. A reallocation will
   * occur if the new size is beyond the current allocated storage
   * size.
   * @param sz - the new size of the container.
   * @param default_value - the value to which to set the new
   *                        storage.
   */
  void resize(const size_t &sz, const T &default_value = T()) {
    // Reallocate
    if (sz > m_num_elements) {
      this->allocate(sz + 10);
      // Allocate copied our values. We need to set the
      // remaining defaults.
      for (size_t i = m_num_elements; i < sz; i++) {
        m_storage[i] = default_value;
      }
      // Change the tracking variable.
    }
    m_num_elements = sz;
  }

  // Allocate at least sz elements in the storage.
  /*
   * Up to O(n)
   * @param sz - the number of elements w need, at least.
   */
  void allocate(const size_t &sz) {
    if (sz > m_num_allocated) {
      T *new_storage = new T[sz];
      for (size_t i = 0; i < m_num_elements; i++) {
        new_storage[i] = m_storage[i];
      }
      delete[] m_storage;
      m_num_allocated = sz;
      m_storage = new_storage;
    }
  }

  class iterator
      : public std::iterator<std::input_iterator_tag, // iterator_category
                             T,                       // value_type
                             size_t,                       // difference_type
                             const T *,               // pointer
                             T                        // reference
                             > {
    vector<T> *m_vector = nullptr;
    size_t m_pos;

  public:
    iterator(vector<T> *vector, size_t pos = 0)
        : m_vector(vector), m_pos(pos) {}

    /// Prefix
    iterator &operator++() {
      m_pos++;
      return *this;
    }

    /// Postfix
    iterator operator++(int) {
      iterator retval = *this;
      ++(*this);
      return retval;
    }

    /// Prefix
    iterator &operator--() {
      m_pos--;
      return *this;
    }

    /// Postfix
    iterator operator--(int) {
      iterator retval = *this;
      --(*this);
      return retval;
    }

    size_t operator-(const iterator &iterator) {
      return this->m_pos - iterator.m_pos;
    }

    iterator operator+(const size_t &count) {
      iterator return_val = *this;
      return_val.m_pos += count;
      return return_val;
    }

    iterator operator-(const size_t &count) {
      iterator return_val = *this;
      return_val.m_pos -= count;
      return return_val;
    }

    bool operator<(const iterator &iterator) {
      return this->m_pos < iterator.m_pos;
    }

    bool operator>(const iterator &iterator) {
      return this->m_pos > iterator.m_pos;
    }

    bool operator==(iterator other) const { return m_pos == other.m_pos; }

    bool operator!=(iterator other) const { return !(*this == other); }

    const T &operator*() const { return m_vector->operator[](m_pos); }

    T &operator*() { return m_vector->operator[](m_pos); }
  };

  // Forward iterators. All of these are created and incremented in O(1).
  iterator begin() { return iterator(this); }
  iterator end() { return iterator(this, this->size()); }
  const iterator cbegin() const { return iterator(this); }
  const iterator cend() const { return iterator(this, this->size()); }

  class reverse_iterator
      : public std::iterator<std::input_iterator_tag, // iterator_category
                             T,                       // value_type
                             size_t,                       // difference_type
                             const T *,               // pointer
                             T                        // reference
                             > {
    vector<T> *m_vector = nullptr;
    size_t m_pos;

  public:
    reverse_iterator(vector<T> *vector, size_t pos = 0)
        : m_vector(vector), m_pos(pos) {}
    reverse_iterator &operator++() {
      m_pos++;
      return *this;
    }
    reverse_iterator operator++(int) {
      reverse_iterator retval = *this;
      ++(*this);
      return retval;
    }

    reverse_iterator &operator--() {
      m_pos--;
      return *this;
    }

    reverse_iterator operator--(int) {
      reverse_iterator retval = *this;
      --(*this);
      return retval;
    }

    size_t operator-(const reverse_iterator &iterator) {
      return this->m_pos - iterator.m_pos;
    }

    bool operator<(const reverse_iterator &iterator) {
      return this->m_pos < iterator.m_pos;
    }

    bool operator>(const reverse_iterator &iterator) {
      return this->m_pos > iterator.m_pos;
    }

    reverse_iterator operator+(const size_t &count) {
      reverse_iterator return_val = *this;
      return_val.m_pos += count;
      return return_val;
    }

    reverse_iterator operator-(const size_t &count) {
      reverse_iterator return_val = *this;
      return_val.m_pos -= count;
      return return_val;
    }

    bool operator==(reverse_iterator other) const {
      return m_pos == other.m_pos;
    }
    bool operator!=(reverse_iterator other) const { return !(*this == other); }
    T &operator*() const {
      return m_vector->operator[](m_vector->size() - m_pos - 1);
    }
  };

  // Reverse iterators. All of these are created and incremented in O(1).
  reverse_iterator rbegin() { return reverse_iterator(this); }
  reverse_iterator rend() { return reverse_iterator(this, this->size()); }
  const reverse_iterator crbegin() const { return iterator(this); }
  const reverse_iterator crend() const { return iterator(this, this->size()); }

private:
  T *m_storage;
  size_t m_num_allocated;
  size_t m_num_elements;
};
}; // namespace prac
