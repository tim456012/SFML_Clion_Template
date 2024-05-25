# Define glad as a library
message(STATUS "Configuring glad")
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC include ${GLAD_DIR}/include)