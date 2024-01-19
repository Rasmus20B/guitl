#pragma once

#include <initializer_list>
#include <numeric>
#include <array>
#include <source_location>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <memory>

#include "type_list/type_list.h"
#include "widget.h"

namespace guitl {


  template<typename T, int N>
  consteval std::array<T, N> create_iota_array() {
    std::array<T, N> arr;
    std::iota(arr.begin(), arr.end(), 0);
    return arr;
  }

  template<typename T>
  struct wrapper {
    using type = T;
  };

  template<typename id_type = uint32_t, typename... W>
  struct static_gui {
    using widgets = InsertionSort<Typelist<W...>, type_cmp>;
    using widget_classes = remove_duplicates<Typelist<W...>>;
    static constexpr auto n_unique_widgets = count_unique<widgets>;
    static constexpr int max_group_elems = count_unique<widgets>;
    using pool_type = std::array<id_type, sizeof...(W)>;
    using registry_type = std::array<std::array<Widget, sizeof...(W)>, n_unique_widgets>;

    template<class F>
    constexpr decltype(auto) print_all_types(F&& f) {
      return [&] <std::size_t... I>
      (F&& f, std::index_sequence<I...>) {
        (print<at<widget_classes, I>>(), ...);
      }(std::forward<F>(f),
        std::make_index_sequence<widget_classes::size>());
    }

    consteval registry_type generate_static_registry(W&&...args) {

      registry_type res;
      std::array<int, n_unique_widgets> idxs{};
      constexpr_for([&res, &idxs](const auto v) {
          if constexpr(std::is_same_v<decltype(v), Button>) {
            res[0][idxs[0]] = static_cast<Button>(v);
            idxs[0]++;
          } else if(std::is_same_v<decltype(v), Textbox>) {
            res[1][idxs[1]] = v;
            idxs[1]++;
          }
        }, args...);
      return res;
    }

    consteval static_gui(W&& ...Args) : widget_types(create_iota_array<id_type, sizeof...(W)>()),
      registry(generate_static_registry(std::forward<W>(Args)...)) {
      }

    pool_type widget_types; 
    registry_type registry;
    uint32_t count{};
  };

}
