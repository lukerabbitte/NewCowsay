cmake_minimum_required(VERSION 3.16)
project(NewCowsay)

set(CMAKE_CXX_STANDARD 17)

add_executable(NewCowsay newcow.c citation.c citation.h constants.h constants.c wildcow.c wildcow.h reading_cow.c reading_cow.h)
