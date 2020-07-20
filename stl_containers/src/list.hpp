#pragma once
#include <iterator>
#include <stddef.h>

namespace prac {

// A doubly-linked list.
template <typename T> struct ListNode {
  ListNode(const T &val_in) : val(val_in), last(nullptr), next(nullptr) {}
  ListNode<T> *last;
  ListNode<T> *next;
  T val;
};

template <typename T> class list {
public:
  list() : m_size(0), m_front(nullptr), m_back(nullptr) {}
  void push_back(const T &new_elem) {
    if (m_front == nullptr) {
      m_front = new ListNode<T>(new_elem);
      m_back = m_front;
    } else {
      m_back->next = new ListNode<T>(new_elem);
      m_back->next->last = m_back;
      m_back = m_back->next;
    }
    m_size++;
  }

  void push_front(const T &new_elem) {
    if (m_front == nullptr) {
      m_front = new ListNode<T>(new_elem);
      m_back = m_front;
    } else {
      ListNode<T> *new_node = new ListNode<T>(new_elem);
      new_node->next = m_front;
      m_front = new_node;
      m_front->next->last = m_front;
    }
    m_size++;
  }

  const T &front() const { return m_front->val; }

  T &front() { return m_front->val; }

  void pop_front() {
    m_front = m_front->next;
    if (m_front) {
      delete m_front->last;
      m_front->last = nullptr;
    }
    m_size--;
  }

  void pop_back() {
    m_back = m_back->last;
    if (m_back) {
      delete m_back->next;
      m_back->next = nullptr;
    }
    m_size--;
  }

  const T &back() const { return m_back->val; }

  T &back() { return m_back->val; }

  ~list() {
    while (m_front != nullptr) {
      auto last = m_front;
      m_front = m_front->next;
      delete last;
    }
  }

  size_t size() const { return m_size; }

  class iterator
      : public std::iterator<std::input_iterator_tag, // iterator_category
                             T,                       // value_type
                             size_t,                  // difference_type
                             const T *,               // pointer
                             T                        // reference
                             > {
    ListNode<T> *m_node = nullptr;

  public:
    iterator(ListNode<T> *node) : m_node(node) {}

    /// Prefix
    iterator &operator++() {
      m_node = m_node->next;
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
      m_node = m_node->last;
      return *this;
    }

    /// Postfix
    iterator operator--(int) {
      iterator retval = *this;
      --(*this);
      return retval;
    }

    bool operator==(iterator other) const { return m_node == other.m_node; }

    bool operator!=(iterator other) const { return !(*this == other); }

    const T &operator*() const { return m_node->val; }

    T &operator*() { return m_node->val; }
  };

  /// Forward iterators. All of these are created and incremented in O(1).
  iterator begin() { return iterator(this->m_front); }
  iterator end() { return iterator(nullptr); }
  const iterator cbegin() const { return iterator(this->m_front); }
  const iterator cend() const { return iterator(nullptr); }

  class reverse_iterator
      : public std::iterator<std::input_iterator_tag, // iterator_category
                             T,                       // value_type
                             size_t,                  // difference_type
                             const T *,               // pointer
                             T                        // reference
                             > {
    ListNode<T> *m_node = nullptr;

  public:
    reverse_iterator(ListNode<T> *node, size_t pos = 0) : m_node(node) {}

    /// Prefix
    reverse_iterator &operator++() {
      m_node = m_node->last;
      return *this;
    }

    /// Postfix
    reverse_iterator operator++(int) {
      reverse_iterator retval = *this;
      ++(*this);
      return retval;
    }

    /// Prefix
    reverse_iterator &operator--() {
      m_node = m_node->next;
      return *this;
    }

    /// Postfix
    reverse_iterator operator--(int) {
      reverse_iterator retval = *this;
      --(*this);
      return retval;
    }

    bool operator==(reverse_iterator other) const {
      return m_node == other.m_node;
    }

    bool operator!=(reverse_iterator other) const { return !(*this == other); }

    const T &operator*() const { return m_node->val; }

    T &operator*() { return m_node->val; }
  };

  /// Forward iterators. All of these are created and incremented in O(1).
  reverse_iterator rbegin() { return reverse_iterator(this->m_back); }
  reverse_iterator rend() { return reverse_iterator(nullptr); }
  const reverse_iterator crbegin() const {
    return reverse_iterator(this->m_front);
  }
  const reverse_iterator crend() const { return reverse_iterator(nullptr); }

private:
  size_t m_size;
  ListNode<T> *m_front;
  ListNode<T> *m_back;
};
}; // namespace prac
