cmake_minimum_required(VERSION 3.20)
project(mk_eso)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ASAN "enable asan/ubsan")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wvla")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og")
	if (ASAN)
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined")
	endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
endif()

add_executable(les1_1 les1/les1_1.c)
add_executable(les1_2 les1/les1_2.c)
add_executable(les1_3 les1/les1_3.c)

add_executable(les2_1 les2/les2_1/main.c les2/les2_1/math.c)
add_executable(les2_2 les2/les2_2.c)
add_executable(les2_3 les2/les2_3.c)

add_executable(les3_1 les3/les3_1.c)
add_executable(les3_2 les3/les3_2/main.c les3/les3_2/rectangle.c
les3/les3_2/input.c)

add_executable(les4_1 les4/les4_1.c)
add_executable(les4_2 les4/les4_2.c)
add_executable(les4_3 les4/les4_3.c)

add_executable(les5_1 les5/les5_1/main.c les5/les5_1/stack.c les5/les5_1/teststack.c)
