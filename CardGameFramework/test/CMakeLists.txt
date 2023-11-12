cmake_minimum_required(VERSION 3.13)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_CXX_STANDARD 20)

set(GTest DesignPattern_Test)

set(Sources
    ExampleTests.cpp
)

add_executable(${GTest} ${Sources})

target_link_libraries(${GTest} PUBLIC
    gtest_main
    ShowDown
    Uno
    CardFrameWork
)

include(GoogleTest)
gtest_discover_tests(${GTest})

# Set the working directory for the test
set_target_properties(${GTest} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test"
)


# 添加依赖关系，确保在运行主程序之前运行测试
add_dependencies(${GTest} RunTests)


add_test(
    NAME ${GTest}
    COMMAND ${GTest}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)



