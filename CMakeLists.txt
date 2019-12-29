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

hunter_add_package(nlohmann_json)
hunter_add_package(Boost COMPONENTS system filesystem program_options)

find_package(nlohmann_json)
find_package(Boost CONFIG REQUIRED system filesystem program_options)

add_library(HistoryExtension STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/HistoryExtension.cpp)
add_library(ChangedFile STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/ChangedFile.cpp)
add_library(ExecutedCommand STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/ExecutedCommand.cpp)
add_library(VimSession STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Vim.cpp)
add_library(FilesLib STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/FilesLib.cpp)
add_library(OptionsLib STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/OptionsLib.cpp)
add_library(JsonSaver STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/JsonSaver.cpp)

add_executable(extension
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)

target_include_directories(HistoryExtension PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(ChangedFile PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(ExecutedCommand PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(VimSession PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(FilesLib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(OptionsLib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(JsonSaver PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(VimSession Boost::filesystem Boost::system)
target_link_libraries(ExecutedCommand Boost::filesystem Boost::system)
target_link_libraries(ChangedFile Boost::filesystem Boost::system)
target_link_libraries(JsonSaver Boost::filesystem Boost::system
nlohmann_json::nlohmann_json ChangedFile ExecutedCommand VimSession)
target_link_libraries(OptionsLib)
target_link_libraries(FilesLib Boost::filesystem Boost::system ChangedFile)
target_link_libraries(HistoryExtension FilesLib OptionsLib Boost::filesystem
Boost::system Boost::program_options JsonSaver ChangedFile ExecutedCommand
VimSession)
target_link_libraries(extension HistoryExtension)
