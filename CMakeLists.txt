cmake_minimum_required(VERSION 3.8)

# ===== CMake Policies =====
#enable hot reload
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT 
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,
            $<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,
            $<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
    )

endif()

if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()


# ===== Global Settings =====
set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS OFF)
set(DGLM_BUILD_TESTS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /diagnostics:caret")
endif()

# ===== Output directories =====
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ==== Projects ====
add_subdirectory(Dependencies)
add_subdirectory(Engine)
add_subdirectory(Examples)

include(CTest)
enable_testing()
add_subdirectory(Tests)
