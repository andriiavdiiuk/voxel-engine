project (TestGame)

add_executable (${PROJECT_NAME} 
    "src/Game.cpp" 
    "src/Game.h"
    "src/GameApplication.hpp"
    "src/GameApplication.cpp"
)
# ===== Copy Assets =====
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    add_custom_command(TARGET ${PROJECT_NAME}  PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    )
   
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build")
    add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    )
endif()

target_link_libraries(${PROJECT_NAME}  PRIVATE Engine)