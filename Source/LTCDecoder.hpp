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
#include "BiphaseMarkCodeDecoder.hpp"

class LTCDecoder
{
public:
    LTCDecoder(double sampleRate, uint8_t frameRate);
    
    template<typename SampleType>
    bool decode(const SampleType* audio, uint64_t numSamples)
    {
        bool wasSuccess = false;
        
        std::for_each(audio, audio + numSamples, [this, &wasSuccess](SampleType sample)
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
                wasSuccess = true;
            }
        });
        
        return wasSuccess;
    }
    
private:
    static constexpr uint8_t syncWordSize = 16;
    static constexpr std::bitset<syncWordSize> syncWord = 0x3FFD;
    
    BiphaseMarkCodeDecoder biphaseDecoder;
    
    std::bitset<80> mostRecentBits;
};
