cmake_minimum_required(VERSION 3.0.2)

set(EXECUTABLE_NAME sdl)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++11")

set(SDL_INCLUDE_DIR /usr/local/Cellar/sdl2/2.0.3/include)
set(SDL_LIBRARY /usr/local/Cellar/sdl2/2.0.3/lib/libSDL2.dylib)

set(SOURCE_FILES srcs/SdlHandler.cpp)

find_package(SDL REQUIRED sdl2)

include_directories(includes)
add_library(${EXECUTABLE_NAME} MODULE ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${SDL_LIBRARY})