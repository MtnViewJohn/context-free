cmake_minimum_required(VERSION 3.5.1)

set(CF_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SOURCE_LIST main.cpp
		mainwindow.cpp
		cfdg_highlighter.cpp
                qtcanvas.cpp
                qtsystem.cpp
                settings_dialog.cpp)

set(INCLUDE_DIR ${CF_MAIN_DIR}/src-common
		${CF_MAIN_DIR}/src-agg
		${CF_MAIN_DIR}/src-unix
                ${CF_MAIN_DIR}/src-win/derivedl
                ${CF_MAIN_DIR}/src-common/agg-extras
                ${CF_MAIN_DIR}/objs)

set(OBJS ${CF_MAIN_DIR}/objs/abstractPngCanvas.o
                ${CF_MAIN_DIR}/objs/agg_bezier_arc.o
                ${CF_MAIN_DIR}/objs/aggCanvas.o
                ${CF_MAIN_DIR}/objs/agg_color_rgba.o
                ${CF_MAIN_DIR}/objs/agg_curves.o
                ${CF_MAIN_DIR}/objs/agg_trans_affine.o
                ${CF_MAIN_DIR}/objs/agg_vcgen_contour.o
                ${CF_MAIN_DIR}/objs/agg_vcgen_stroke.o
                ${CF_MAIN_DIR}/objs/astexpression.o
                ${CF_MAIN_DIR}/objs/ast.o
                ${CF_MAIN_DIR}/objs/astreplacement.o
                ${CF_MAIN_DIR}/objs/bounds.o
                ${CF_MAIN_DIR}/objs/builder.o
                ${CF_MAIN_DIR}/objs/cfdgimpl.o
                ${CF_MAIN_DIR}/objs/cfdg.o
                ${CF_MAIN_DIR}/objs/cfdg.tab.o
                ${CF_MAIN_DIR}/objs/CmdInfo.o
                ${CF_MAIN_DIR}/objs/commandLineSystem.o
                ${CF_MAIN_DIR}/objs/ffCanvasDummy.o
                ${CF_MAIN_DIR}/objs/HSBColor.o
                ${CF_MAIN_DIR}/objs/lex.yy.o
                ${CF_MAIN_DIR}/objs/mainsyms.o
                ${CF_MAIN_DIR}/objs/makeCFfilename.o
                ${CF_MAIN_DIR}/objs/pathIterator.o
                ${CF_MAIN_DIR}/objs/pngCanvas.o
                ${CF_MAIN_DIR}/objs/posixSystem.o
                ${CF_MAIN_DIR}/objs/posixTimer.o
                ${CF_MAIN_DIR}/objs/posixVersion.o
                ${CF_MAIN_DIR}/objs/primShape.o
                ${CF_MAIN_DIR}/objs/Rand64.o
                ${CF_MAIN_DIR}/objs/rendererAST.o
                ${CF_MAIN_DIR}/objs/renderimpl.o
                ${CF_MAIN_DIR}/objs/shape.o
                ${CF_MAIN_DIR}/objs/shapeSTL.o
                ${CF_MAIN_DIR}/objs/stacktype.o
                ${CF_MAIN_DIR}/objs/SVGCanvas.o
                ${CF_MAIN_DIR}/objs/tempfile.o
                ${CF_MAIN_DIR}/objs/tiledCanvas.o
                ${CF_MAIN_DIR}/objs/variation.o)

project(context-free)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(PNG)

SET_SOURCE_FILES_PROPERTIES(
  ${OBJS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

#set(ENV{QT_NO_DEBUG_OUTPUT} 1)

add_executable(context-free ${SOURCE_LIST} ${OBJS})
add_executable(dummy EXCLUDE_FROM_ALL mainwindow.ui settings_dialog.ui)

target_link_libraries(context-free Qt5::Widgets)
target_link_libraries(context-free ${PNG_LIBRARIES})
#target_link_libraries(context-free Qt5::Test)

include_directories(${INCLUDE_DIR})
