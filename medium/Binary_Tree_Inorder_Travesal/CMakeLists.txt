#CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

project(inorder_traversal_tree)

add_definitions(
  -std=gnu++11 -g -pipe -W -Wall -fPIC 	
)

set(inorder_traversal_tree_SOURCES
  ${PROJECT_SOURCE_DIR}/main.cpp
)

include_directories(
  /usr/local/include/
)

add_executable(inorder_traversal_tree
  ${inorder_traversal_tree_SOURCES}	
)

target_link_libraries(inorder_traversal_tree /usr/local/lib/libgflags.a)
