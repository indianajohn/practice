#pragma once
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

private:
  size_t m_size;
  ListNode<T> *m_front;
  ListNode<T> *m_back;
};
}; // namespace prac
