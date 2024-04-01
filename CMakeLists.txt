cmake_minimum_required(VERSION 3.25)

project(skylib-avr VERSION 1.0.0)

add_library(skylib-avr INTERFACE)

target_include_directories(skylib-avr INTERFACE include)
