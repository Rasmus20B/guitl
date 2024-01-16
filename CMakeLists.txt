cmake_minimum_required(VERSION 3.13)  
project(guitl)               
set(CMAKE_CXX_STANDARD 23)            
set(CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES 
  src/guitl.cc
  src/sparse_set.h
  src/type_list.h
  )

add_compile_options(
  -Wall
  -O3
  -pedantic
  )
add_subdirectory(test)
# Add executable target with source files listed in SOURCE_FILES variable
include(FetchContent)


add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} raylib)
