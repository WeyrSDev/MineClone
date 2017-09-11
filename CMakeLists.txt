cmake_minimum_required (VERSION 3.8)
project(MineClone)

include_directories(src)

set(CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE SRC src/*.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
        link_libraries(opengl32 glew32)
endif()
if (CMAKE_SYSTEM_NAME    MATCHES "Linux")
        link_libraries(GL GLEW)
endif()
link_libraries(sfml-system sfml-window sfml-graphics)


add_executable(MineClone ${SRC})
