#pragma once

#include <numeric>
#include <array>
#include <source_location>
#include <type_traits>
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

  template<typename id_type = uint32_t, typename... W>
  struct static_gui {
    using widgets = InsertionSort<Typelist<W...>, type_cmp>;
    static constexpr auto n_unique_widgets = count_unique<widgets>;
    using pool_type = std::array<id_type, sizeof...(W)>;
    using registry_type = std::array<std::vector<Widget>, n_unique_widgets>;

    consteval registry_type generate_static_registry(W&&...Args) {
      registry_type res;
      return res;
    }

    consteval static_gui(W&& ...Args) : widget_types(create_iota_array<id_type, sizeof...(W)>()),
      registry(generate_static_registry(std::forward<W>(Args)...)) {}

    pool_type widget_types{}; 
    registry_type registry{};
    uint32_t count{};
  };

}
