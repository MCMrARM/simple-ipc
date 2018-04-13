cmake_minimum_required (VERSION 2.6)

project(simpleipc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

add_library(simpleipc include/simpleipc/common/connection.h include/simpleipc/common/io_handler.h include/simpleipc/server/service.h include/simpleipc/server/service_impl.h include/simpleipc/client/service_client.h include/simpleipc/client/service_client_impl.h src/common/connection_internal.h src/unix/common/unix_connection.cpp src/unix/common/unix_connection.h src/unix/server/unix_service_impl.cpp src/unix/server/unix_service_impl.h src/unix/client/unix_service_client.cpp src/unix/client/unix_service_client.h src/unix/epoll_io_handler.cpp src/unix/epoll_io_handler.h)
target_include_directories(simpleipc PUBLIC include/)
target_link_libraries(simpleipc Threads::Threads nlohmann_json)