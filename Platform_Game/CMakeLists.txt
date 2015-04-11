project(Platform_Game)
FIND_PACKAGE(Qt4 REQUIRED)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR})
set(HEADERS_DIR ${CMAKE_CURRENT_LIST_DIR})
set(RESOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/resources)

set(PROJECT_SOURCES)

set(PROJECT_HEADERS)


INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

add_subdirectory(gamelib)
add_subdirectory(src)

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES} )

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} allegro-5.0.9-monolith-md-debug.lib)
