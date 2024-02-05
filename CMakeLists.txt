cmake_minimum_required(VERSION 3.27)
project(SFML_Clion_Template)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add ImGui and ImGui-SFML modules
file(GLOB IMGUI_SOURCES "${CMAKE_SOURCE_DIR}/imgui/*.cpp")
include_directories("${CMAKE_SOURCE_DIR}/imgui")

# Add SFML modules
if(WIN32)
    set(SFML_DIR "C:/Users/tim16/tools/SFML-2.6.1/lib/cmake/SFML")
endif ()

find_package(SFML 2 REQUIRED system window graphics network audio)
add_executable(SFML_Clion_Template main.cpp ${IMGUI_SOURCES})
# add_executable(SFML_Clion_Template ${SOURCE_FILES})

if(WIN32)
    set(SFML_DLL_DIR "C:/Users/tim16/tools/SFML-2.6.1/bin")

    add_custom_command(TARGET SFML_Clion_Template POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_DLL_DIR}" $<TARGET_FILE_DIR:SFML_Clion_Template>)
endif ()

if(OPENGL_FOUND)
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${OPENGL_gl_LIBRARY})
endif ()
