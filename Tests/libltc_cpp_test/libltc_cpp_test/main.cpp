//
//  main.cpp
//  libltc_cpp_test
//
//  Created by Max Walley on 13/07/2022.
//

#include <iostream>
#include "LTCDecoder.hpp"
#include "AudioFile.h"

int main(int argc, const char** argv)
{
    if(argc < 2)
    {
        std::cout << "Please provide a path to test audio file as an argument" << std::endl;
        return 1;
    }
    
    AudioFile<float> audioFile(argv[1]);
    
    const int numSamples = audioFile.getNumSamplesPerChannel();
    
    if(numSamples == 0)
    {
        std::cout << "Error opening audio file" << std::endl;
        return 1;
    }
    
    constexpr int bufferSize = 1024;
    std::array<float, bufferSize> buffer;
    
    LTCDecoder decoder(48000.0, 25);
    
    for(uint64_t startSample = 0; startSample + bufferSize < numSamples; startSample += bufferSize)
    {
        uint64_t endSample = startSample + bufferSize;
        
        std::copy(audioFile.samples[0].cbegin() + startSample, audioFile.samples[0].cbegin() + endSample, buffer.begin());
        
        if(uint numFrames = decoder.decode(buffer.data(), bufferSize); numFrames > 0)
        {
            const std::deque<LTCFrame>& frames = decoder.getLastFrames();
            
            std::for_each(frames.cbegin() + frames.size() - numFrames, frames.cend(), [](const LTCFrame& frame)
            {
                std::cout << frame.hours.count() << ":" << frame.minutes.count() << ":" << frame.seconds.count() << "." << (int)frame.frameNumber << std::endl;
            });
        }
    }
    
    /*float sampleRate = 48000.0;
    int frameRate = 25;
    int maxSamplesPerBit = std::ceil(sampleRate / (80 * frameRate));
    int minSamplesPerBit = std::floor(sampleRate / (80 * frameRate));
    
    bool currentPhase = false;
    uint64_t phaseLength = 0;
    uint64_t lastPhaseLength = 0;
    
    for(int sampleIndex = 0; sampleIndex < numSamples; ++sampleIndex)
    {
        const float currentSample = audioFile.samples[0][sampleIndex];
        const bool samplePhase = currentSample >= 0.0f;
        
        if(sampleIndex == 0)
        {
            currentPhase = samplePhase;
        }
        else
        {
            if(samplePhase != currentPhase)
            {
                if(phaseLength == maxSamplesPerBit || phaseLength == minSamplesPerBit)
                {
                    std::cout << "0";
                }
                else if(phaseLength + lastPhaseLength == maxSamplesPerBit || phaseLength + lastPhaseLength == minSamplesPerBit)
                {
                    std::cout << "1";
                    phaseLength = 0;
                }
                else
                {
                    //std::cout << "Bad" << std::endl;
                    //assert(false);
                }
                
                currentPhase = samplePhase;
                lastPhaseLength = phaseLength;
                phaseLength = 0;
            }
        }
        
        ++phaseLength;
    }*/
    
    return 0;
}
