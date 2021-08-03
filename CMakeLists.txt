cmake_minimum_required(VERSION 3.19)
project("vec.std")

set(CMAKE_CXX_STANDARD 20)

include(smsdk_ext-cmake/smsdk_ext.cmake)

add_library(json INTERFACE)
target_link_libraries(json INTERFACE "${CMAKE_SOURCE_DIR}/3rdparty/json")

# Boost
# vcpkg install boost-asio
# vcpkg install boost-beast
# vcpkg install boost-smart-ptr
#add_subdirectory(${CMAKE_SOURCE_DIR}/extern/boost-cmake)
find_package(Boost REQUIRED date_time coroutine)
add_definitions(-DASIO_HAS_STD_COROUTINE -DASIO_HAS_CO_AWAIT)

add_subdirectory(smcppsdk)
add_subdirectory(src)