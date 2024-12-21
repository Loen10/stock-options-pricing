cmake_minimum_required(VERSION 3.10)
project(stock-options-pricing)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(stock-options-pricing main.cpp black-scholes-merton.cpp)