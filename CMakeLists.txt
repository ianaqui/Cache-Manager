cmake_minimum_required(VERSION 3.10)
project(milestone6)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCE_FILES
        milestone6.cpp
        self_balancing_tree.cpp
        tree_node.cpp
        hash_table.cpp
        hash_node.cpp
        doubly_linked_list.cpp
        dll_node.cpp
        cache_manager.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directory for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Copy JSON files individually to avoid wildcard issues
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/milestone6.json
        ${CMAKE_BINARY_DIR}/milestone6.json)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/milestone6_config.json
        ${CMAKE_BINARY_DIR}/milestone6_config.json)

# Enable JSON library (if it's using a vendored JSON library)
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    # Include the JSON library from the project
    include_directories(${CMAKE_SOURCE_DIR}/json)
endif()