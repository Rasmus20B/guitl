
#pragma once
#include <cstdint>

namespace guitl {

  struct type_counter final {
    [[nodiscard]] static inline std::uint32_t next() noexcept {
      static std::uint32_t count{};
      return count++;
    }
  };

  template<typename KeyType, typename ValType>
  struct TypeMap final {
    
  };
}
