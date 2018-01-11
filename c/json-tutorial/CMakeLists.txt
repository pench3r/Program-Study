cmake_minimum_required (VERSION 2.6)
project (ljson_test C)

add_library(ljson ljson.c)
add_executable(ljson_1 test.c)
target_link_libraries(ljson_1 ljson)
