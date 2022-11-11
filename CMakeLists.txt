cmake_minimum_required(VERSION 3.5)

project(simulation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -pedantic")
set(POSITION_INDEPENDENT_CODE ON)
#add_compile_definitions(DEBUG_RELATIONS) # MAKROS

file(GLOB_RECURSE PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        )


# source: https://stackoverflow.com/a/57928919/14471542
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/simlib/*.h
            )
    SET(dir_list "")
    FOREACH (file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH ()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()
HEADER_DIRECTORIES(header_dirs)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${header_dirs})
