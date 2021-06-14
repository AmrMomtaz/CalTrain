cmake_minimum_required(VERSION 3.19)
project(CalTrain C)

set(CMAKE_C_STANDARD 99)

add_executable(CalTrain caltrain.h caltrain.c caltrain-runner.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")