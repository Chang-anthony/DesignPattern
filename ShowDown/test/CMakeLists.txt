cmake_minimum_required(VERSION 3.13)

set(GTest DesignPattern_Test)

set(Sources
    ExampleTests.cpp
)

add_executable(${GTest} ${Sources})

target_link_libraries(${GTest} PUBLIC
    gtest_main
    SimpleDesignPatternCs1H
)

include(GoogleTest)
gtest_discover_tests(${GTest})


add_test(
    NAME ${GTest}
    COMMAND ${GTest}
)

