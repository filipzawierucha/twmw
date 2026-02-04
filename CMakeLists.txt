cmake_minimum_required(VERSION 4.0)
project(twmw)

file(GLOB LIB_SOURCES
    src/*.cpp
    src/*.h
    src/utils/*.cpp
    src/utils/*.h
)

add_executable(twmw WIN32 
    src/main.cpp 
    ${LIB_SOURCES}
)