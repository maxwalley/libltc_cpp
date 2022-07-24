//
//  LTCDecoder.cpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#include "LTCDecoder.hpp"

LTCDecoder::LTCDecoder()
{
    
}

LTCFrame LTCDecoder::decode(const float* audio, uint64_t numSamples)
{
    const uint8_t numFloatBits = sizeof(float) * 8;
    
    //Look for the last sync word in the audio data
    const uint64_t numBitsThisFrame = numSamples * numFloatBits;
    
    std::bitset<16> comparisonBuffer;
    
    for(uint64_t startCompBit = numBitsThisFrame - 16; startCompBit >= 0; --startCompBit)
    {
        uint64_t startSample = std::floor(startCompBit / float(numFloatBits));
        uint64_t offset = startCompBit % numFloatBits;
    }
    
    //If that doesnt work look for a sync word in the overlap between the overlap buffer and the audio buffer
    
    return LTCFrame();
}
