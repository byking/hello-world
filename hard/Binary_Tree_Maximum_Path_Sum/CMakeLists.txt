#CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

project(test_tree)

add_definitions(
  -std=gnu++11 -g -pipe -W -Wall -fPIC 	
)

set(test_tree_SOURCES
  ${PROJECT_SOURCE_DIR}/main.cpp
)

include_directories(
  /usr/local/include/
)

add_executable(test_tree
  ${test_tree_SOURCES}	
)

target_link_libraries(test_tree /usr/local/lib/libgflags.a)
