cmake_minimum_required(VERSION 3.16)
project(Search_Engine)

set(CMAKE_CXX_STANDARD 14)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(Search_Engine main.cpp converter.h)

target_link_libraries(Search_Engine PRIVATE nlohmann_json::nlohmann_json)