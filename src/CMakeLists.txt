# Add Library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)

# Compile Demo Using Library
add_executable(${PROJECT_NAME}-demo main.cpp)
target_link_libraries(${PROJECT_NAME}-demo ${PROJECT_NAME})