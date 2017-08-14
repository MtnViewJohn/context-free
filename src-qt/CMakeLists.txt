cmake_minimum_required(VERSION 3.5.1)

set(CF_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SOURCE_LIST main.cpp
		mainwindow.cpp
		cfdg_highlighter.cpp
		qtcanvas.cpp
		qtsystem.cpp)

set(INCLUDE_DIR ${CF_MAIN_DIR}/src-common
		${CF_MAIN_DIR}/src-agg
		${CF_MAIN_DIR}/src-unix
		${CF_MAIN_DIR}/src-win/derived
		${CF_MAIN_DIR}/src-common/agg-extras)

file(GLOB OBJS ${CF_MAIN_DIR}/objs "*.o")

project(context-free)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(PNG)

add_executable(context-free ${SOURCE_LIST} ${OBJS})

target_link_libraries(context-free Qt5::Widgets)
target_link_libraries(context-free Qt5::Test)
target_link_libraries(context-free ${CMAKE_SOURCE_DIR}/cfdg.a)

include_directories(${INCLUDE_DIR})
