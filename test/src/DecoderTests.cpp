#include "gtest/gtest.h"
#include "TestState.h"

//Test that a single valid frame decodes correctly
TEST(DecoderTests, DecodesValidSingleFrame)
{
    const std::__fs::filesystem::path testDataDir = testFilesParentDirectory / "decoder/decodes_single_valid_frame";
    const std::__fs::filesystem::directory_entry keyFile(testDataDir / "key.csv");

    ASSERT_TRUE(keyFile.exists());

    int numTestFilesFound = 0;

    for(const std::__fs::filesystem::directory_entry& child_file : std::__fs::filesystem::directory_iterator{testDataDir})
    {
        if(child_file.path().extension() == ".pcm")
        {
            numTestFilesFound++;
        }
    }

    std::cout << "Found " << numTestFilesFound << " test files" << std::endl;

    ASSERT_GT(numTestFilesFound, 0);
    ASSERT_EQ(4, 5);
}

//Test that a single frame of random bytes decodes incorectly and reports an error
TEST(DecoderTests, DecodesInvalidSingleFrame)
{

}

//Test that decoding a stream of multiple valid sequential frames performs correctly
TEST(DecoderTests, DecodesValidMultiFrame)
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
