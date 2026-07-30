cmake_minimum_required(VERSION 3.20)

project(async_twitch_bot VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Boost REQUIRED COMPONENTS system CONFIG)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

set(TARGET_NAME twitch_bot)

add_subdirectory(src)