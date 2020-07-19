#include "assert.hpp"

int main(int argc, char **argv) {
  ASSERT_EQ(true, true);
  ASSERT(true);
  ASSERT_NEAR(3.0, 3.0);
  ASSERT_TOL(3.0001, 3.0, 1e-3);
}
