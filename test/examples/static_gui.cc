#include "../../src/guitl.h"

int main() {

  static constinit guitl::static_gui layout {
    guitl::Button(20, 40),
    guitl::Textbox(50, 90, "Hello"),
    guitl::Button(70, 40),
    guitl::Button(70, 40),
    guitl::Button(70, 40),
  };

  std::cout << "Number of different Widgets Types: " << layout.registry.size() << "\n";

  for(auto i: layout.registry) {
    std::cout << "Widget " << i.size() << "\n";
  }
}
