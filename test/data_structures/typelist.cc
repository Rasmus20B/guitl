#include "../../src/type_list.h"
#include <gtest/gtest.h>

using namespace guitl;

TEST(sparse_set, emplace_new) {

  using list = Typelist<int, char, float, std::string, long, char, float, float>;

  static_assert(count_unique<InsertionSort<list, type_cmp>> == 5);
  static_assert(count_frequency<list, int> == 1);
  static_assert(count_frequency<list, char> == 2);
  static_assert(count_frequency<list, long> == 1);
  static_assert(count_frequency<list, float> == 3);
}
