project(uefi_boot)

cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-g -Wall -pthread -std=c++2a")
find_package(Threads REQUIRED)
enable_testing()

set(lgtestpath ${CMAKE_SOURCE_DIR}/vendor/gtest/build/lib/libgtest.a)
file(GLOB TESTS ${CMAKE_SOURCE_DIR}/**/*spec.cxx)
message(STATUS ${TESTS})
foreach(testpath ${TESTS})
  get_filename_component(testname ${testpath} NAME_WE)
  set(target ${testname}.spec)
  add_executable(${target} ${testpath})
  target_link_libraries(${target} ${lgtestpath})
  target_include_directories(
    ${target} SYSTEM
    INTERFACE ${CMAKE_SOURCE_DIR}/vendor/gtest/googletest/include)
  add_test(${target} ${target})
  message(STATUS "Building unit test ${target}")
endforeach()