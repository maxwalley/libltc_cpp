//
//  LTCFrame.hpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#pragma once

#include <array>
#include <bitset>
#include <chrono>

namespace LTC
{

struct Frame
{
    std::array<std::bitset<4>, 8> userBits;
    
    uint8_t frameNumber;
    std::chrono::seconds seconds;
    std::chrono::minutes minutes;
    std::chrono::hours hours;
    
    bool dropFrameFlag;
    bool colourFrameFlag;
};
}
