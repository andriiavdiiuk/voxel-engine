add_subdirectory(GLFW)
add_subdirectory(glm)
add_subdirectory(spdlog)
add_subdirectory(glaze)
add_subdirectory(googletest)

add_library(glad STATIC "glad/glad.c")
target_include_directories(glad PUBLIC "glad")

add_library(stb_image STATIC "${CMAKE_SOURCE_DIR}/Dependencies/stb/stb_image.cpp")
target_include_directories(stb_image PUBLIC "stb")

add_library(imgui STATIC
    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/backends/imgui_impl_glfw.cpp"
    "imgui/backends/imgui_impl_opengl3.cpp"
)

target_link_libraries(imgui PRIVATE glfw)

target_include_directories(imgui PUBLIC "imgui")