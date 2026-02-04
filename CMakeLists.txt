cmake_minimum_required(VERSION 4.0)
project(twmw)

file(GLOB LIB_SOURCES *.cpp *.h)

add_executable(twmw WIN32
    main.cpp
    ${LIB_SOURCES}
)