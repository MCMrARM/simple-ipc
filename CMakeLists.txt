cmake_minimum_required (VERSION 2.6)

project(simpleipc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

add_library(simpleipc include/simpleipc/common/connection.h include/simpleipc/common/io_handler.h include/simpleipc/server/service.h include/simpleipc/server/service_impl.h src/unix/server/unix_service_impl.cpp src/unix/server/unix_service_impl.h src/unix/epoll_io_handler.cpp src/unix/epoll_io_handler.h)
target_include_directories(simpleipc PUBLIC include/)
target_link_libraries(simpleipc Threads::Threads nlohmann_json)