cmake_minimum_required(VERSION 3.12)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(Designpattern_Cs21H)
set(CMAKE_CXX_STANDARD 20)

# ========================================================
# GTEST
include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    DOWNLOAD_NO_EXTRACT TRUE
    # GIT_REPOSITORY https://github.com/google/googletest.git
    # GIT_TAG        master
    # DOWNLOAD_NO_EXTRACT TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set_property(TARGET gmock PROPERTY FOLDER "gtest")
set_property(TARGET gmock_main PROPERTY FOLDER "gtest")
set_property(TARGET gtest PROPERTY FOLDER "gtest")
set_property(TARGET gtest_main PROPERTY FOLDER "gtest")

# ======================================================


#加入include directories 位置
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/utils)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

# 將所有源檔案放入變數中
set(SOURCES
    main.cpp
)


# 指定項目的執行檔名稱和源檔
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SimpleDesignPatternCs21H)

# 將項目的 include 路徑設定為當前目錄（或是你的標頭檔所在的目錄）
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/utils)

# 設定項目的目標特性，比如 C++ 版本
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -finput-charset=UTF-8)

# 設置MSVC編譯編碼
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


#GTEST
enable_testing()
add_subdirectory(test)

