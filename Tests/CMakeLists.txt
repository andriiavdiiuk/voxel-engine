project (Tests)

add_executable (Tests 
    src/BitArrayTest.cpp
    src/VoxelStorageTest.cpp
)

target_link_libraries(Tests PRIVATE 
    Engine
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)
