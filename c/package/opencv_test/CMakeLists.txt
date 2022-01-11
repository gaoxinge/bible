cmake_minimum_required(VERSION 2.8)
project(DisplayImage)

add_subdirectory(external/opencv)
add_executable(main main.cpp)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect)
target_link_libraries(main PUBLIC ${OpenCV_LIBS})
file(GLOB OpenCV_INCLUDE_DIRS external/opencv/include external/opencv/modules/*/include)
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}" "${OpenCV_INCLUDE_DIRS}")
