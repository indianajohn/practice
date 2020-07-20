#include "vector.hpp"
#include "assert.hpp"
#include "test_utils.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {

template <typename T>
prac::vector<T> randomVector(std::vector<T> *stl_vec = nullptr,
                             const size_t &size = rand() % 20 + 1) {
  prac::vector<T> new_vec;
  for (size_t j = 0; j < size; j++) {
    T val = randomVal<T>();
    new_vec.push_back(val);
    if (stl_vec) {
      stl_vec->push_back(val);
    }
  }
  return new_vec;
}

}; // namespace

template <typename T> void testConstruction() { prac::vector<T> my_vec; }

template <typename T> void testPushBack() {
  std::vector<T> stl_vector;
  prac::vector<T> vec = randomVector<T>(&stl_vector);
  ASSERT_EQ(vec.size(), stl_vector.size());
}

template <typename T> void testBracketOperator() {
  // Test that we can write to the vector and
  // the writes will be reflected. Also implicitly test
  // push_back further.
  std::vector<T> stl_vector;
  prac::vector<T> vec = randomVector<T>(&stl_vector);
  for (size_t i = 0; i < stl_vector.size(); i++) {
    ASSERT(stl_vector[i] == vec[i]);
  }
}

template <typename T> void testIterators() {
  // Test every form of iterator works, and that
  // C++ iterator helpers work.
  std::vector<T> stl_vector;
  prac::vector<T> vec = randomVector<T>(&stl_vector);
  size_t num_visitations = 0;
  for (auto itr = vec.begin(); itr != vec.end(); itr++) {
    ASSERT(vec[num_visitations] == *itr);
    num_visitations++;
  }
  ASSERT(num_visitations == stl_vector.size());
  num_visitations = 0;
  for (auto elem : vec) {
    ASSERT(vec[num_visitations] == elem);
    num_visitations++;
  }
  ASSERT(num_visitations == stl_vector.size());
  num_visitations = 0;
  for (auto &elem : vec) {
    ASSERT(vec[num_visitations] == elem);
    num_visitations++;
  }
  ASSERT(num_visitations == stl_vector.size());
  num_visitations = 0;
  for (const auto &elem : vec) {
    ASSERT(vec[num_visitations] == elem);
    num_visitations++;
  }
  ASSERT(num_visitations == stl_vector.size());
  // Ensure we can write back using the []
  // operator.
  prac::vector<T> new_values = randomVector<T>(nullptr, vec.size());
  for (size_t i = 0; i < vec.size(); i++) {
    vec[i] = new_values[i];
  }
  for (size_t i = 0; i < vec.size(); i++) {
    ASSERT(vec[i] == new_values[i]);
  }
}

template <typename T> void testReverseIterators() {
  std::vector<T> stl_vector;
  prac::vector<T> vec = randomVector<T>(&stl_vector);
  size_t num_visitations = 0;

  // Make sure reverse iterators iterate correctly (in the
  // opposite direction).
  for (auto itr = vec.rbegin(); itr != vec.rend(); itr++) {
    ASSERT(vec[vec.size() - num_visitations - 1] == *itr);
    num_visitations++;
  }
  ASSERT(num_visitations == stl_vector.size());

  // Make sure reverse iterators can write back.
  prac::vector<T> new_values = randomVector<T>(nullptr, vec.size());
  auto ritr = vec.rbegin();
  for (int i = vec.size() - 1; i >= 0; i--) {
    *ritr = new_values[i];
    ritr++;
  }
  ASSERT(ritr == vec.rend());
  for (size_t i = 0; i < vec.size(); i++) {
    ASSERT(vec[i] == new_values[i]);
  }
}

template <typename T> void testResizeLarger() {
  std::vector<T> stl_vec;
  prac::vector<T> vec = randomVector<T>(&stl_vec);
  size_t size_before = vec.size();
  auto val = randomVal<T>();
  int new_size = size_before + 20;
  vec.resize(new_size, val);
  ASSERT_EQ(vec.size(), new_size);
  for (size_t i = 0; i < size_before; i++) {
    ASSERT(vec[i] == stl_vec[i]);
  }
  for (size_t i = size_before; i < new_size; i++) {
    ASSERT(vec[i] == val);
  }
}

