#=============================================================================
# Copyright (C) 2013 Daniel Pfeifer <daniel@pfeifer-mail.de>
#
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#=============================================================================

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(CrossTest CXX)

enable_testing()

if(MSVC)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SCL_SECURE_NO_WARNINGS
    )
endif()

if(CMAKE_CROSSCOMPILING AND CMAKE_HOST_UNIX)
  set(Boost_INCLUDE_DIR "${CMAKE_BINARY_DIR}/boost_root")
  if(NOT EXISTS "${Boost_INCLUDE_DIR}/boost")
    file(MAKE_DIRECTORY "${Boost_INCLUDE_DIR}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
      "/usr/include/boost"
      "${Boost_INCLUDE_DIR}/boost"
      )
  endif()
endif()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(test_list
  replace
  to_upper
  )

create_test_sourcelist(test_sources
  main.cpp
  ${test_list}
  )

add_executable(test_driver ${test_sources})

if(WIN32 AND CMAKE_HOST_UNIX)
  target_link_libraries(test_driver
    -static-libgcc
    -static-libstdc++
    )
  find_program(test_launcher wine)
  if(NOT test_launcher)
    message(FATAL_ERROR "Wine is required to execure Windows tests on UNIX!")
  endif()
else()
  set(test_launcher)
endif()

foreach(test IN LISTS test_list)
  add_test(NAME ${test}
    COMMAND ${test_launcher} $<TARGET_FILE:test_driver> ${test}
    )
endforeach()
