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
    
    LTC::Decoder decoder(44100.0, 29.97);
    
    for(uint64_t startSample = 0; startSample + bufferSize < numSamples; startSample += bufferSize)
    {
        uint64_t endSample = startSample + bufferSize;
        
        std::copy(audioFile.samples[0].cbegin() + startSample, audioFile.samples[0].cbegin() + endSample, buffer.begin());
        
        if(uint numFrames = decoder.decode(buffer.data(), bufferSize); numFrames > 0)
        {
            const std::deque<LTC::Frame>& frames = decoder.getLastFrames();
            
            std::for_each(frames.cbegin() + frames.size() - numFrames, frames.cend(), [](const LTC::Frame& frame)
            {
                std::cout << frame.hours.count() << ":" << frame.minutes.count() << ":" << frame.seconds.count() << "." << (int)frame.frameNumber << std::endl;
                
                std::cout << std::boolalpha << frame.isDropFrame << std::endl;
            });
        }
    }
    
    return 0;
}
