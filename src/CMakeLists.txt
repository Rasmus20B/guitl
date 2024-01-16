
include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(guitl ${SOURCE_FILES})
target_link_libraries(guitl raylib)
