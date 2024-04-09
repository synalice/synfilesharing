cmake_minimum_required(VERSION 3.27)
set(PROJECT_NAME synfilesharing)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

# Library
add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME}
        PUBLIC
        src/synfs.cpp
        src/implementations/server.cpp
        src/builders/server_builder.cpp
)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        include
)

# Dependency sdbus-c++
add_subdirectory(libs/sdbus-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC libs/sdbus-cpp/include)
target_link_libraries(${PROJECT_NAME} INTERFACE sdbus-c++)

# Example executable
set(PROJECT_EXAMPLE synfilesharingExample)
add_executable(${PROJECT_EXAMPLE})
target_sources(${PROJECT_EXAMPLE}
        PUBLIC
        examples/server.cpp
        src/synfs.cpp
        src/implementations/server.cpp
        src/builders/server_builder.cpp
)
target_include_directories(${PROJECT_EXAMPLE}
        PUBLIC
        include
        libs/sdbus-cpp/include
)
target_link_libraries(${PROJECT_EXAMPLE}
        PUBLIC
        ${PROJECT_NAME}
        INTERFACE
        sdbus-c++
)
