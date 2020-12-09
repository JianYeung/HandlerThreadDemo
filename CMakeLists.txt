cmake_minimum_required(VERSION 3.17)
project(HandlerThread)

set(CMAKE_CXX_STANDARD 11)

add_executable(HandlerThread main.cpp Looper.cpp Looper.h Handler.cpp Handler.h Message.cpp Message.h)