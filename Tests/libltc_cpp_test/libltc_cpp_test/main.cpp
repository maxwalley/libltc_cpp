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
    
    LTCDecoder decoder;
    
    const int bufferSize = 1024;
    std::array<float, bufferSize> buffer;
    
    for(int currentSample = 0; currentSample < numSamples; currentSample += bufferSize)
    {
        const int lastSample = std::min(numSamples, currentSample + bufferSize);
        std::copy(audioFile.samples[0].begin() + currentSample, audioFile.samples[0].begin() + lastSample, buffer.begin());
        
        if(int numPadding = lastSample - numSamples; numPadding > 0)
        {
            std::fill(buffer.begin() + numPadding, buffer.end(), 0.0f);
        }
        
        if(decoder.decode(buffer.data(), buffer.size()))
        {
            std::cout << "Detected" << std::endl;
        }
    }
    
    return 0;
}
