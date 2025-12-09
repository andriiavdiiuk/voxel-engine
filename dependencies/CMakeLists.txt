add_subdirectory(GLFW)
add_subdirectory(glm)
add_subdirectory(spdlog)
add_subdirectory(glaze)
add_subdirectory(googletest)

add_library(glad STATIC "glad/glad.c")
target_include_directories(glad PUBLIC "glad")

add_library(stb_image STATIC "${CMAKE_SOURCE_DIR}/Dependencies/stb/stb_image.cpp")
target_include_directories(stb_image PUBLIC "stb")
