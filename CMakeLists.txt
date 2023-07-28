cmake_minimum_required(VERSION 3.10)

project(regex-plus)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_library(regex-plus)
add_executable(regex-dev src/main/main.cc)

target_link_libraries(regex-dev PUBLIC regex-plus)

# set(EXECUTABLE_OUTPUT_PATH ../bin)

target_include_directories(regex-plus PRIVATE ./)
target_include_directories(regex-dev PRIVATE ./)

target_sources(regex-plus PRIVATE src/parser/parser.cc)
target_sources(regex-plus PRIVATE src/parser/st-nodes.cc)
target_sources(regex-plus PRIVATE src/parser/st-generate-nfa.cc)
target_sources(regex-plus PRIVATE src/nfa/nfa.cc)
target_sources(regex-plus PRIVATE src/nfa/nfa-states.cc)
