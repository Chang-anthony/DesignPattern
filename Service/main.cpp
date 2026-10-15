/*
* @author - (Anthony)
*
* Service 主程式（Client）：服務探索 / 負載平衡 / 黑名單的 Http Client 套件。
* 目前在 OOA 階段，尚未實作（見 CLAUDE.md）。
*/
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif


int main(int argc, char** argv)
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出 / 輸入改為 UTF-8 才能正確顯示與讀取中文
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

}
