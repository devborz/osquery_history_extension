cmake_minimum_required(VERSION 3.10.2:)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
 HUNTER_CACHE_SERVERS
 "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
 CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

huntergate(
 URL "https://github.com/ruslo/hunter/archive/v0.23.34.tar.gz"
 SHA1 "70287b1ffa810ee4e952052a9adff9b4856d0d54"
)

project(HistoryExtension)

hunter_add_package(Boost COMPONENTS system filesystem program_options)
find_package(Boost CONFIG REQUIRED system filesystem program_options)



add_library(HistoryExtension STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/HistoryExtension.cpp)
add_library(files STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/files.cpp)
add_library(command STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/command.cpp)
add_library(period STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/period.cpp)

add_executable(extension
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)


target_include_directories(HistoryExtension PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(files PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(command PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(period PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(command Boost::filesystem Boost::system)
target_link_libraries(files period Boost::filesystem Boost::system)
target_link_libraries(HistoryExtension files period command
Boost::filesystem Boost::system Boost::program_options)
target_link_libraries(extension HistoryExtension)
