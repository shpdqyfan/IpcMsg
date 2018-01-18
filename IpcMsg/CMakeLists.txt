cmake_minimum_required(VERSION 3.0)
project(IpcMsgLibTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message(------------------------------------------------)
find_package(Boost
             1.57.0
             COMPONENTS
             REQUIRED)

message(project_name: ${PROJECT_NAME})
message(project_src_dir: ${PROJECT_SOURCE_DIR})
message(project_bin_dir: ${PROJECT_BINARY_DIR})

add_subdirectory(IpcMsg)

set(APP_SRC main.cpp)
add_executable(${PROJECT_NAME} ${APP_SRC})

target_link_libraries(${PROJECT_NAME} ipcmsg)

# The "include" path here represents 
# "C:\Users\yqian1\6testcode\zzz_testing\IpcMsg\include" in my computer
include_directories("include")

