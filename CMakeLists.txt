cmake_minimum_required(VERSION 3.15)
project(ChartStart_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChartStart_Server main.cpp include/Common.h include/Server.h Server.cpp include/Utils.h utils.cpp)