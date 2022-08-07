//
//  LTCDecoder.cpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#include "LTCDecoder.hpp"

LTCDecoder::LTCDecoder(double sampleRate, uint8_t frameRate)  : biphaseDecoder(sampleRate, frameRate)
{
}
