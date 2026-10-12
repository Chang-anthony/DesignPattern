/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include <Database.hpp>
#include <Employee.hpp>
#include <PasswordProtectProxy.hpp>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#ifndef EMPLOYEE_DATA_PATH
#define EMPLOYEE_DATA_PATH "data.data"
#endif

static void SetPassword(const char* password)
{
#ifdef _WIN32
    _putenv_s("PASSWORD", password);
#else
    setenv("PASSWORD", password, 1);
#endif
}

static void PrintEmployee(const Employee* employee, int depth)
{
    std::cout << std::string(depth * 4, ' ')
              << "[" << employee->getId() << "] "
              << employee->getName() << " (" << employee->getAge() << ")" << std::endl;

    for (const Employee* sub : employee->getSubordinates()) {
        PrintEmployee(sub, depth + 1);
    }
}

int main(int argc, char** argv)
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::string path = (argc > 1) ? argv[1] : EMPLOYEE_DATA_PATH;
    std::cout << "資料檔: " << path << std::endl;

    // client 只認得 Database 介面，不知道背後是 proxy
    Database* database = new PasswordProtectProxy(path);

    std::cout << "\n== 1. 未設定密碼，查詢 id 4 ==" << std::endl;
    SetPassword("");
    Employee* employee = database->getEmployeeById(4);
    if (employee == nullptr) {
        std::cout << "驗證失敗，回傳 nullptr" << std::endl;
    }

    std::cout << "\n== 2. 設定正確密碼，查詢 id 4 ==" << std::endl;
    SetPassword("1qaz2wsx");
    employee = database->getEmployeeById(4);
    if (employee != nullptr) {
        PrintEmployee(employee, 0);
    }

    std::cout << "\n== 3. 查詢 id 5 的 subordinates ==" << std::endl;
    for (const Employee* sub : database->getSubordinatesById(5)) {
        PrintEmployee(sub, 0);
    }

    delete database;

    std::cout << "\n按下 Enter鍵 已結束程式" << std::endl;
    std::system("pause");
    return 0;
}
