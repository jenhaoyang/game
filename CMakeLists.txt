#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(game)

# Set version information in a config.h file
set(game_VERSION_MAJOR 1)
set(game_VERSION_MINOR 0)
include_directories("include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Define sources and executable
set(EXECUTABLE_NAME "game")
set(game_PROJECT_SOURCES
    src/main.cpp
    src/State.cpp
    src/Entity.cpp
    src/EntityManager.cpp
    src/SFMLDebugDraw.cpp
    src/Collisions.cpp
)
set(game_PROJECT_HEADERS
    include/State.h
    include/Entity.h
    include/EntityManager.h
    include/SFMLDebugDraw.h
    include/Collisions.h
)
add_executable(${EXECUTABLE_NAME} ${game_PROJECT_SOURCES} ${game_PROJECT_HEADERS})
include_directories(/usr/include/Box2D)
target_link_libraries(${EXECUTABLE_NAME} /lib64/libBox2D.so.2.1.0)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${game_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${game_VERSION_MINOR}")
include(CPack)
