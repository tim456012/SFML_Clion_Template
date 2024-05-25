message(STATUS "Fetching SFML...")

# Disable when needed
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)

FetchContent_MakeAvailable(sfml)
