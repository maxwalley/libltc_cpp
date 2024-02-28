#Add google test and set it not to build googlemock
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
add_subdirectory(googletest)

add_executable(tests
    src/main.cpp
    src/DecoderTests.cpp

    include/TestState.h
)

target_include_directories(tests PUBLIC include)

target_link_libraries(tests
    gtest
)

include(googletest)
gtest_discover_tests(tests
    EXTRA_ARGS ${CMAKE_SOURCE_DIR}/test/test_files
)