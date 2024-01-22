cmake_minimum_required(VERSION 3.20)
project(mk_eso)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wvla")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
endif()

add_executable(les1_1 les1/les1_1.c)
add_executable(les1_2 les1/les1_2.c)
add_executable(les1_3 les1/les1_3.c)

add_executable(les2_1 les2/les2_1/main.c les2/les2_1/math.c)
