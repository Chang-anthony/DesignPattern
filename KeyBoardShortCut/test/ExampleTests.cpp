#include <iostream>
#include <gtest/gtest.h>
#include "gtest/gtest-spi.h"
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif



int main(int argc, char **argv) {
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

