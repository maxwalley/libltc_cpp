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
#include <type_traits>

class LTCDecoder
{
public:
    LTCDecoder();
    
    template<typename SampleType>
    bool decode(const SampleType* audio, uint64_t numSamples)
    {
        if(numSamples > std::numeric_limits<uint64_t>::max() / 8)
        {
            assert(false);
            std::cout << "Too many samples per frame" << std::endl;
            return false;
        }
        
        //Number of converted bits in the frame
        const uint64_t numBitsThisFrame = numSamples * 8;

        std::bitset<syncWordSize> comparisonBuffer;
        
        //Reverse iterate through all the converted bits
        for(uint64_t startCompBit = numBitsThisFrame - syncWordSize; startCompBit < numBitsThisFrame; --startCompBit)
        {
            //Load the bits into the comp bitset
            uint64_t currentSampleIndex = std::floor(startCompBit / 8);
            uint8_t currentBitOffset = startCompBit % 8;
            
            //Get the converted sample to use
            uint8_t currentSample = convertSample(audio[currentSampleIndex]);
            
            for(uint8_t currentBit = 0; currentBit < syncWordSize; ++currentBit)
            {
                //Get the bit value at the current offset position
                uint8_t revOffset = 7 - currentBitOffset;
                bool bitVal = (currentSample & (1 << revOffset)) >> revOffset;
                
                comparisonBuffer[currentBit] = bitVal;
                
                if(++currentBitOffset >= 8)
                {
                    ++currentSampleIndex;
                    currentSample = convertSample(audio[currentSampleIndex]);
                    currentBitOffset = 0;
                }
                
                //std::cout << (bitVal ? "1" : "0") << std::endl;
            }
            
            std::cout << comparisonBuffer << std::endl;
            
            if(comparisonBuffer == syncWord)
            {
                return true;
            }
        }
        
        //If that doesnt work look for a sync word in the overlap between the overlap buffer and the audio buffer
        
        return false;
    }
    
    void test() const;
    
private:
    
    template<typename SampleType>
    uint8_t convertSample(SampleType sample) const
    {
        if constexpr (std::is_floating_point_v<SampleType>)
        {
            //Map from -1 to 1 to the uint8 limits
            return 0 + ((std::numeric_limits<uint8_t>::max() - 0) * (sample - -1.0)) / (1.0 - -1.0);
        }
        else if constexpr (std::is_same_v<uint8_t, SampleType>)
        {
            return sample;
        }
        else if constexpr (std::is_integral_v<SampleType>)
        {
            //Map from the limits of that sample type to the limits of uint8
            return 0 + ((std::numeric_limits<uint8_t>::max() - 0) * (sample - std::numeric_limits<SampleType>::min())) / (std::numeric_limits<SampleType>::max() - std::numeric_limits<SampleType>::min());
        }
    
        assert(false);
        return 0;
    }
    
    //This buffer is used to hold frame data that is moved in between audio buffers
    std::bitset<80> overlapBuffer;
    
    static constexpr uint8_t syncWordSize = 16;
    static constexpr std::bitset<syncWordSize> syncWord = 0x3FFD;
};
