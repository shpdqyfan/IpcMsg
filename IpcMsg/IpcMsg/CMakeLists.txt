cmake_minimum_required(VERSION 3.0)
project(ipcmsg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message(------------------------------------------------)
find_package(Boost
             1.57.0
             COMPONENTS
             REQUIRED)

message(project_name: ${PROJECT_NAME})
message(project_src_dir: ${PROJECT_SOURCE_DIR})
message(project_bin_dir: ${PROJECT_BINARY_DIR})

file(GLOB LIB_SRC src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${LIB_SRC})

# The "include" path here represents 
# "C:\Users\yqian1\6testcode\zzz_testing\IpcMsg\IpcMsg\include" in my computer
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PUBLIC "../include")

