#include "vector.hpp"
#include "assert.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace {

template <typename T> T randomVal() { return T(rand() % 1000); }

template <> std::string randomVal<std::string>() {
  size_t num_chars = rand() % 20;
  std::string new_val;
  for (size_t j = 0; j < num_chars; j++) {
    new_val.push_back('a' + (rand() % 26));
  }
  return new_val;
}

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

template <typename T> void testAll() {
  testConstruction<T>();
  testPushBack<T>();
  testBracketOperator<T>();
  testIterators<T>();
  testReverseIterators<T>();
}

int main(int argc, char **argv) {
  testAll<int>();
  testAll<std::string>();
}
