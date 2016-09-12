#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.6)
#Name your project here
project(my_music_day)

#Sends the -std=c99 flag to the gcc compiler
add_definitions(-std=c++11 -stdlib=libc++)
#This tells CMake to fib.c and name it fibonacci
add_executable(my_music_day my_music_day.cpp)

file(COPY music_day_files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
