cmake_minimum_required(VERSION 3.25)
project(opencv_slider_captcha_solver)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT>
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
    )
endif ()

find_package(OpenCV CONFIG REQUIRED)

set(OpenCV_STATIC ON)
set(OpenCV_CUDA OFF)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_library(opencv_slider_captcha_solver SHARED
        captcha.cpp
        captcha.h)

target_link_libraries(opencv_slider_captcha_solver ${OpenCV_LIBS})
