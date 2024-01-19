#include "../../src/type_list/type_list.h"
#include "../../src/widget.h"
#include <gtest/gtest.h>
#include <type_traits>

using namespace guitl;

template<typename T>
struct is_int : std::false_type{};
template<>
struct is_int<int> : std::true_type{};

template<typename T>
struct is_char : std::false_type{};
template<>
struct is_char<char> : std::true_type{};


using list = Typelist<char, float, int, std::string, long, char, float, float>;
static_assert(count_unique<InsertionSort<list, type_cmp>> == 5);
static_assert(count_frequency<is_int, list> == 1);
static_assert(count_frequency<is_char, list> == 2);
static_assert(std::is_same_v<filter<is_int, list>, Typelist<int>>);
static_assert(count_frequency<is_int, filter<is_int, list>> == 1);
static_assert(count_frequency_of_type<int, filter<is_int, list>> == 1);

static_assert(std::is_same_v<remove_duplicates<list>, Typelist<char, float, int, long, std::string>>);

static_assert(std::is_same_v<filter_on_type<int, list>, Typelist<int>>);

static_assert(remove_duplicates<list>::size == count_unique<InsertionSort<list, type_cmp>>);

static_assert(guitl::type_code<guitl::Button>::value != guitl::type_code<guitl::Textbox>::value);

int main() {
  print<at<list, 0>>();
  print<at<list, 1>>();
  print<at<list, 2>>();
  print<at<list, 3>>();
  print<at<list, 4>>();
  print<at<list, 5>>();
  print<at<list, 6>>();
  print<at<list, 7>>();

  std::cout << guitl::type_code<guitl::Button>::value << "\n";
  std::cout << guitl::type_code<guitl::Textbox>::value << "\n";
}
