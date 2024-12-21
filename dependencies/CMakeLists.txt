include(FetchContent)

FetchContent_Declare(sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 7f1162dfea4969bc17417563ac55d93b72e84c1e # 3.0
)

add_subdirectory(sfml)

message(STATUS "Fetching ImGui...")
FetchContent_Declare(imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui"
        GIT_TAG 993fa347495860ed44b83574254ef2a317d0c14f # 1.91.6
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(imgui-sfml
        GIT_REPOSITORY "https://github.com/SFML/imgui-sfml"
        GIT_TAG 4fec0d0f35f10f58b327cf5b4d12852ed1a77fbb # master
)

add_subdirectory(imgui-sfml)
