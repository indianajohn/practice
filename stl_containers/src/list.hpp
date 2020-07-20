#pragma once
#include <stddef.h>

namespace prac {

template <typename T> class list {
public:
  list() : m_size(0) {}
  void push_back(const T &new_elem) { m_size++; }
  size_t size() const { return m_size; }

private:
  size_t m_size;
};
}; // namespace prac
