cmake_minimum_required(VERSION 3.10)
#********************************************
project(iMonitor)
#********************************************
include(cmake/common.cmake)
include(cmake/qt.cmake)
include(cmake/git.cmake)
include(cmake/hook.cmake)
#********************************************
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
#********************************************
add_subdirectory(src)
