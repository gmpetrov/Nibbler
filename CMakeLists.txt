cmake_minimum_required(VERSION 3.0.2)

project(Nibbler)

set(dev-warnings "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++11")
set(warnings "${CMAKE_CXX_FLAGS} -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${dev-warnings}")
set(EXECUTABLE_NAME nibbler)
set(SOURCE_FILES
  srcs/main.cpp
  srcs/Board.cpp
  srcs/GraphSwitch.cpp
)

include_directories(includes)

add_subdirectory(libraries/sfml)
add_subdirectory(libraries/ncurses)
add_subdirectory(libraries/sdl)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
