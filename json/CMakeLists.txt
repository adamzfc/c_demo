cmake_minimum_required (VERSION 2.6)
project (leptjson_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    # https://github.com/msteinbeck/tinyspline/issues/21
    if (APPLE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
    endif()
endif()

add_library(leptjson leptjson.c)
add_executable(leptjson_test test.c)
target_link_libraries(leptjson_test leptjson)
