#include <string>
#include <vector>
#pragma once

template <typename T> T randomVal() { return T(rand() % 1000); }

template <> std::string randomVal<std::string>() {
  size_t num_chars = rand() % 20;
  std::string new_val;
  for (size_t j = 0; j < num_chars; j++) {
    new_val.push_back('a' + (rand() % 26));
  }
  return new_val;
}

