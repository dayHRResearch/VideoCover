cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(videocover)

find_package(OpenCV REQUIRED)       # find OpenCV
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(/usr/local/include/)
include_directories(/usr/local/include/opencv4/)
include_directories(/usr/local/include/opencv4/opencv2)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

add_executable(videocover source/run.cc)

target_link_libraries(videocover ${TORCH_LIBRARIES} ${OpenCV_LIBS}) 
set_property(TARGET videocover PROPERTY CXX_STANDARD 17)


 

