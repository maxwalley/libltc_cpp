//
//  LTCDecoder.hpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#pragma once

#include "LTCFrame.hpp"
#include <cmath>

class LTCDecoder
{
public:
    LTCDecoder();
    
    LTCFrame decode(const float* audio, uint64_t numSamples);
    
private:
    
    //This buffer is used to hold frame data that is moved in between audio buffers
    std::bitset<80> overlapBuffer;
    
    const std::bitset<16> syncWord = 0x3FFD;
};
