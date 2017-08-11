cmake_minimum_required(VERSION 3.0)

project(log)

# file(GLOB_RECURSE sources      src/main/*.cpp src/main/*.h)
# file(GLOB_RECURSE sources_test src/test/*.cpp)
# file(GLOB_RECURSE data resources/*)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src _src)
message(${PROJECT_NAME})
message(${_src})
add_executable(${PROJECT_NAME} ${_src})

set(CMAKE_CXX_COMPILE "gcc")
set(CMAKE_CXX_FLAGS "-std=c99")
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FALGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG ")
