cmake_minimum_required(VERSION 3.16)
project(aucho)

set(CMAKE_CXX_STANDARD 20)

set(PROFILES_DIR "${CMAKE_SOURCE_DIR}/scripts/build/profiles")

execute_process(COMMAND
                echo "conan install . -if ${CMAKE_BINARY_DIR} -pr ${PROFILES_DIR}/clang -pr ${PROFILES_DIR}/${CMAKE_BUILD_TYPE} -pr ${PROFILES_DIR}/linux --build=missing")

#execute_process(COMMAND
#                conan install . -if ${CMAKE_BINARY_DIR} -pr ${PROFILES_DIR}/clang -pr ${PROFILES_DIR}/${CMAKE_BUILD_TYPE} -pr ${PROFILES_DIR}/linux --build=missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(aucho main.cpp)