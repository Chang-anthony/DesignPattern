#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <vector>
#include <fstream>

#include "Database.hpp"
#include "Employee.hpp"
#include "RealDatabase.hpp"
#include "LazyInitDatabaseProxy.hpp"
#include "PasswordProtectProxy.hpp"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

static const std::string DATA_PATH = EMPLOYEE_DATA_PATH;
// 假設的密碼，直接透過建構子給 proxy，不需設定環境變數
static const std::string CORRECT_PASSWORD = "1qaz2wsx";
static const std::string WRONG_PASSWORD = "wrong";
static std::vector<int> idsOf(const std::vector<Employee*>& employees)
{
    std::vector<int> ids;
    for (const Employee* employee : employees) {
        ids.push_back(employee->getId());
    }
    return ids;
}

// ================= RealDatabase

TEST(RealDatabaseTest, GetEmployeeById_ReturnsCorrectFields) {
    RealDatabase database(DATA_PATH);
    Employee* employee = database.getEmployeeById(2);
    ASSERT_NE(employee, nullptr);
    EXPECT_EQ(employee->getId(), 2);
    EXPECT_EQ(employee->getName(), "fixiabis");
    EXPECT_EQ(employee->getAge(), 15);
    EXPECT_EQ(idsOf(employee->getSubordinates()), (std::vector<int>{1, 3}));
}

TEST(RealDatabaseTest, GetEmployeeById_NestedSubordinates) {
    RealDatabase database(DATA_PATH);
    Employee* employee = database.getEmployeeById(4);
    ASSERT_NE(employee, nullptr);
    std::vector<Employee*> subordinates = employee->getSubordinates();
    ASSERT_EQ(idsOf(subordinates), (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(idsOf(subordinates[1]->getSubordinates()), (std::vector<int>{1, 3}));
    EXPECT_EQ(idsOf(subordinates[2]->getSubordinates()), (std::vector<int>{1}));
    EXPECT_TRUE(subordinates[0]->getSubordinates().empty());
}

TEST(RealDatabaseTest, GetEmployeeById_InvalidId) {
    RealDatabase database(DATA_PATH);
    EXPECT_EQ(database.getEmployeeById(0), nullptr);
    EXPECT_EQ(database.getEmployeeById(-1), nullptr);
    EXPECT_EQ(database.getEmployeeById(7), nullptr);
    EXPECT_EQ(database.getEmployeeById(100), nullptr);
}

TEST(RealDatabaseTest, GetSubordinatesById) {
    RealDatabase database(DATA_PATH);
    EXPECT_EQ(idsOf(database.getSubordinatesById(5)), (std::vector<int>{1, 4}));
    EXPECT_TRUE(database.getSubordinatesById(1).empty());
    EXPECT_TRUE(database.getSubordinatesById(0).empty());
}

// ================= LazyInitDatabaseProxy

TEST(LazyInitDatabaseProxyTest, NotLoadedUntilFirstCall) {
    LazyInitDatabaseProxy proxy(DATA_PATH);
    EXPECT_FALSE(proxy.isLoaded());
    proxy.getEmployeeById(1);
    EXPECT_TRUE(proxy.isLoaded());
}

TEST(LazyInitDatabaseProxyTest, GetSubordinatesAlsoLoads) {
    LazyInitDatabaseProxy proxy(DATA_PATH);
    EXPECT_EQ(idsOf(proxy.getSubordinatesById(2)), (std::vector<int>{1, 3}));
    EXPECT_TRUE(proxy.isLoaded());
}

TEST(LazyInitDatabaseProxyTest, ReturnsSameAsRealDatabase) {
    RealDatabase real(DATA_PATH);
    LazyInitDatabaseProxy proxy(DATA_PATH);
    for (int id = 1; id <= 6; id++) {
        Employee* expected = real.getEmployeeById(id);
        Employee* actual = proxy.getEmployeeById(id);
        ASSERT_NE(expected, nullptr);
        ASSERT_NE(actual, nullptr);
        EXPECT_EQ(actual->getId(), expected->getId());
        EXPECT_EQ(actual->getName(), expected->getName());
        EXPECT_EQ(actual->getAge(), expected->getAge());
        EXPECT_EQ(idsOf(actual->getSubordinates()), idsOf(expected->getSubordinates()));
    }
}

TEST(LazyInitDatabaseProxyTest, InvalidId) {
    LazyInitDatabaseProxy proxy(DATA_PATH);
    EXPECT_EQ(proxy.getEmployeeById(0), nullptr);
    EXPECT_EQ(proxy.getEmployeeById(7), nullptr);
}

// ================= PasswordProtectProxy

TEST(PasswordProtectProxyTest, WrongPassword_ReturnsNull) {
    PasswordProtectProxy proxy(DATA_PATH, WRONG_PASSWORD);
    EXPECT_EQ(proxy.getEmployeeById(1), nullptr);
    EXPECT_TRUE(proxy.getSubordinatesById(2).empty());
    // 沒通過驗證就不應該載入資料庫
    EXPECT_FALSE(proxy.isLoaded());
}

TEST(PasswordProtectProxyTest, EmptyPassword_ReturnsNull) {
    PasswordProtectProxy proxy(DATA_PATH, "");
    EXPECT_EQ(proxy.getEmployeeById(1), nullptr);
    EXPECT_FALSE(proxy.isLoaded());
}

TEST(PasswordProtectProxyTest, CorrectPassword_ReturnsEmployee) {
    PasswordProtectProxy proxy(DATA_PATH, CORRECT_PASSWORD);
    EXPECT_FALSE(proxy.isLoaded());
    Employee* employee = proxy.getEmployeeById(3);
    ASSERT_NE(employee, nullptr);
    EXPECT_EQ(employee->getName(), "fong");
    EXPECT_EQ(employee->getAge(), 7);
    EXPECT_EQ(idsOf(proxy.getSubordinatesById(4)), (std::vector<int>{1, 2, 3}));
    EXPECT_TRUE(proxy.isLoaded());
}

// ================= Polymorphism

TEST(DatabaseTest, ClientUsesSameInterface) {
    std::vector<Database*> databases = {
        new RealDatabase(DATA_PATH),
        new LazyInitDatabaseProxy(DATA_PATH),
        new PasswordProtectProxy(DATA_PATH, CORRECT_PASSWORD),
    };
    for (Database* database : databases) {
        Employee* employee = database->getEmployeeById(6);
        ASSERT_NE(employee, nullptr);
        EXPECT_EQ(employee->getName(), "handsomeboy");
        EXPECT_EQ(idsOf(database->getSubordinatesById(6)), (std::vector<int>{1}));
        delete database;
    }
}

int main(int argc, char **argv) {
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
