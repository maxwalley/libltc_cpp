//
//  LTCFrame.hpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#pragma once

#include <array>
#include <bitset>

namespace LTC
{

struct Frame
{
    std::array<std::bitset<4>, 8> userBits;
    
    uint8_t frameNumber;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    
    bool dropFrameFlag;
    bool colourFrameFlag;
};
}
