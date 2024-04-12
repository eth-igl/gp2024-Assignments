cmake_minimum_required(VERSION 3.5...3.28)
include(FetchContent)
project(assignment4)

set(CMAKE_CXX_STANDARD 14)

FetchContent_Declare(
    libigl
    GIT_REPOSITORY https://github.com/libigl/libigl.git
    GIT_TAG v2.4.0
)
FetchContent_MakeAvailable(libigl)
igl_include(glfw)
igl_include(imgui)

add_library(viewer_proxy SHARED src/viewer/viewer_proxy.cpp)
target_link_libraries(viewer_proxy igl::core igl::imgui igl::glfw)

# Add your project files
FILE(GLOB SRCFILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRCFILES})
target_link_libraries(${PROJECT_NAME} igl::core igl::imgui igl::glfw viewer_proxy)
