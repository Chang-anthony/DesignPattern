cmake_minimum_required(VERSION 3.13)

set(GTest DesignPattern_Test)

set(Sources
    ExampleTests.cpp
)

add_executable(${GTest} ${Sources})

target_link_libraries(${GTest} PUBLIC
    gtest_main
    SimpleDesignPatternCs2_2H
)

include(GoogleTest)
gtest_discover_tests(${GTest})

# Set the working directory for the test
set_target_properties(${GTest} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test"
)

# 在主程序之前添加一个自定义目标以运行测试
add_custom_target(RunTests
    COMMAND ${CMAKE_CTEST_COMMAND}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test
    COMMENT "Running tests before the main program"
)

# 添加依赖关系，确保在运行主程序之前运行测试
add_dependencies(${PROJECT_NAME} RunTests)


add_test(
    NAME ${GTest}
    COMMAND ${GTest}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test"
)



