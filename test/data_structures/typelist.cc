#include "../../src/type_list.h"
#include <gtest/gtest.h>
#include <type_traits>

using namespace guitl;

template<typename T>
struct is_int : std::false_type{};

template<>
struct is_int<int> : std::true_type{};

using list = Typelist<int, char, float, std::string, long, char, float, float>;
static_assert(count_unique<InsertionSort<list, type_cmp>> == 5);
static_assert(count_frequency<list, int> == 1);
static_assert(count_frequency<list, char> == 2);
static_assert(count_frequency<list, long> == 1);
static_assert(count_frequency<list, float> == 3);
static_assert(std::is_same_v<filter<is_int, list>, Typelist<int>>);
static_assert(count_frequency<filter<is_int, list>, int> == 1);
