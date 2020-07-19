#include "vector.hpp"
#include "assert.hpp"
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

void testConstruction() {
  prac::vector<int> int_vec;
  prac::vector<std::string> my_vec;
}

template <typename T> void testPushBack() {
  // For now, just make sure we don't seg fault on
  // construction and push_back.
  std::vector<T> stl_vector;
  prac::vector<T> vec = randomVector<T>(&stl_vector);
  ASSERT_EQ(vec.size(), stl_vector.size());
}

int main(int argc, char **argv) {
  testConstruction();
  testPushBack<int>();
  testPushBack<std::string>();
}
