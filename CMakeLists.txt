cmake_minimum_required(VERSION 3.16)
project(GPS_converter)

set(CMAKE_CXX_STANDARD 17)

add_executable(GPS_converter main.cpp GpsData.h)