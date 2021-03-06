# Fetch Catch2 Dependency
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v3.0.0-preview3
)
FetchContent_MakeAvailable(Catch2)

# Compile Test Executable
add_executable(
    tests
    ListTest.h
    ListTest.cpp
    ArrayListTest.cpp
    LinkedListTest.cpp
    PriorityQueueTest.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE ${PROJECT_NAME})

# Register Tests
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)