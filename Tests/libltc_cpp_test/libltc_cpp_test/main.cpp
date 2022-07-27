//
//  main.cpp
//  libltc_cpp_test
//
//  Created by Max Walley on 13/07/2022.
//

#include <iostream>
#include "LTCDecoder.hpp"

int main(int argc, const char * argv[])
{
    LTCDecoder decoder;
    
    decoder.decode(nullptr, 1024);
    
    return 0;
}
