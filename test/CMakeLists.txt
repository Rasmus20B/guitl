include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(sparse_set_test data_structures/sparse_set.cc)
add_executable(type_list data_structures/typelist.cc)
add_executable(static_gui_example examples/static_gui.cc)
target_link_libraries(sparse_set_test GTest::gtest_main)
target_link_libraries(static_gui_example GTest::gtest_main)
target_link_libraries(type_list GTest::gtest_main)

include(GoogleTest)
