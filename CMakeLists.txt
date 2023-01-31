cmake_minimum_required(VERSION 3.0.0)
project(callstack VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lstdc++ -Wall -O2 -Wpedantic")

file(GLOB_RECURSE callstack_SRC CONFIGURE_DEPENDS "./src/*.cpp")
file(GLOB_RECURSE callstack_HDR CONFIGURE_DEPENDS "./src/*.h")

set(callstack_INC "")
foreach(_headerFile ${callstack_HDR})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND callstack_INC ${_dir})
endforeach()
list(REMOVE_DUPLICATES callstack_INC)

include(CTest)
enable_testing()

add_executable(callstack ${callstack_SRC})
target_include_directories(callstack PRIVATE ${callstack_INC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
