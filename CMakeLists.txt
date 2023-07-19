cmake_minimum_required(VERSION 3.0)
project(libltc_cpp VERSION 0.2.0 LANGUAGES CXX)

add_library(ltc_cpp SHARED
    Source/LTCDecoder.cpp
    Source/BiphaseMarkCodeDecoder.cpp

    Source/LTCDecoder.hpp
    Source/BiphaseMarkCodeDecoder.hpp
    Source/LTCFrame.hpp
)

set_target_properties(ltc_cpp PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES
)