#include "list.hpp"
#include "assert.hpp"
#include "test_utils.hpp"
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

template <typename T> void testAll() {
  testConstruction<T>();
  testPushBack<T>();
}

int main(int argc, char **argv) {
  testAll<int>();
  testAll<std::string>();
}
