cmake_minimum_required (VERSION 2.6)

project(simpleipc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(simpleipc include/simpleipc/common/connection.h include/simpleipc/server/service.h include/simpleipc/server/service_impl.h src/unix/server/unix_service_impl.cpp src/unix/server/unix_service_impl.h)
target_include_directories(simpleipc PUBLIC include/)
target_link_libraries(simpleipc nlohmann_json)