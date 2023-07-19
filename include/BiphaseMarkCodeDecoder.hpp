//
//  BiphaseMarkCodeDecoder.hpp
//  libltc_cpp
//
//  Created by Max Walley on 06/08/2022.
//

#pragma once

#include <cstdint>
#include <optional>
#include <cmath>
#include <iostream>
#include <cassert>

class BiphaseMarkCodeDecoder
{
public:
    BiphaseMarkCodeDecoder(double sampleRate, double frameRate);
    
    //Pass this a sample and if it detects a bit it will return it
    template<typename SampleType>
    std::optional<bool> decode(SampleType sample)
    {
        std::optional<bool> returnVal = std::nullopt;
        
        bool phase = getSamplePhase(sample);
        
        if(phase != currentPhase)
        {
            if(currentPhaseLength == minSamplesPerBit || currentPhaseLength == maxSamplesPerBit)
            {
                returnVal = false;
            }
            else if(currentPhaseLength + lastPhaseLength == minSamplesPerBit || currentPhaseLength + lastPhaseLength == maxSamplesPerBit)
            {
                returnVal = true;
                currentPhaseLength = 0;
            }
            
            lastPhaseLength = currentPhaseLength;
            currentPhaseLength = 0;
            currentPhase = phase;
        }
        
        ++currentPhaseLength;
        
        return returnVal;
    }
    
    void reset();
    
private:
    template<typename SampleType>
    bool getSamplePhase(SampleType sample)
    {
        if constexpr (std::is_floating_point_v<SampleType>)
        {
            return sample >= 0.0f;
        }
        else if constexpr (std::is_integral_v<SampleType>)
        {
            SampleType maxPossibleVal = std::numeric_limits<SampleType>::max();
            SampleType minPossibleVal = std::numeric_limits<SampleType>::min();
            
            //Return if the value is more than or same as the mid value of this type
            return sample >= (maxPossibleVal + minPossibleVal) / 2;
        }
        
        assert(false);
        return false;
    }
    
    bool currentPhase = false;
    uint64_t currentPhaseLength = 0;
    uint64_t lastPhaseLength = 0;
    
    const int minSamplesPerBit;
    const int maxSamplesPerBit;
};
