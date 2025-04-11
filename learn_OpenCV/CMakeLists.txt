cmake_minimum_required(VERSION 3.10)
project(Learn_OpenCV)

set(CMAKE_CXX_STANDARD 17)

# CAMBIA ESTA RUTA por donde esté OpenCV instalado
set(OpenCV_DIR "C:/Program Files/opencv/build")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(app main.cpp)
target_link_libraries(app ${OpenCV_LIBS})
