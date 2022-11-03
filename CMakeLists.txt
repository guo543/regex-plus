cmake_minimum_required(VERSION 3.10)

project(regex-plus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_library(regp)
add_executable(regexp src/main/main.cc)

target_link_libraries(regexp PUBLIC regp)

# set(EXECUTABLE_OUTPUT_PATH ../bin)

target_include_directories(regp PRIVATE ./)
target_include_directories(regexp PRIVATE ./)

target_sources(regp PRIVATE src/parser/parser.cc)
target_sources(regp PRIVATE src/parser/st-nodes.cc)
target_sources(regp PRIVATE src/parser/st-generate-nfa.cc)
target_sources(regp PRIVATE src/nfa/nfa.cc)
target_sources(regp PRIVATE src/nfa/nfa-states.cc)