//
//  LTCDecoder.cpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#include "LTCDecoder.hpp"

namespace LTC
{

Decoder::Decoder(double sampleRate, double frameRate, int numFramesToStore)  : biphaseDecoder(sampleRate, frameRate)
{
    mostRecentFrames.resize(numFramesToStore);
}

Frame Decoder::createFrameFromCurrentBits() const
{
    Frame newFrame;
    
    newFrame.frameNumber = decodeBCD(0, 4) + decodeBCD(8, 2, true);
    newFrame.seconds = decodeBCD(16, 4) + decodeBCD(24, 3, true);
    newFrame.minutes = decodeBCD(32, 4) + decodeBCD(40, 3, true);
    newFrame.hours = decodeBCD(48, 4) + decodeBCD(56, 2, true);
    
    uint8_t userBitFieldStartBit = 4;
    std::for_each(newFrame.userBits.begin(), newFrame.userBits.end(), [&userBitFieldStartBit, this](auto& userBits)
    {
        for(uint8_t bitIndex = 0; bitIndex < 4; ++bitIndex)
        {
            userBits[bitIndex] = mostRecentBits[79 - (bitIndex + userBitFieldStartBit)];
        }
        
        userBitFieldStartBit += 8;
    });
    
    newFrame.dropFrameFlag = mostRecentBits[79 - 10];
    newFrame.colourFrameFlag = mostRecentBits[79 - 11];
    
    return newFrame;
}

uint8_t Decoder::decodeBCD(uint8_t startBitIndex, uint8_t numBitsToRead, bool tens) const
{
    assert(startBitIndex >= 0 && startBitIndex + numBitsToRead < mostRecentBits.size());
    
    uint8_t decodedVal = 0;
    
    //Get frame ones
    for(int bitIndex = startBitIndex; bitIndex < startBitIndex + numBitsToRead; ++bitIndex)
    {
        if(mostRecentBits[79 - bitIndex])
        {
            decodedVal += pow(2, bitIndex - startBitIndex);
        }
    }
    
    return tens ? decodedVal * 10 : decodedVal;
}

}
