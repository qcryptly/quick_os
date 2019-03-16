cmake_minimum_required(VERSION 3.13.0)
project(os)
set(OS_VERSION 0.0.0)
set(LOCAL_INCLUDE ${CMAKE_SOURCE_DIR}/include)
find_package (Threads)
if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

message(STATUS "LOCAL_INCLUDE=${LOCAL_INCLUDE}")
enable_testing()

file(GLOB SRCS ${CMAKE_SOURCE_DIR}/src/*.cxx)
message(STATUS "Found srcs: ${SRCS}")
foreach(srcpath ${SRCS})
  get_filename_component(srcname ${srcpath} NAME_WE)
  set(target run-${srcname})
  add_executable(${target} ${srcpath})
  target_compile_options(${target} PRIVATE -g -Wall -std=c++2a)
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
  target_compile_options(${target} PRIVATE -g -Wall -pthread -std=c++2a)
  target_link_libraries(${target} PUBLIC ${lgtestpath} ${CMAKE_THREAD_LIBS_INIT})
  target_include_directories(
    ${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)
  target_include_directories(
    ${target} SYSTEM
    PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/vendor/gtest/googletest/include>)
  add_test(${target} ${target})
  message(STATUS "Building unit test ${target}")
endforeach()
message(STATUS "My ${ARCH}")

add_subdirectory(efi-kern)
add_subdirectory(bios-kern)
