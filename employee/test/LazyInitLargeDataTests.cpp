#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <filesystem>

#include "Employee.hpp"
#include "RealDatabase.hpp"
#include "LazyInitDatabaseProxy.hpp"

// 隨機產生大量員工資料，測試 LazyInitDatabaseProxy 的延遲載入行為
//
// 資料結構為一棵隨機樹：員工 i 的主管是 [1, i-1] 中隨機一人，
// 因此不會有循環，查詢任一員工只會展開他自己的子樹。

namespace {

constexpr int EMPLOYEE_COUNT = 50000;
constexpr unsigned SEED = 20261012;     // 固定 seed，失敗時可重現
constexpr int QUERY_COUNT = 2000;

struct Record {
    std::string name;
    int age;
    std::vector<int> subordinates;
};

std::filesystem::path tempFile(const std::string& name)
{
    return std::filesystem::temp_directory_path() / name;
}

std::vector<int> idsOf(const std::vector<Employee*>& employees)
{
    std::vector<int> ids;
    for (const Employee* employee : employees) {
        ids.push_back(employee->getId());
    }
    return ids;
}

void freeEmployee(Employee* employee)
{
    if (employee == nullptr) {
        return;
    }
    for (Employee* sub : employee->getSubordinates()) {
        freeEmployee(sub);
    }
    delete employee;
}

void freeEmployees(const std::vector<Employee*>& employees)
{
    for (Employee* employee : employees) {
        freeEmployee(employee);
    }
}

} // namespace

class LazyInitLargeDataTest : public ::testing::Test {
protected:
    // records[0] 不使用，id 從 1 開始
    static std::vector<Record> records;
    static std::filesystem::path dataPath;

    static void SetUpTestSuite()
    {
        std::mt19937 rng(SEED);
        std::uniform_int_distribution<int> ageDist(18, 65);
        std::uniform_int_distribution<int> lenDist(4, 10);
        std::uniform_int_distribution<int> charDist('a', 'z');

        records.assign(EMPLOYEE_COUNT + 1, Record());
        for (int id = 1; id <= EMPLOYEE_COUNT; id++) {
            std::string name;
            int len = lenDist(rng);
            for (int i = 0; i < len; i++) {
                name += static_cast<char>(charDist(rng));
            }
            records[id].name = name;
            records[id].age = ageDist(rng);

            if (id >= 2) {
                int manager = std::uniform_int_distribution<int>(1, id - 1)(rng);
                records[manager].subordinates.push_back(id);
            }
        }

        dataPath = tempFile("employee_lazy_large.data");
        writeDataFile(dataPath);
    }

    static void TearDownTestSuite()
    {
        std::filesystem::remove(dataPath);
        records.clear();
    }

    // 格式與 data.data 相同：表頭 + "id name age subordinateIds"
    static void writeDataFile(const std::filesystem::path& path)
    {
        std::ofstream file(path);
        file << "id name age subordinateIds\n";
        for (int id = 1; id <= EMPLOYEE_COUNT; id++) {
            const Record& record = records[id];
            file << id << " " << record.name << " " << record.age << " ";
            for (size_t i = 0; i < record.subordinates.size(); i++) {
                file << (i ? "," : "") << record.subordinates[i];
            }
            file << "\n";
        }
    }

    static void expectMatches(Employee* employee, int id)
    {
        ASSERT_NE(employee, nullptr) << "id " << id;
        EXPECT_EQ(employee->getId(), id);
        EXPECT_EQ(employee->getName(), records[id].name) << "id " << id;
        EXPECT_EQ(employee->getAge(), records[id].age) << "id " << id;
        EXPECT_EQ(idsOf(employee->getSubordinates()), records[id].subordinates) << "id " << id;
    }

    static std::vector<int> randomIds(unsigned seed, int count)
    {
        std::mt19937 rng(seed);
        std::uniform_int_distribution<int> idDist(1, EMPLOYEE_COUNT);
        std::vector<int> ids;
        for (int i = 0; i < count; i++) {
            ids.push_back(idDist(rng));
        }
        return ids;
    }
};

