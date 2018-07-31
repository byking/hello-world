#CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

project(minimum_depth_of_binary_tree)

add_definitions(
  -std=gnu++11 -g -pipe -W -Wall -fPIC 	
)

set(minimum_depth_of_binary_tree_SOURCES
  ${PROJECT_SOURCE_DIR}/main.cpp
)

include_directories(
  /usr/local/include/
)

add_executable(minimum_depth_of_binary_tree
  ${minimum_depth_of_binary_tree_SOURCES}	
)

target_link_libraries(minimum_depth_of_binary_tree /usr/local/lib/libgflags.a)
