cmake_minimum_required(VERSION 3.13)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_CXX_STANDARD 20)

set(GTest DesignPattern_Test)

set(Sources
    ExampleTests.cpp
)

add_executable(${GTest} ${Sources})

target_link_libraries(${GTest} PUBLIC ${PROJECT_NAME}_LIB gtest_main)

# 指定生成的可执行文件路径
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Run)

include(GoogleTest)
gtest_discover_tests(${GTest})


add_test(
    NAME ${GTest}
    COMMAND ${GTest}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

set(GTESTON ON)
# set(GTESTOFF OFF)
# 在主程序之前添加一个自定义目标以运行测试
if(GTESTON)
    # # Set the working directory for the test
    # set_target_properties(${GTEST} PROPERTIES
    # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    # )
    # add_custom_target(RunTests
    # COMMAND ${CMAKE_CTEST_COMMAND} -V
    # WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    # COMMENT "Running tests before the main program"
    # )
    # # 添加依赖关系，确保在运行主程序之前运行测试
    # add_dependencies(${PROJECT_NAME} RunTests)

    # 添加自定义命令，该命令在构建完成后运行
    # add_custom_command(
    #     TARGET ${GTest}
    #     POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E echo "Build completed. Running execute_process..."
    #     COMMAND ${CMAKE_COMMAND} -E echo "Your additional commands here..."
    #     COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.bat
    # )


    # # 添加自定义目标，该目标依赖于构建完成后运行的自定义命令
    add_custom_target(RunTests
        COMMAND ${CMAKE_COMMAND} -E echo "Build completed. Running execute_process..."
        COMMAND ${CMAKE_COMMAND} -E echo "Your additional commands here..."
        COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.bat
        DEPENDS ${GTest}
        # COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/Run/DesignPattern_Test.exe
    )

    add_dependencies(${PROJECT_NAME} RunTests)

    # add_custom_target(run_all
    #     DEPENDS RunTests
    # )

    # 设置 "make RunTests" 命令用于运行自定义目标
    # add_custom_target(run_tests_all
    #     COMMAND ${CMAKE_MAKE_PROGRAM} RunTests
    #     COMMENT "Run all tests"
    # )

    # execute_process(
    # COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/Run/DesignPattern_Test.exe 
    #     RESULT_VARIABLE result
    #     OUTPUT_VARIABLE output
    # )
    # message("Result: ${result}")
    # message("Output: ${output}")

    # execute_process(
    #     COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.bat
    #     OUTPUT_VARIABLE output
    #     RESULT_VARIABLE result
    # )
    # message("Command output: ${output}")
    # message("Output from batch file: ${output}")
endif()





