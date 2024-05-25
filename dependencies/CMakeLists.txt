include(FetchContent)

FetchContent_Declare(sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
)

add_subdirectory(sfml)

message(STATUS "Fetching ImGui...")
FetchContent_Declare(imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui"
        GIT_TAG 6ccc561a2ab497ad4ae6ee1dbd3b992ffada35cb # 1.90.6
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(imgui-sfml
        GIT_REPOSITORY "https://github.com/SFML/imgui-sfml"
        GIT_TAG de565ac8f2b795dedc0307b60830cb006afd2ecd # 2.6
)

add_subdirectory(imgui-sfml)

add_subdirectory(glad)