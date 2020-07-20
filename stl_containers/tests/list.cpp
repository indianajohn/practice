#include "list.hpp"
#include "assert.hpp"
#include "test_utils.hpp"
#include <iostream>
#include <list>
#include <string>

namespace {

template <typename T>
prac::list<T> randomList(std::list<T> *stl_list = nullptr,
                         const size_t &size = rand() % 20 + 1) {
  prac::list<T> new_list;
  for (size_t j = 0; j < size; j++) {
    T val = randomVal<T>();
    new_list.push_back(val);
    if (stl_list) {
      stl_list->push_back(val);
    }
  }
  return new_list;
}

}; // namespace

template <typename T> void testConstruction() { prac::list<T> new_list; }

template <typename T> void testPushBack() {
  std::list<T> stl_list;
  prac::list<T> new_list = randomList<T>(&stl_list);
  ASSERT_EQ(new_list.size(), stl_list.size());
}

template <typename T> void testPushFront() {
  std::list<T> stl_list;
  prac::list<T> new_list;
  size_t size = rand() % 20 + 1;
  for (size_t j = 0; j < size; j++) {
    T val = randomVal<T>();
    new_list.push_front(val);
    stl_list.push_front(val);
  }
  ASSERT_EQ(new_list.size(), stl_list.size());
}

template <typename T> void testBack() {
  std::list<T> stl_list;
  prac::list<T> new_list = randomList<T>(&stl_list);
  while (new_list.size() > 0) {
    ASSERT(stl_list.back() == new_list.back());
    new_list.pop_back();
    stl_list.pop_back();
  }
}

template <typename T> void testFront() {
  std::list<T> stl_list;
  prac::list<T> new_list = randomList<T>(&stl_list);
  while (new_list.size() > 0) {
    ASSERT(stl_list.front() == new_list.front());
    new_list.pop_front();
    stl_list.pop_front();
  }
}

template <typename T> void testForwardIterators() {
  std::list<T> stl_list;
  prac::list<T> new_list = randomList<T>(&stl_list);
  auto itr = new_list.begin();
  auto stl_itr = stl_list.begin();
  size_t num_nodes = 0;
  while (itr != new_list.end()) {
    ASSERT(*itr == *stl_itr);
    itr++;
    stl_itr++;
    num_nodes++;
  }
  ASSERT(num_nodes == new_list.size());
  ASSERT(itr == new_list.end());
  ASSERT(stl_itr == stl_list.end());
}

template <typename T> void testReverseIterators() {
  std::list<T> stl_list;
  prac::list<T> new_list = randomList<T>(&stl_list);
  auto itr = new_list.rbegin();
  auto stl_itr = stl_list.rbegin();
  size_t num_nodes = 0;
  while (itr != new_list.rend()) {
    ASSERT(*itr == *stl_itr);
    itr++;
    stl_itr++;
    num_nodes++;
  }
  ASSERT(num_nodes == new_list.size());
  ASSERT(itr == new_list.rend());
  ASSERT(stl_itr == stl_list.rend());
}

template <typename T> void testSTLConstruction() {
  std::list<T> stl_list;
  prac::list<T> new_list = randomList<T>(&stl_list);
  prac::list<T> copied_list(stl_list.begin(), stl_list.end());
  auto itr = copied_list.begin();
  auto stl_itr = stl_list.begin();
  size_t num_nodes = 0;
  while (itr != new_list.end()) {
    ASSERT(*itr == *stl_itr);
    itr++;
    stl_itr++;
    num_nodes++;
  }
  ASSERT(num_nodes == stl_list.size());
  ASSERT(itr == copied_list.end());
  ASSERT(stl_itr == stl_list.end());
}

template <typename T> void testAll() {
  testConstruction<T>();
  testPushBack<T>();
  testPushFront<T>();
  testBack<T>();
  testForwardIterators<T>();
  testReverseIterators<T>();
  testSTLConstruction<T>();
}

int main(int argc, char **argv) {
  testAll<int>();
  testAll<std::string>();
}
