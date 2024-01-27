cmake_minimum_required(VERSION 3.27)
project(SFML_Clion_Template)

set(CMAKE_CXX_STANDARD 11)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add ImGui and ImGui-SFML modules
file(GLOB IMGUI_SOURCES "${CMAKE_SOURCE_DIR}/imgui/*.cpp")
include_directories("${CMAKE_SOURCE_DIR}/imgui")

# Add SFML modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif ()

add_executable(SFML_Clion_Template main.cpp ${IMGUI_SOURCES})
# add_executable(SFML_Clion_Template ${SOURCE_FILES})

if(SFML_FOUND AND OPENGL_FOUND)
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${OPENGL_gl_LIBRARY})
endif ()