#CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

project(primer_plus_examples)

add_definitions(
  -std=gnu++11 -g -pipe -W -Wall -fPIC 	
)

set(primer_examples_SOURCES
  ${PROJECT_SOURCE_DIR}/main.cpp
)

include_directories(
  /usr/local/include/
)

add_executable(primer_examples
  ${primer_examples_SOURCES}	
)

target_link_libraries(primer_examples /usr/local/lib/libgflags.a)