std::vector<Record> LazyInitLargeDataTest::records;
std::filesystem::path LazyInitLargeDataTest::dataPath;

// 先建立 proxy、之後才產生檔案，仍能查到資料 → 建構時沒有讀檔
TEST_F(LazyInitLargeDataTest, ConstructorDoesNotReadFile) {
    std::filesystem::path path = tempFile("employee_lazy_late.data");
    std::filesystem::remove(path);

    LazyInitDatabaseProxy proxy(path.string());
    EXPECT_FALSE(proxy.isLoaded());

    writeDataFile(path);
    int id = EMPLOYEE_COUNT / 2;
    Employee* employee = proxy.getEmployeeById(id);
    EXPECT_TRUE(proxy.isLoaded());
    expectMatches(employee, id);

    freeEmployee(employee);
    std::filesystem::remove(path);
}

// 第一次查詢後刪除檔案，之後的查詢仍正確 → 只讀一次檔
TEST_F(LazyInitLargeDataTest, FileReadOnlyOnce) {
    std::filesystem::path path = tempFile("employee_lazy_once.data");
    writeDataFile(path);

    LazyInitDatabaseProxy proxy(path.string());
    Employee* first = proxy.getEmployeeById(1);
    ASSERT_NE(first, nullptr);
    freeEmployee(first);

    ASSERT_TRUE(std::filesystem::remove(path));

    for (int id : randomIds(SEED + 1, 200)) {
        Employee* employee = proxy.getEmployeeById(id);
        expectMatches(employee, id);
        freeEmployee(employee);
    }
}

TEST_F(LazyInitLargeDataTest, RandomQueries_MatchGeneratedData) {
    LazyInitDatabaseProxy proxy(dataPath.string());

    for (int id : randomIds(SEED + 2, QUERY_COUNT)) {
        Employee* employee = proxy.getEmployeeById(id);
        expectMatches(employee, id);
        freeEmployee(employee);
    }

    EXPECT_EQ(proxy.getEmployeeById(EMPLOYEE_COUNT + 1), nullptr);
    expectMatches(proxy.getEmployeeById(EMPLOYEE_COUNT), EMPLOYEE_COUNT);
}

TEST_F(LazyInitLargeDataTest, RandomSubordinateQueries_MatchGeneratedData) {
    LazyInitDatabaseProxy proxy(dataPath.string());

    for (int id : randomIds(SEED + 3, QUERY_COUNT)) {
        std::vector<Employee*> subordinates = proxy.getSubordinatesById(id);
        EXPECT_EQ(idsOf(subordinates), records[id].subordinates) << "id " << id;
        freeEmployees(subordinates);
    }
}

// 建構 proxy 不讀檔，應明顯比直接建構 RealDatabase（讀整個檔案）快
TEST_F(LazyInitLargeDataTest, ConstructionCost_LazyVsReal) {
    using Clock = std::chrono::steady_clock;
    auto micros = [](Clock::duration d) {
        return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
    };

    auto t0 = Clock::now();
    RealDatabase real(dataPath.string());
    auto t1 = Clock::now();
    LazyInitDatabaseProxy proxy(dataPath.string());
    auto t2 = Clock::now();
    Employee* employee = proxy.getEmployeeById(EMPLOYEE_COUNT);
    auto t3 = Clock::now();

    std::cout << "[ INFO     ] " << EMPLOYEE_COUNT << " employees\n"
              << "[ INFO     ] RealDatabase ctor          : " << micros(t1 - t0) << " us\n"
              << "[ INFO     ] LazyInitDatabaseProxy ctor : " << micros(t2 - t1) << " us\n"
              << "[ INFO     ] proxy first query (load)   : " << micros(t3 - t2) << " us\n";

    expectMatches(employee, EMPLOYEE_COUNT);
    EXPECT_LT(t2 - t1, t1 - t0);

    freeEmployee(employee);
}
