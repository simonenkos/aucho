cmake_minimum_required(VERSION 3.16)
project(aucho CXX)

set(CMAKE_CXX_STANDARD 20)

set(PROFILES_DIR "${CMAKE_SOURCE_DIR}/scripts/build/profiles")

string(TOLOWER "${CMAKE_BUILD_TYPE}"      BUILD_TYPE)
string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMPILER_ID)
string(TOLOWER "${CMAKE_SYSTEM_NAME}"     SYSTEM_NAME)

message("BUILD_TYPE:  ${BUILD_TYPE}")
message("COMPILER_ID: ${COMPILER_ID}")
message("SYSTEM_NAME: ${SYSTEM_NAME}")

include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    check_cxx_compiler_flag("-std=c++20"      SUPPORT_CPP20)
    check_cxx_compiler_flag("-fcoroutines-ts" SUPPORT_COROUTINES)
    check_include_file_cxx("experimental/coroutine" HAS_COROUTINES_HEADER "-std=c++20")
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    check_cxx_compiler_flag("-std=gnu++20" SUPPORT_CPP20)
    check_cxx_compiler_flag("-fcoroutines" SUPPORT_COROUTINES)
    check_include_file_cxx("coroutine" HAS_COROUTINES_HEADER "-std=gnu++20 -fcoroutines")
elseif(CMAKE_CXX_COMPILER_ID MATCHED MSVS)
    check_cxx_compiler_flag("/std:c++20" SUPPORT_CPP20)
    check_cxx_compiler_flag("/await"     SUPPORT_COROUTINES)
    check_include_file_cxx("coroutine" HAS_COROUTINES_HEADER "/std:c++20")
endif()

if(NOT SUPPORT_CPP20)
    message(FATAL_ERROR "C++20 is not supported by compiler")
elseif(NOT SUPPORT_COROUTINES OR NOT HAS_COROUTINES_HEADER)
    message(FATAL_ERROR "Coroutines are not supported by compiler")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
endif()

find_program(CONAN_CMD conan REQUIRED)
message("CONAN_CMD is ${CONAN_CMD}")

execute_process(COMMAND
                ${CONAN_CMD} install ${CMAKE_SOURCE_DIR} -if ${CMAKE_BINARY_DIR} -pr ${PROFILES_DIR}/${COMPILER_ID} -pr ${PROFILES_DIR}/${BUILD_TYPE} -pr ${PROFILES_DIR}/${SYSTEM_NAME} --build=missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(aucho src/main.cpp) #src/aucho/account.h src/aucho/account_manager.h src/aucho/server.h src/aucho/server.cpp
target_link_libraries(aucho ${Boost_LIBRARIES} Threads::Threads)