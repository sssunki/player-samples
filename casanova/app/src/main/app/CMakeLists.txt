cmake_minimum_required(VERSION 3.19.1)
add_library(my-sdk SHARED main.cpp)
target_link_libraries(my-sdk android log)