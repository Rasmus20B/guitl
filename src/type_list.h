#pragma once

#include <type_traits>
#include <string_view>
#include <source_location>

template<typename T>
struct Identity {
  using value = T;
};

template<typename... Elems>
struct Typelist {
  static inline constexpr size_t size = sizeof...(Elems);
};

template<typename List>
struct FrontT;

template<typename Head, typename... Tail>
struct FrontT<Typelist<Head, Tail...>> {
  using value = Head;
};

template<>
struct FrontT <Typelist<>> {
  using value = std::false_type; 
};

template<typename List>
using Front = typename FrontT<List>::value;

template<typename List>
struct PopFrontT;

template<>
struct PopFrontT <Typelist<>> {
  using value = Typelist<>;
};

template<typename Head, typename ...Tail>
struct PopFrontT <Typelist<Head, Tail...>>{
  using value = Typelist<Tail...>;
};

template<typename List>
using PopFront = typename PopFrontT<List>::value;

template<typename A, typename B, typename List>
struct count_uniqueT;

template<typename List, typename Element>
struct PushFrontT;

template<typename... List, typename Element>
struct PushFrontT <Typelist<List...>, Element> {
  using value = Typelist<Element, List...>;
};

template<typename List, typename Element>
using PushFront = typename PushFrontT<List, Element>::value;

template<typename A, typename B, typename Tail>
struct count_uniqueT {
  static inline constexpr size_t value = (!std::is_same_v<A, B>) + count_uniqueT<B, Front<PopFront<Tail>>, PopFront<Tail>>::value;
};

template<typename A, typename B>
struct count_uniqueT<A, B, Typelist<>>  {
  static inline constexpr size_t value = (!std::is_same_v<A, B>);
};

template<typename T>
[[nodiscard]] consteval std::string_view templateID() {
  return std::source_location::current().function_name();
}

template<typename T, typename U>
struct type_cmp {
  static inline constexpr bool value = (templateID<T>()) < (templateID<U>());
};

template<typename List, typename Element,
  template<typename T, typename U> typename Compare, bool = (std::is_same_v<List, Typelist<>>)>
  struct InsertSortedT;

// Recursive Case
template<typename List, typename Element,
  template<typename T, typename U> class Compare>
  struct InsertSortedT<List, Element, Compare, false> {
    using NewTail = typename std::conditional<Compare<Element, Front<List>>::value,
                                Identity<List>,
                                InsertSortedT<PopFront<List>, Element, Compare>>::type;

    using NewHead = typename std::conditional<Compare<Element, Front<List>>::value,
                                Element,
                                Front<List>>::type;

    using value = PushFront<typename NewTail::value, NewHead>;
  };

// Base Case
template<typename List, typename Element,
  template<typename T, typename U> class Compare>
  struct InsertSortedT<List, Element, Compare, true> 
: public PushFrontT<List, Element>
  {};

template<typename List, typename Element,
  template<typename T, typename U> class Compare>
  using InsertSorted = typename InsertSortedT<List, Element, Compare>::value;

template<typename List,
  template<typename T, typename U> typename Compare, 
  bool = std::is_same_v<List, Typelist<>> >
  struct InsertionSortT;

template<typename List,
  template<typename T, typename U> class Compare>
  using InsertionSort = typename InsertionSortT<List, Compare>::value;

// Recursive Case
template<typename List,
  template<typename T, typename U> class Compare>
  struct InsertionSortT<List, Compare, false>
  : public InsertSortedT<InsertionSort<PopFront<List>, Compare>,
                         Front<List>, Compare> {};

// Base Case
template<typename List,
  template<typename T, typename U> class Compare>
  struct InsertionSortT<List, Compare, true> {
  using value = List;
  };

template<typename haystack, typename needle>
struct count_frequencyT;

template<typename Haystack, typename Needle>
struct count_frequencyT {
  static constexpr int value = std::is_same_v<Front<Haystack>, Needle> + count_frequencyT<PopFront<Haystack>, Needle>::value;
};

template<typename Needle>
struct count_frequencyT<Typelist<>, Needle> {
  static constexpr int value = 0;
};

template<typename List> 
inline static constexpr size_t count_unique = count_uniqueT<Front<List>, Front<PopFront<List>>, PopFront<List>>::value;

template<typename List, typename Needle>
inline static constexpr size_t count_frequency = count_frequencyT<List, Needle>::value;
