project(Engine)

# ===== Executable =====
set(ENGINE_HEADERS
    "include/Engine/Core/Application.hpp"
    "include/Engine/Core/Window.hpp"
    "include/Engine/Core/Logger.hpp"

    "include/Engine/Core/Graphics/Shaders/Shader.hpp"
    "include/Engine/Core/Graphics/Buffers/IndexBufferObject.hpp"
    "include/Engine/Core/Graphics/Buffers/VertexArrayObject.hpp"
    "include/Engine/Core/Graphics/Buffers/VertexBufferObject.hpp"
    "include/Engine/Core/Graphics/Textures/Texture.hpp"
    "include/Engine/Core/Graphics/Textures/Texture2D.hpp"
    "include/Engine/Core/Graphics/Textures/TextureArray.hpp"
    "include/Engine/Core/Graphics/Textures/TextureParameters.hpp"

    "include/Engine/Core/Objects/GameObject.hpp"
    "include/Engine/Core/Objects/Camera.hpp"
    "include/Engine/Core/Objects/CameraController.hpp"

    "include/Engine/Core/World/Chunk.hpp"
    "include/Engine/Core/World/VoxelStorage.hpp"
    "include/Engine/Core/World/Level.hpp"
    "include/Engine/Core/World/LevelGenerator.hpp"
    "include/Engine/Core/World/WorldDefinitions.hpp"
    "include/Engine/Core/World/ChunkController.hpp"

    "include/Engine/Core/Components/Transform.hpp"

    "include/Engine/Core/Input/Input.hpp"
    "include/Engine/Core/Input/Mouse.hpp"
    "include/Engine/Core/Input/MouseButton.hpp"
    "include/Engine/Core/Input/Keyboard.hpp"
    "include/Engine/Core/Input/Key.hpp"
    "include/Engine/Core/Input/KeyState.hpp"
    "include/Engine/Core/Input/KeyStateMap.hpp"
    "include/Engine/Core/Events/EventDispatcher.hpp"

    "include/Engine/Common//Bimap.hpp"
    "include/Engine/Common/BitArray.hpp"
    "include/Engine/Common/Noises/PerlinNoise.hpp"
    "include/Engine/Common/Noises/PerlinNoiseParams.hpp"

    "include/Engine/Core/Resources/AssetHandle.hpp"
    "include/Engine/Core/Resources/AssetStorage.hpp"
    "include/Engine/Core/Resources/AssetLoaders.hpp"
    "include/Engine/Core/Resources/DefaultAssets.hpp"
    "include/Engine/Core/Renderer/ChunkRenderer.hpp"
                    
    "include/Engine/Core/Graphics/Meshing/ChunkMesh.hpp"
                    
    "include/Engine/Core/UI/ImGui/ImGuiBase.hpp"
    "include/Engine/Core/UI/ImGui/ImGuiDebugLayer.hpp"

    "include/Engine/Utils/FileUtils.hpp"
)

set(ENGINE_SOURCES
    "src/Core/Application.cpp"
    "src/Core/Window.cpp"
    "src/Core/Logger.cpp"

    "src/Core/Graphics/Shaders/Shader.cpp"

    "src/Core/Graphics/Buffers/IndexBufferObject.cpp"
    "src/Core/Graphics/Buffers/VertexArrayObject.cpp"
    "src/Core/Graphics/Buffers/VertexBufferObject.cpp"

    "src/Core/Graphics/Textures/Texture.cpp"
    "src/Core/Graphics/Textures/Texture2D.cpp"
    "src/Core/Graphics/Textures/TextureArray.cpp"

    "src/Core/Objects/Camera.cpp"
    "src/Core/Objects/CameraController.cpp"

    "src/Core/World/Chunk.cpp"
    "src/Core/World/VoxelStorage.cpp"
    "src/Core/World/LevelGenerator.cpp"
    "src/Core/World/ChunkController.cpp"

    "src/Core/Input/Input.cpp"
    "src/Core/Input/Mouse.cpp"
    "src/Core/Input/Keyboard.cpp"

    "src/Common/BitArray.cpp"
    "src/Common/Noises/PerlinNoise.cpp"

    "src/Core/Resources/AssetLoaders.cpp"

    "src/Core/Renderer/ChunkRenderer.cpp"

    "src/Core/Graphics/Meshing/ChunkMesh.cpp"

    "src/Core/UI/ImGui/ImGuiBase.cpp"
    "src/Core/UI/ImGui/ImGuiDebugLayer.cpp"

    "src/Utils/FileUtils.cpp"
)

add_library(${PROJECT_NAME}
    ${ENGINE_HEADERS}
    ${ENGINE_SOURCES})
# ===== Output Properties =====
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

# ===== Disable console =====
if(WIN32)
    # set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
else()
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
endif()

# ==== Enable diagnostics for MSVC ====

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /diagnostics:caret")
endif()

# ===== Copy Assets =====
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/engine_assets"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/engine_assets"
)


# ===== Includes =====
target_include_directories(${PROJECT_NAME} PUBLIC
    "include"
    "${CMAKE_SOURCE_DIR}/Dependencies/glad"
    "${CMAKE_SOURCE_DIR}/Dependencies/glm"
    "${CMAKE_SOURCE_DIR}/Dependencies"
)

find_package(OpenGL REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC
    OpenGL::GL
    glfw
    glm::glm
    glad
    stb_image
    spdlog::spdlog
    glaze::glaze
    imgui
)

