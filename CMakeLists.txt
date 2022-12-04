cmake_minimum_required(VERSION 3.5)

################################################################################
# Functions
################################################################################
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


################################################################################
# Project
################################################################################
project(bread_factory VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -O0")
set(POSITION_INDEPENDENT_CODE ON)

# Prepare all files
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
HEADER_DIRECTORIES(PROJECT_HEADER_DIRS)


# Target executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_HEADER_DIRS})

# Simlib
find_library(SIMLIB_LIB simlib /usr/lib/ /usr/local/lib/)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SIMLIB_LIB})


################################################################################
# Petr Peringer's Examples
################################################################################
#list(APPEND EXAMPLES
#        ball ball2
#        bessel
#        ctest
#        heating
#        lorenz
#        model2 model2-timeout model3 model4 model5
#        multiexp
#        network
#        pbx
#        procesor
#        rc
#        rlc
#        test3D
#        wheel wheel2
#        )
#foreach (example IN LISTS EXAMPLES)
#    add_executable(${example} third_party/simlib/examples/${example}.cc)
#    target_include_directories(${example} PUBLIC ${PROJECT_HEADER_DIRS})
#    target_link_libraries(${example} PUBLIC /usr/local/lib/libsimlib.so)
#endforeach ()
