cmake_minimum_required(VERSION 3.16)
project(Search_Engine)

set(CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
add_subdirectory(googletest)
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL
#        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(Search_Engine main.cpp CTPL/ctpl_stl.h include/converter.h include/inverted_index.h src/unit_test.cpp src/inverted_index.cpp src/search_server.cpp include/search_server.h src/converter.cpp)
#add_executable(Search_Engine main.cpp converter.h)

target_link_libraries(Search_Engine PRIVATE nlohmann_json::nlohmann_json gtest_main)
#target_link_libraries(Search_Engine PRIVATE nlohmann_json::nlohmann_json)
include(GoogleTest)
gtest_discover_tests(Search_Engine)
