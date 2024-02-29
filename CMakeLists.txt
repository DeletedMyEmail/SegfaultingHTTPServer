cmake_minimum_required(VERSION 3.26)
project(HTTPinC C)

set(CMAKE_C_STANDARD 17)
#set(CMAKE_C_COMPILER C:\\msys64\\ucrt64\\bin\\gcc.exe)

set(GCC_COVERAGE_COMPILE_FLAGS "-lwsock32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

# add all source files to executable
file(GLOB_RECURSE SRC_FILES src/*.c includes/*.h)

add_executable(HTTPinC ${SRC_FILES})

find_library(WSOCK32_LIBRARY NAMES wsock32)
target_link_libraries(HTTPinC ${WSOCK32_LIBRARY})
