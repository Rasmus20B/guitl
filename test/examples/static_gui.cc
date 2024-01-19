#include "../../src/guitl.h"
#include "../../src/type_list/type_list.h"

#include <typeinfo>

template<typename T>
void print() {
  std::cout << std::source_location::current().function_name() << "\n";
}

int main() {

  std::tuple<std::array<int, 4>> hello{};

  std::cout << std::get<0>(hello)[0] << "\n";


  static constinit guitl::static_gui layout {
    guitl::Button(20, 40),
    guitl::Textbox(50, 90, "Hello"),
    guitl::Button(70, 40),
    guitl::Button(70, 40),
    guitl::Button(70, 40),
  };

  std::cout << "Number of different Widgets Types: " << layout.registry.size() << "\n";

  layout.print_all_types([](auto value) {return;});

  for(int i = 0; i < layout.registry.size(); ++i) {
    std::cout << "===========\n";
    std::cout << "This is the " << typeid(layout.registry[i][0]).name() << "\n";
    if(i == 0) {
      for(auto j: layout.registry[i]) {
        std::cout << "Found a button. \n" ;
      }
    } else if(i == 1) {
      for(auto j: layout.registry[i]) {
        std::cout << "Found a Textbox.\n";
      }
    } else {
      for(auto j: layout.registry[i]) {
        std::cout << "Found something or other.\n";
      }
    }
  }
}
