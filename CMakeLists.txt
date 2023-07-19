cmake_minimum_required(VERSION 3.0)
project(libltc_cpp VERSION 0.2.0 LANGUAGES CXX)

option(BUILD_TESTS "Build tests" ON)

add_library(ltc_cpp SHARED
    src/LTCDecoder.cpp
    src/BiphaseMarkCodeDecoder.cpp

    include/LTCDecoder.hpp
    include/BiphaseMarkCodeDecoder.hpp
    include/LTCFrame.hpp
)

target_include_directories(ltc_cpp PUBLIC include)

set_target_properties(ltc_cpp PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()