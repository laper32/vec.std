cmake_minimum_required(VERSION 3.12)
project("vec.std")
set(CMAKE_CXX_STANDARD 20)
include(smsdk_ext-cmake/smsdk_ext.cmake)

add_library(json INTERFACE)
target_link_libraries(json INTERFACE "${CMAKE_SOURCE_DIR}/3rdparty/json")

add_subdirectory(smcppsdk)
add_subdirectory(src)