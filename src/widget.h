#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>
#include <variant>

namespace guitl {

  struct Widget {
    virtual ~Widget() = default;
  };


  struct button : Widget {
    consteval button() = default;
    consteval button(const uint32_t x, const uint32_t y) : m_x(x), m_y(y) {}

    void print()  {
      std::cout << m_x << ", " << m_y << "\n";
    }
    uint32_t m_x;
    uint32_t m_y;

  };

  template<typename T>
  struct WidgetCRTP : public Widget {
    virtual void print() {
      std::cout << "base\n";
    }
  };

  struct Button : WidgetCRTP<Button> {
    consteval Button() = default;
    consteval Button(const uint32_t x, const uint32_t y) : m_x(x), m_y(y) {}

    void print() override {
      std::cout << m_x << ", " << m_y << "\n";
    }
    uint32_t m_x;
    uint32_t m_y;
  };

  struct Textbox : WidgetCRTP<Textbox> {
    consteval Textbox() = default;
    consteval Textbox(const uint32_t x, const uint32_t y, std::string_view text) : m_x(x), m_y(y), m_text(text) {}

    void print() override {
      std::cout << m_x << ", " << m_y << " :: " << m_text << "\n";
    }
    uint32_t m_x;
    uint32_t m_y;
    std::string_view m_text;
  };

  template<typename T>
  struct type_code {
    static constexpr auto value = std::numeric_limits<int>::max();
  };

  template<int n>
  struct n_to_widget {
    using type = std::false_type;
  };

  template<>
  struct n_to_widget<0> {
    using type = Button;
  };
  
  template<>
  struct n_to_widget<1> {
    using type = Textbox;
  };

  template<>
  struct type_code<Button> {
    static constexpr auto value = 0;
  };

  template<>
  struct type_code<Textbox> {
    static constexpr auto value = 1;
  };

  enum WidgetType {
    ButtonT,
    TextboxT,
  };

}
