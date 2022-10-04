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
    if(argc != 3)
    {
        std::cout << "Please provide arguments in the format: AudioFile Framerate" << std::endl;
        return 1;
    }
    
    AudioFile<float> audioFile(argv[1]);
    
    const int numSamples = audioFile.getNumSamplesPerChannel();
    
    if(numSamples == 0)
    {
        std::cout << "Error opening audio file" << std::endl;
        return 1;
    }
    
    double frameRate;
    
    try
    {
        frameRate = std::stod(argv[2]);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: cannot read framerate argument, Please provide arguments in the format: AudioFile Framerate" << std::endl;
        return 2;
    }
    
    constexpr int bufferSize = 1024;
    std::array<float, bufferSize> buffer;
    
    LTC::Decoder decoder(audioFile.getSampleRate(), frameRate);
    
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
            });
        }
    }
    
    return 0;
}
