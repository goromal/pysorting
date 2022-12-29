cmake_minimum_required(VERSION 2.8.12)
project(pysorting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(pybind11 REQUIRED)
find_package(sorting REQUIRED)

pybind11_add_module(pysorting python_module.cpp)
target_link_libraries(pysorting INTERFACE sorting)
