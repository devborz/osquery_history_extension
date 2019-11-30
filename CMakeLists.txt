cmake_minimum_required(VERSION 3.10.2:)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#option(BUILD_COVERAGE "Build coverage" OFF)

#set(
# HUNTER_CACHE_SERVERS
# "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
# CACHE STRING "Default cache server"
#)

#include("cmake/HunterGate.cmake")

#huntergate(
# URL "https://github.com/ruslo/hunter/archive/v0.23.34.tar.gz"
# SHA1 "70287b1ffa810ee4e952052a9adff9b4856d0d54"
#)

project(HistoryExtension)

#hunter_add_package(GTest)
#hunter_add_package(nlohmann_json)

#find_package(GTest CONFIG REQUIRED)
#find_package(nlohmann_json CONFIG REQUIRED)

add_library(HistoryExtension STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/HistoryExtension.cpp )

add_executable(extension
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)

target_include_directories(HistoryExtension PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
 )

target_link_libraries(extension HistoryExtension)