template <typename T> void testResizeSmaller() {
  std::vector<T> stl_vec;
  prac::vector<T> vec = randomVector<T>(&stl_vec, rand() % 30 + 20);
  size_t size_before = vec.size();
  auto val = randomVal<T>();
  int new_size = size_before - 10;
  vec.resize(new_size, val);
  ASSERT_EQ(vec.size(), new_size);
  for (size_t i = 0; i < size_before; i++) {
    ASSERT(vec[i] == stl_vec[i]);
  }
}

template <typename T> void testIterConstruction() {
  std::vector<T> stl_vec;
  prac::vector<T> vec = randomVector<T>(&stl_vec, rand() % 30 + 20);
  prac::vector<T> itr_constructed(stl_vec.begin(), stl_vec.end());
  ASSERT_EQ(itr_constructed.size(), stl_vec.size());
  for (size_t i = 0; i < stl_vec.size(); i++) {
    ASSERT(stl_vec[i] == itr_constructed[i]);
  }
}

template <typename T> void testOperators() {
  prac::vector<T> vec = randomVector<T>(nullptr, 5);
  size_t diff = vec.end() - vec.begin();
  ASSERT_EQ(diff, vec.size());
  ASSERT(vec.end() > vec.begin());
  ASSERT(vec.begin() < vec.end());
  auto itr = vec.begin();
  itr = itr + 1;
  ASSERT(*itr == vec[1]);
  itr = itr - 1;
  ASSERT(*itr == vec[0]);
  auto forward_postfix = itr++;
  ASSERT(*itr == vec[1]);
  ASSERT(*forward_postfix == vec[0]);
  auto reverse_postfix = itr--;
  ASSERT(*reverse_postfix == vec[1]);
  ASSERT(*itr == vec[0]);
  auto forward_prefix = ++itr;
  ASSERT(*itr == vec[1]);
  ASSERT(*forward_prefix == vec[1]);
  auto reverse_prefix = --itr;
  ASSERT(*reverse_prefix == vec[0]);
  ASSERT(*itr == vec[0]);
}

template <typename T> void testReverseOperators() {
  prac::vector<T> vec = randomVector<T>(nullptr, 5);
  size_t last = vec.size() - 1;
  size_t diff = vec.rend() - vec.rbegin();
  ASSERT_EQ(diff, vec.size());
  ASSERT(vec.rend() > vec.rbegin());
  ASSERT(vec.rbegin() < vec.rend());
  auto itr = vec.rbegin();
  ASSERT(*itr == vec[last]);
  itr = itr + 1;
  ASSERT(*itr == vec[last - 1]);
  itr = itr - 1;
  ASSERT(*itr == vec[last]);
  auto forward_postfix = itr++;
  ASSERT(*itr == vec[last - 1]);
  ASSERT(*forward_postfix == vec[last]);
  auto reverse_postfix = itr--;
  ASSERT(*reverse_postfix == vec[last - 1]);
  ASSERT(*itr == vec[last]);
  auto forward_prefix = ++itr;
  ASSERT(*itr == vec[last - 1]);
  ASSERT(*forward_prefix == vec[last - 1]);
  auto reverse_prefix = --itr;
  ASSERT(*reverse_prefix == vec[last]);
  ASSERT(*itr == vec[last]);
}

template <typename T> void testAlgorithms() {
  {
    std::vector<T> stl_vec;
    prac::vector<T> vec = randomVector<T>(&stl_vec, rand() % 30 + 20);
    std::sort(vec.begin(), vec.end());
    for (size_t i = 1; i < vec.size(); i++) {
      ASSERT(vec[i - 1] <= vec[i]);
    }
  }
  {
    std::vector<T> stl_vec;
    prac::vector<T> vec = randomVector<T>(&stl_vec, rand() % 30 + 20);
    std::sort(vec.rbegin(), vec.rend());
    for (size_t i = 1; i < vec.size(); i++) {
      ASSERT(vec[i - 1] >= vec[i]);
    }
  }
}

template <typename T> void testAll() {
  for (size_t trials = 0; trials < 50; trials++) {
    testConstruction<T>();
    testPushBack<T>();
    testBracketOperator<T>();
    testIterators<T>();
    testReverseIterators<T>();
    testResizeLarger<T>();
    testResizeSmaller<T>();
    testIterConstruction<T>();
    testOperators<T>();
    testReverseOperators<T>();
    testAlgorithms<T>();
  }
}

int main(int argc, char **argv) {
  testAll<int>();
  testAll<std::string>();
  testAlgorithms<int>();
}
