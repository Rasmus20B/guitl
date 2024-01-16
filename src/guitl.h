#pragma once

#include <numeric>
#include <array>
#include <memory>

#include "type_list.h"
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
    using pool_type = std::array<id_type, sizeof...(W)>;
    using registry_type = std::array<std::array<std::shared_ptr<Widget>, 64>, count_unique<InsertionSort<Typelist<W...>, type_cmp>>>;

    consteval auto counter(auto ...Args, int c) {
      return c + 1;
    }

    template<size_t c>
    consteval registry_type generate_static_registry(W&&...Args) {
      return {};
    }

    consteval static_gui(W&& ...Args) : widget_types(create_iota_array<id_type, sizeof...(W)>()),
      registry(generate_static_registry<sizeof...(W)>(std::forward<W>(Args)...)) {}

    pool_type widget_types{}; 
    registry_type registry{};
    uint32_t count{};
  };

}
