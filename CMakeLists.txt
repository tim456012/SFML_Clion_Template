cmake_minimum_required(VERSION 3.27)
project(SFML_Clion_Template VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory(dependencies)

if (CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/WX /W3 /permissive-)
    add_compile_options(/MP)
endif ()

configure_file(public/ProjectConfig.h.in ProjectConfig.h)

add_executable(${PROJECT_NAME} private/main.cpp)
# add_executable(SFML_Clion_Template ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML SFML::System SFML::Window SFML::Graphics)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
            $<TARGET_FILE:SFML::Graphics>
            $<TARGET_FILE:SFML::Window>
            $<TARGET_FILE:SFML::System>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()