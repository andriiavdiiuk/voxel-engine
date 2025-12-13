project(GameEngine)

# ===== Executable =====
add_library(GameEngine
    
    src/Core/Application.hpp
    src/Core/Application.cpp

    src/Core/Window.cpp    
    src/Core/Window.hpp

    src/Core/Logger.cpp
    src/Core/Logger.hpp

    src/Core/Graphics/Shaders/Shader.cpp
    src/Core/Graphics/Shaders/Shader.hpp

    src/Core/Graphics/Buffers/IndexBufferObject.cpp
    src/Core/Graphics/Buffers/IndexBufferObject.hpp
    src/Core/Graphics/Buffers/VertexArrayObject.cpp
    src/Core/Graphics/Buffers/VertexArrayObject.hpp
    src/Core/Graphics/Buffers/VertexBufferObject.cpp
    src/Core/Graphics/Buffers/VertexBufferObject.hpp

    src/Core/Graphics/Textures/Texture.cpp
    src/Core/Graphics/Textures/Texture.hpp
    src/Core/Graphics/Textures/Texture2D.cpp
    src/Core/Graphics/Textures/Texture2D.hpp
    src/Core/Graphics/Textures/TextureArray.cpp
    src/Core/Graphics/Textures/TextureArray.hpp
    src/Core/Graphics/Textures/TextureParameters.hpp

    src/Core/Objects/GameObject.hpp
    src/Core/Objects/Camera.cpp
    src/Core/Objects/Camera.hpp
    src/Core/Objects/CameraController.hpp
    src/Core/Objects/CameraController.cpp


    src/Core/World/Chunk.cpp
    src/Core/World/Chunk.hpp
    src/Core/World/VoxelStorage.cpp
    src/Core/World/VoxelStorage.hpp
    src/Core/World/World.hpp
    src/Core/World/WorldGenerator.cpp
    src/Core/World/WorldGenerator.hpp
    src/Core/World/WorldDefinitions.hpp

    src/Core/Components/Transform.hpp

    src/Core/Input/Input.cpp
    src/Core/Input/Input.hpp
    
    src/Core/Input/Mouse.cpp
    src/Core/Input/Mouse.hpp
    src/Core/Input/MouseButton.hpp
    src/Core/Input/Keyboard.cpp
    src/Core/Input/Keyboard.hpp
    src/Core/Input/Key.hpp
    src/Core/Input/KeyState.hpp
    src/Core/Input/KeyStateMap.hpp

    src/Core/Events/EventDispatcher.hpp
    src/Common/Bimap.hpp
    src/Common/BitArray.hpp
    src/Common/BitArray.cpp
    src/Common/Noises/PerlinNoise.hpp
    src/Common/Noises/PerlinNoise.cpp

    src/Core/Resources/AssetHandle.hpp
    src/Core/Resources/AssetStorage.hpp
    src/Core/Resources/AssetLoaders.hpp
    src/Core/Resources/AssetLoaders.cpp
    src/Core/Resources/DefaultAssets.hpp

    src/Core/Renderer/ChunkRenderer.hpp
    src/Core/Renderer/ChunkRenderer.cpp

    src/Core/Graphics/Meshing/ChunkMesh.hpp
    src/Core/Graphics/Meshing/ChunkMesh.cpp 
    
    src/Core/UI/ImGui/ImGuiBase.cpp
    src/Core/UI/ImGui/ImGuiBase.hpp
    src/Core/UI/ImGui/ImGuiDebugLayer.hpp
    src/Core/UI/ImGui/ImguiDebugLayer.cpp
    
    src/Utils/FileUtils.hpp
    src/Utils/FileUtils.cpp)   
  
# ===== Output Properties =====
set_target_properties(GameEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

# ===== Disable console =====
if(WIN32)
    # set_target_properties(GameEngine PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
else()
    target_link_options(GameEngine PRIVATE -mwindows)
endif()

# ==== Enable diagnostics for MSVC ====

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /diagnostics:caret")
endif()

# ===== Copy Assets =====
set(GAMEENGINE_ASSETS_CURRENT_RELATIVE_PATH "assets")
set(GAMEENGINE_ASSETS_OUPUT_RELATIVE_PATH "engine/assets")
target_compile_definitions(GameEngine PUBLIC
    GAMEENGINE_ASSETS_RELATIVE_PATH=\"${GAMEENGINE_ASSETS_CURRENT_RELATIVE_PATH}\"
)
add_custom_command(TARGET GameEngine PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/${GAMEENGINE_ASSETS_CURRENT_RELATIVE_PATH}"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${GAMEENGINE_ASSETS_OUPUT_RELATIVE_PATH}"
)


# ===== Includes =====
target_include_directories(GameEngine PUBLIC
    "src"
    "${CMAKE_SOURCE_DIR}/Dependencies/glad"
    "${CMAKE_SOURCE_DIR}/Dependencies/glm"
    "${CMAKE_SOURCE_DIR}/Dependencies"
)

find_package(OpenGL REQUIRED)


target_link_libraries(GameEngine PUBLIC
    OpenGL::GL
    glfw
    glm::glm
    glad
    stb_image
    spdlog::spdlog
    glaze::glaze
    imgui
)

