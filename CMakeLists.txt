cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME synfilesharing)
set(SERVER_EXAMPLE serverExample)
set(CLIENT_EXAMPLE clientExample)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)


#----------------------------------
# Library
#----------------------------------
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/synfilesharing.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/implementations/server.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/implementations/client.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/builders/server_builder.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/builders/client_builder.cpp>
)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

#----------------------------------
# Dependency sdbus-c++
#----------------------------------
add_subdirectory(libs/sdbus-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/sdbus-cpp/include>
        $<INSTALL_INTERFACE:include>
)

#----------------------------------
# Example server
#----------------------------------
add_executable(${SERVER_EXAMPLE})
target_sources(${SERVER_EXAMPLE} PUBLIC examples/server.cpp)
target_include_directories(${SERVER_EXAMPLE} PUBLIC include libs/sdbus-cpp/include)
target_link_libraries(${SERVER_EXAMPLE}
        PUBLIC ${PROJECT_NAME} sdbus-c++
)

#----------------------------------
# Example client
#----------------------------------
add_executable(${CLIENT_EXAMPLE})
target_sources(${CLIENT_EXAMPLE} PUBLIC examples/client.cpp)
target_include_directories(${CLIENT_EXAMPLE} PUBLIC include libs/sdbus-cpp/include)
target_link_libraries(${CLIENT_EXAMPLE}
        PUBLIC ${PROJECT_NAME}
        PUBLIC sdbus-c++
)

#----------------------------------
# CPack
#----------------------------------
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
)
install(DIRECTORY include/synfilesharing
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT dev
)

install(EXPORT ${PROJECT_NAME}-targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        COMPONENT dev
)

set(CPACK_PACKAGE_VENDOR "synalice")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library for sharing files via DBus")
set(CPACK_PACKAGE_CONTACT "nikita.nikita.krasnov@gmail.com")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_COMPONENTS_ALL dev)

set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_RUNTIME_DEBUGINFO_PACKAGE ON)
set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "libsystemd-dev (>=236)")

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

include(CPack)
