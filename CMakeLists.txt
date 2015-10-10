cmake_minimum_required(VERSION 3.0.2)

project(Nibbler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")
set(BIN_NAME nibbler)
set(SRCS
	srcs/main.cpp
	srcs/Board.cpp
	)

include_directories(includes)

#add_subdirectory(libs/sdl)
#add_subdirectory(libs/sfml)
#add_subdirectory(libs/ncurses)

add_executable(${BIN_NAME} ${SRCS})
target_link_libraries(${BIN_NAME} ${CMAKE_DL_LIBS})
