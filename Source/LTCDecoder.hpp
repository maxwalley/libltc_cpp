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
#include <deque>
#include "BiphaseMarkCodeDecoder.hpp"

namespace LTC
{

class Decoder
{
public:
    Decoder(double sampleRate, uint8_t frameRate, int numFramesToStore = 10);
    
    //Returns how many frames it found
    template<typename SampleType>
    uint decode(const SampleType* audio, uint64_t numSamples)
    {
        uint numFoundFrames = 0;
        
        std::for_each(audio, audio + numSamples, [this, &numFoundFrames](SampleType sample)
        {
            if(const auto bit = biphaseDecoder.decode(sample); bit)
            {
                mostRecentBits <<= 1;
                mostRecentBits[0] = *bit;
            }
            
            bool success = true;
            for(uint8_t bitNumber = 64; bitNumber < 80; ++bitNumber)
            {
                bool syncValue = true;
                
                if(bitNumber == 64 || bitNumber == 65 || bitNumber == 78)
                {
                    syncValue = false;
                }
                
                if(mostRecentBits[79 - bitNumber] != syncValue)
                {
                    success = false;
                    break;
                }
            }
            
            if(success)
            {
                ++numFoundFrames;
                mostRecentFrames.pop_front();
                mostRecentFrames.push_back(createFrameFromCurrentBits());
                mostRecentBits.reset();
            }
        });
        
        return numFoundFrames;
    }
    
    const std::deque<Frame>& getLastFrames() const
    {
        return mostRecentFrames;
    }
    
private:
    Frame createFrameFromCurrentBits() const;
    uint8_t decodeBCD(uint8_t startBitIndex, uint8_t numBitsToRead, bool tens = false) const;
    
    static constexpr uint8_t syncWordSize = 16;
    static constexpr std::bitset<syncWordSize> syncWord = 0x3FFD;
    
    BiphaseMarkCodeDecoder biphaseDecoder;
    
    std::bitset<80> mostRecentBits;
    
    std::deque<Frame> mostRecentFrames;
};

}
