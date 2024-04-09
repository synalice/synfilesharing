cmake_minimum_required(VERSION 3.27)
set(PROJECT_NAME synfilesharing)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

# Library
add_library(${PROJECT_NAME} SHARED
        include/synfilesharing/synfs.h
)
target_sources(${PROJECT_NAME} PUBLIC src/synfs.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Dependency sdbus-c++
add_subdirectory(libs/sdbus-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC libs/sdbus-cpp/include)
target_link_libraries(${PROJECT_NAME} INTERFACE sdbus-c++)

# Example executable
set(PROJECT_EXAMPLE syndbusExample)
add_executable(${PROJECT_EXAMPLE}
        include/synfilesharing/implementations/server.h
        include/synfilesharing/implementations/client.h
        include/synfilesharing/constants.h
        include/synfilesharing/builders/server_builder.h
        include/synfilesharing/builders/client_builder.h
        include/synfilesharing/interfaces/i_client.h
        include/synfilesharing/interfaces/i_server.h)
target_sources(${PROJECT_EXAMPLE} PUBLIC examples/main.cpp)
target_include_directories(${PROJECT_EXAMPLE} PUBLIC include)
target_link_libraries(${PROJECT_EXAMPLE} PUBLIC ${PROJECT_NAME})
