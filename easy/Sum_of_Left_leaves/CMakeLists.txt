#CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

project(sum_of_left_leaves)

add_definitions(
  -std=gnu++11 -g -pipe -W -Wall -fPIC 	
)

set(sum_of_left_leaves_SOURCES
  ${PROJECT_SOURCE_DIR}/main.cpp
)

include_directories(
  /usr/local/include/
)

add_executable(sum_of_left_leaves
  ${sum_of_left_leaves_SOURCES}	
)

target_link_libraries(sum_of_left_leaves /usr/local/lib/libgflags.a)
