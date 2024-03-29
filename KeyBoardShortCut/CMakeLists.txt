cmake_minimum_required(VERSION 3.12)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(KeyBoardShortCut)
set(CMAKE_CXX_STANDARD 20)

# ============ set

set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib)
set(UTILS_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/utils)

# ============

# ========================================================
# GTEST
find_package(GTEST REQUIRED)

if(NOT GTEST_FOUND)
    message(STATUS "Start Fetch Google Test.")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
        # DOWNLOAD_NO_EXTRACT TRUE
        # GIT_TAG        release-1.11.0
        DOWNLOAD_EXTRACT_TIMESTAMP ON
    )

    # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # set_property(TARGET gmock PROPERTY FOLDER "gtest")
    # set_property(TARGET gmock_main PROPERTY FOLDER "gtest")
    # set_property(TARGET gtest PROPERTY FOLDER "gtest")
    # set_property(TARGET gtest_main PROPERTY FOLDER "gtest")
endif()


# 確認是否已經包含 Google Test
# if(TARGET gtest)
#     message(STATUS "Google Test found!")
# else()
#     message(FATAL_ERROR "Failed to find Google Test!")
# endif()

# ======================================================


# ================= main
include(${LIB_PATH}/libary.cmake)

set(SRCS)
set(INCS)
list(APPEND SRCS ${LIB_SRCS})
list(APPEND INCS ${LIB_INCS})

# set(${PROJECT_NAME}_SRCS ${SRCS})
# set(${PROJECT_NAME}_INCS ${INCS})


include(${UTILS_PATH}/utils.cmake)
set(COMM_INCS ${UTILS_INCS})
set(COMM_SRCS)
# ==================



add_library(${PROJECT_NAME}_LIB STATIC
    ${SRCS}
    ${COMM_SRCS}
)


# 指定項目的執行檔名稱和源檔
# 將所有源檔案放入變數中
set(SOURCES
    main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

#============ include directories setting ========

# include_directories(${PROJECT_NAME} PUBLIC ${INCS} ${COMM_INCS})
#=================================================

### 使用 target_include_directories 容易找不到 hpp 用 include dir
# 將項目的 include 路徑設定為當前目錄（或是你的標頭檔所在的目錄）
# target_include_directories(${PROJECT_NAME} PUBLIC ${BIGTWO_INCS} ${COMM_INCS})
# 将包含目录添加为库的接口目录
# PRIVATE main main檔連接到這個庫的時候會找不到 hpp 檔 PUBLIC 才行
target_include_directories(${PROJECT_NAME}_LIB PUBLIC ${INCS} ${COMM_INCS})
# target_include_directories(${PROJECT_NAME}_LIB PUBLIC 
#     ${CMAKE_CURRENT_LIST_DIR}/lib/Channel 
#     ${CMAKE_CURRENT_LIST_DIR}/lib/Subscriber 
#     ${CMAKE_CURRENT_LIST_DIR}/lib/utils)


# 链接库到可执行文件
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_LIB)

# 設定項目的目標特性，比如 C++ 版本
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
# target_compile_options(${PROJECT_NAME} PRIVATE -finput-charset=UTF-8)

if(WIN32)
    # 設置MSVC編譯編碼
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

if(APPLE OR UNIX)
    add_compile_options(-finput-charset=UTF-8)
    add_compile_options(-fexec-charset=UTF-8)
endif()


#GTEST
enable_testing()
add_subdirectory(test)


# 在主程序之前添加一个自定义目标以运行测试
# add_custom_target(RunTests
#     COMMAND ${CMAKE_CTEST_COMMAND}
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#     COMMENT "Running tests before the main program"
# )


# 添加依赖关系，确保在运行主程序之前运行测试
# add_dependencies(${PROJECT_NAME} RunTests)

