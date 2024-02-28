#include "gtest/gtest.h"
#include "TestState.h"

std::__fs::filesystem::path testFilesParentDirectory;

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    if(argc == 2)
    {
        testFilesParentDirectory = argv[1];
    }
    
    return RUN_ALL_TESTS();
};
