#include "gtest/gtest.h"
#include "TestState.h"

//Test that a single valid frame decodes correctly
TEST(DecoderTests, DecodesValidSingleFrame)
{
    std::cout << testFilesDirectory << std::endl;

    ASSERT_EQ(4, 5);
}

//Test that a single frame of random bytes decodes incorectly and reports an error
TEST(DecoderTests, DecodesInvalidSingleFrame)
{

}

//Test that decoding a stream of multiple valid sequential frames performs correctly and reports no errors
TEST(DecoderTests, DecodesValidMultiFrame)
{

}

//Test that decoding a stream of multiple valid frames that are not in order reports a warning
TEST(DecoderTests, DecodesNonSequentialMultiFrame)
{
    
}

//Test that decoding works at multiple sample rates
TEST(DecoderTests, DecodesMultiSampleRate)
{

}

//Test that decoding a stream that is not at the specified sample rate reports an error
TEST(DecoderTests, DecodesWrongSampleRate)
{
    
}

//Test that decoding works at multiple frame rates
TEST(DecoderTests, DecodesMultiFrameRate)
{

}

//Test that decoding a stream that is not at the specified frame rate reports an error
TEST(DecoderTests, DecodesWrongFrameRate)
{
    
}

//Test that user bits are maintained through decoding
TEST(DecoderTests, DecodesUserBits)
{
    
}

//Test that reverse frames can be correctly decoded
TEST(DecoderTests, DecodesReverseFrames)
{
    
}

//Test that reverse frames not in order reports a warning
TEST(DecoderTests, DecodesReverseFramesNonSequential)
{
    
}
