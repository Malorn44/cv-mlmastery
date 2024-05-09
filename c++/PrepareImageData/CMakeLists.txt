cmake_minimum_required(VERSION 2.8)
project( PrepareData )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( PrepareData PrepareData.cpp )
target_link_libraries( PrepareData ${OpenCV_LIBS} )
 