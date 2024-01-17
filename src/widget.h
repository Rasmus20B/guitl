#pragma once

#include <cstdint>
#include <iostream>

namespace guitl {

  struct Widget {};

  template<typename T>
  struct WidgetCRTP : public Widget {
    virtual void print() {
      std::cout << "base\n";
    }
  };

  struct Button : WidgetCRTP<Button> {
    consteval Button(const uint32_t x, const uint32_t y) : m_x(x), m_y(y) {}

    void print() override {
      std::cout << m_x << ", " << m_y << "\n";
    }
    uint32_t m_x;
    uint32_t m_y;
  };

  struct Textbox : WidgetCRTP<Button> {
    consteval Textbox(const uint32_t x, const uint32_t y, std::string_view text) : m_x(x), m_y(y), m_text(text) {}

    void print() override {
      std::cout << m_x << ", " << m_y << " :: " << m_text << "\n";
    }
    uint32_t m_x;
    uint32_t m_y;
    std::string_view m_text;
  };
}
