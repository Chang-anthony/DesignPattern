cmake_minimum_required(VERSION 3.13)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")


set(CMAKE_CXX_STANDARD 20)

set(GTest Test)

set(Sources 
ExampleTests.cpp
)

add_executable(${GTest} ${Sources})
if(GTEST_FOUND)
    target_link_libraries(${GTest} PRIVATE ${PROJECT_NAME}_LIB GTest::GTest GTest::Main)
else()
    target_link_libraries(${GTest} PRIVATE ${PROJECT_NAME}_LIB gtest_main)
endif()

add_test(
    NAME ${GTest}
    COMMAND ${GTest}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)


set(GTESTON ON)
# set(GTESTOFF OFF)
# 在主程序之前添加一个自定义目标以运行测试
if(GTESTON)
    # 檢測系統是否為 macOS
    if(APPLE OR UNIX)
        # add_custom_target(RunTests
        #     COMMAND ${CMAKE_COMMAND} -E echo "Build completed. Running execute_process..."
        #     COMMAND ${CMAKE_COMMAND} -E echo "Your additional commands here..."
        #     COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.sh
        #     # DEPENDS ${GTest}
        #     # COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/Run/DesignPattern_Test.exe
        # )

        # 在 macOS 上執行 bash 腳本
        # # 添加自定义目标，该目标依赖于构建完成后运行的自定义命令
        add_custom_command(
            TARGET ${GTest}
            POST_BUILD
            COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.sh
            COMMENT "Running run_tests"
        )
        # 定義一個自定義目標，用來執行你的自定義命令
        add_custom_target(RunTests DEPENDS ${GTest})
    endif()

    if(WIN32)
        add_custom_command(
            TARGET ${GTest}
            POST_BUILD
            COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.bat
            COMMENT "Running run_tests"
        )
        # # 添加自定义目标，该目标依赖于构建完成后运行的自定义命令
        # add_custom_target(RunTests
        #     COMMAND ${CMAKE_COMMAND} -E echo "Build completed. Running execute_process..."
        #     COMMAND ${CMAKE_COMMAND} -E echo "Your additional commands here..."
        #     COMMAND ${CMAKE_CURRENT_LIST_DIR}/run_tests.bat
        #     # DEPENDS ${GTest}
        #     # COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/Run/DesignPattern_Test.exe
        # )
        add_custom_target(RunTests DEPENDS ${GTest})
    endif()
endif()





