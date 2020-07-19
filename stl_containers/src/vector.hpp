#pragma once
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
      T *new_storage = new T[m_num_allocated * 2];
      for (size_t i = 0; i < m_num_elements; i++) {
        new_storage[i] = m_storage[i];
      }
      delete[] m_storage;
      m_num_allocated = 2 * m_num_allocated;
      m_storage = new_storage;
    }
    m_storage[m_num_elements] = new_elem;
    m_num_elements++;
  }

  size_t size() const { return m_num_elements; }

private:
  T *m_storage;
  size_t m_num_allocated;
  size_t m_num_elements;
};
}; // namespace prac
