cmake_minimum_required(VERSION 3.19)
project(GraphDrawing)

set(CMAKE_CXX_STANDARD 14)

add_executable(GraphDrawing main.cpp)

#add_library(ogdf STATIC ${CMAKE_SOURCE_DIR}/ogdf)

find_library(NAMES ogdf PATHS C:/Users/igorf/Documents/Projetos/GraphDrawing/ogdf/)
#set_target_properties(ogdf PROPERTIES LINKER_LANGUAGE C)