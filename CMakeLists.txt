cmake_minimum_required(VERSION 3.27)
set(PROJECT_NAME synfilesharing)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

# Library
add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME}
        PUBLIC
        src/synfilesharing.cpp
        src/implementations/server.cpp
        src/implementations/client.cpp
        src/builders/server_builder.cpp
        src/builders/client_builder.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Dependency sdbus-c++
add_subdirectory(libs/sdbus-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC libs/sdbus-cpp/include)
target_link_libraries(${PROJECT_NAME} INTERFACE sdbus-c++)

# Example server
set(SERVER_EXAMPLE serverExample)
add_executable(${SERVER_EXAMPLE})
target_sources(${SERVER_EXAMPLE} PUBLIC examples/server.cpp)
target_include_directories(${SERVER_EXAMPLE} PUBLIC include libs/sdbus-cpp/include)
target_link_libraries(${SERVER_EXAMPLE}
        PUBLIC ${PROJECT_NAME}
        INTERFACE sdbus-c++
)

# Example client
set(CLIENT_EXAMPLE clientExample)
add_executable(${CLIENT_EXAMPLE})
target_sources(${CLIENT_EXAMPLE} PUBLIC examples/client.cpp)
target_include_directories(${CLIENT_EXAMPLE} PUBLIC include libs/sdbus-cpp/include)
target_link_libraries(${CLIENT_EXAMPLE}
        PUBLIC ${PROJECT_NAME}
        INTERFACE sdbus-c++
)
