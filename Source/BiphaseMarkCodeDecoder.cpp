//
//  BiphaseMarkCodeDecoder.cpp
//  libltc_cpp
//
//  Created by Max Walley on 06/08/2022.
//

#include "BiphaseMarkCodeDecoder.hpp"

BiphaseMarkCodeDecoder::BiphaseMarkCodeDecoder(double sampleRate, uint8_t frameRate)  : minSamplesPerBit(std::floor(sampleRate / (frameRate * 80))), maxSamplesPerBit(std::ceil(sampleRate / (frameRate * 80)))
{
    
}

void BiphaseMarkCodeDecoder::reset()
{
    currentPhaseLength = 0;
    lastPhaseLength = 0;
    currentPhase = false;
}
