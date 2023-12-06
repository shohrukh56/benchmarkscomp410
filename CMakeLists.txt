cmake_minimum_required(VERSION 3.26)
project(untitled2 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled2 simplebenchamark.c
        Built-InBenchmarking/main.cpp
        BenchmarkingInterprocessCommunicationPerformance.c)
