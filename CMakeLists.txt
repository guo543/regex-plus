cmake_minimum_required(VERSION 3.10)

project(regex-plus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(regexp src/main/main.cc)

target_include_directories(regexp PRIVATE ./)

target_sources(regexp PRIVATE src/parser/parser.cc)
target_sources(regexp PRIVATE src/parser/st-nodes.cc)