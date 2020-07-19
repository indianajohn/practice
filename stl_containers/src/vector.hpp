#pragma once
#include <iterator>
#include <stddef.h>

namespace prac {
template <typename T> class vector {
public:
  vector(size_t num_elements = 0, T default_value = T())
      : m_num_elements(num_elements) {
    m_num_allocated = 10 + num_elements;
    m_storage = new T[m_num_allocated];
    for (size_t i = 0; i < m_num_elements; i++) {
      m_storage[i] = default_value;
    }
  }

  void push_back(const T &new_elem) {
    if (m_num_elements >= m_num_allocated) {
      this->allocate(m_num_allocated * 2);
    }
    m_storage[m_num_elements] = new_elem;
    m_num_elements++;
  }

  const T &operator[](const size_t &i) const { return m_storage[i]; }

  T &operator[](const size_t &i) { return m_storage[i]; }

  size_t size() const { return m_num_elements; }

  void resize(const size_t &sz, const T &default_value) {
    // Reallocate
    if (sz >= m_num_elements) {
      this->allocate(sz + 10);
    }
    // Allocate copied our values. We need to set the
    // remaining defaults.
    for (size_t i = m_num_elements; i < sz; i++) {
      m_storage[i] = default_value;
    }
    // Change the tracking variable.
    m_num_elements = sz;
  }

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
                             T,                       // difference_type
                             const T *,               // pointer
                             T                        // reference
                             > {
    vector<T> *m_vector = nullptr;
    size_t m_pos;

  public:
    iterator(vector<T> *vector, size_t pos = 0)
        : m_vector(vector), m_pos(pos) {}
    iterator &operator++() {
      m_pos++;
      return *this;
    }
    iterator operator++(int) {
      iterator retval = *this;
      ++(*this);
      return retval;
    }
    bool operator==(iterator other) const { return m_pos == other.m_pos; }
    bool operator!=(iterator other) const { return !(*this == other); }
    const T &operator*() const { return m_vector->operator[](m_pos); }
    T &operator*() { return m_vector->operator[](m_pos); }
  };
  iterator begin() { return iterator(this); }
  iterator end() { return iterator(this, this->size()); }
  const iterator cbegin() const { return iterator(this); }
  const iterator cend() const { return iterator(this, this->size()); }

  class reverse_iterator
      : public std::iterator<std::input_iterator_tag, // iterator_category
                             T,                       // value_type
                             T,                       // difference_type
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
    bool operator==(reverse_iterator other) const {
      return m_pos == other.m_pos;
    }
    bool operator!=(reverse_iterator other) const { return !(*this == other); }
    T &operator*() const {
      return m_vector->operator[](m_vector->size() - m_pos - 1);
    }
  };
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
