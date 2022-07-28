//
//  LTCDecoder.cpp
//  libltc_cpp
//
//  Created by Max Walley on 23/07/2022.
//

#include "LTCDecoder.hpp"

LTCDecoder::LTCDecoder()
{
    assert(sizeof(float) == numFloatBits / 8);
}

bool LTCDecoder::decode(const float* audio, uint64_t numSamples)
{
    if(numSamples > std::numeric_limits<uint64_t>::max() / 8)
    {
        assert(false);
        std::cout << "Too many samples per frame" << std::endl;
        return false;
    }
    
    //Look for the last sync word in the audio data
    const uint64_t numBitsThisFrame = numSamples * numFloatBits;
    
    std::bitset<syncWordSize> comparisonBuffer;
    
    for(uint64_t startCompBit = numBitsThisFrame - syncWordSize; startCompBit < numBitsThisFrame; --startCompBit)
    {
        //Load the bits into the comp bitset
        uint64_t currentSample = std::floor(startCompBit / float(numFloatBits));
        uint8_t currentOffset = startCompBit % numFloatBits;
        
        for(uint8_t currentBit = 0; currentBit < syncWordSize; ++currentBit)
        {
            //Get the bit value at the current offset position
            float sample = audio[currentSample];
            uint32_t* convertedSample = reinterpret_cast<uint32_t*>(&sample);
            uint64_t revOffset = (numFloatBits - 1) - currentOffset;
            bool bitVal = (*convertedSample & (1 << revOffset)) >> revOffset;
            
            comparisonBuffer[currentBit] = bitVal;
            
            if(++currentOffset >= numFloatBits)
            {
                ++currentSample;
                currentOffset = 0;
            }
        }
        
        if(comparisonBuffer == syncWord)
        {
            return true;
        }
    }
    
    //If that doesnt work look for a sync word in the overlap between the overlap buffer and the audio buffer
    
    return false;
}
