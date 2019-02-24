project(os)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-g -Wall -pthread -std=c++2a")
set(LOCAL_INCLUDE ${CMAKE_SOURCE_DIR}/include)
message(STATUS "LOCAL_INCLUDE=${LOCAL_INCLUDE}")
enable_testing()

file(GLOB SRCS ${CMAKE_SOURCE_DIR}/src/*.cxx)
message(STATUS "Found srcs: ${SRCS}")
foreach(srcpath ${SRCS})
  get_filename_component(srcname ${srcpath} NAME_WE)
  set(target run-${srcname})
  add_executable(${target} ${srcpath})
  target_include_directories(${target} SYSTEM
                             PUBLIC $<BUILD_INTERFACE:${LOCAL_INCLUDE}>)
endforeach()

set(lgtestpath ${CMAKE_SOURCE_DIR}/vendor/gtest/build/lib/libgtest.a)
file(GLOB TESTS ${CMAKE_SOURCE_DIR}/**/*spec.cxx)
message(STATUS "Found tests: ${TESTS}")

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
