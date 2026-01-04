#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstring> 
#include "employee.h"
#include "fileUtils.h" 

employee createEmp(int num, double hours, const std::string& nameStr) 
{
    employee emp;
    emp.num = num;
    emp.hours = hours;
    std::strncpy(emp.name, nameStr.c_str(), sizeof(emp.name) - 1);
    emp.name[sizeof(emp.name) - 1] = '\0';
    return emp;
}

bool areEmployeesEqual(const employee& e1, const employee& e2)
{
    return e1.num == e2.num && 
           std::abs(e1.hours - e2.hours) < 0.001 &&
           std::string(e1.name) == std::string(e2.name);
}

TEST(FileUtilsTest, WriteAndReadStream) 
{
    std::vector<employee> originalData;
    originalData.push_back(createEmp(1, 40.5, "Alice"));
    originalData.push_back(createEmp(2, 35.0, "Bob"));

    std::stringstream ss;

    writeEmployees(ss, originalData);

    ss.seekg(0, std::ios::end);
    std::streampos size = ss.tellg();
    ss.seekg(0, std::ios::beg);

    EXPECT_EQ(size, originalData.size() * sizeof(employee));

    std::vector<employee> readData = readEmployees(ss);

    ASSERT_EQ(readData.size(), originalData.size());
    EXPECT_TRUE(areEmployeesEqual(readData[0], originalData[0]));
    EXPECT_TRUE(areEmployeesEqual(readData[1], originalData[1]));
}

TEST(FileUtilsTest, WriteAndReadRealFile) 
{
    std::string filename = "test_employees.bin";
    
    std::vector<employee> originalData;
    originalData.push_back(createEmp(100, 12.5, "TestUser"));

    writeEmployeesIntoFile(filename, originalData);

    std::ifstream checkFile(filename);
    ASSERT_TRUE(checkFile.good()) << "File was not created!";
    checkFile.close();

    std::vector<employee> readData = readEmployeesFromFile(filename);

    ASSERT_EQ(readData.size(), originalData.size());
    EXPECT_TRUE(areEmployeesEqual(readData[0], originalData[0]));

    std::remove(filename.c_str());
}

TEST(FileUtilsTest, ReadNonExistentFileThrows) 
{
    std::string badFilename = "does_not_exist.bin";
    
    EXPECT_THROW(readEmployeesFromFile(badFilename), std::runtime_error);
}


TEST(FileUtilsTest, GetFilenameAddsExtension)
{
    std::stringstream input("data");
    std::string result = getFilename(input, ".bin");
    
    EXPECT_EQ(result, "data.bin");
}

TEST(FileUtilsTest, GetFilenameKeepsExtension)
{
    std::stringstream input("report.txt");
    std::string result = getFilename(input, ".bin");
    
    EXPECT_EQ(result, "report.txt");
}
