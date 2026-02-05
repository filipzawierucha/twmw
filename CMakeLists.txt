cmake_minimum_required(VERSION 4.0)
project(twmw)

file(GLOB LIB_SOURCES
    src/*.cpp
    src/*.h
    src/utils/*.cpp
    src/utils/*.h
    src/hooks/*.cpp
    src/hooks/*.h
)

add_executable(twmw WIN32 
  src/main.cpp 
  ${LIB_SOURCES}
)

# add_library(wsHook SHARED src/hooks/wsHook.cpp)
# set_target_properties(wsHook PROPERTIES
#     PREFIX ""
#     OUTPUT_NAME "wsHook"
# )

target_link_libraries(twmw PRIVATE dwmapi)