//
//  LTCDecoder.hpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#pragma once

#include "LTCFrame.hpp"
#include <cmath>
#include <iostream>

class LTCDecoder
{
public:
    LTCDecoder();
    
    bool decode(const float* audio, uint64_t numSamples);
    
private:
    
    //This buffer is used to hold frame data that is moved in between audio buffers
    std::bitset<80> overlapBuffer;
    
    static constexpr uint8_t syncWordSize = 16;
    static constexpr std::bitset<syncWordSize> syncWord = 0x3FFD;
    
    static constexpr uint8_t numFloatBits = 32;
};
