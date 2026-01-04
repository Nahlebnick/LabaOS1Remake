#include <gtest/gtest.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include "process.h"

using namespace myLib;


TEST(ProcessTest, CreateAndFinishSimpleProcess)
{
    ASSERT_NO_THROW({
        Process p(L"cmd.exe /c exit 0");
        EXPECT_TRUE(p.valid());
        EXPECT_NE(p.GetProcessID(), 0);
        EXPECT_NE(p.GetThreadID(), 0);
        EXPECT_NE(p.GetProcessHandle(), nullptr);
        
        p.wait(); 
    });
}

TEST(ProcessTest, ThrowsOnEmptyCommand) {
    EXPECT_THROW(Process(L""), std::invalid_argument);
}

TEST(ProcessTest, ThrowsOnNonExistentFile)
{
    EXPECT_THROW(Process(L"this_executable_definitely_does_not_exist_12345.exe"), std::system_error);
}

TEST(ProcessTest, MoveConstructorTransfersOwnership) {
    Process p1(L"cmd.exe /c timeout /t 1 /nobreak");
    DWORD originalPid = p1.GetProcessID();
    HANDLE originalHandle = p1.GetProcessHandle();

    Process p2(std::move(p1));

    EXPECT_FALSE(p1.valid());
    EXPECT_EQ(p1.GetProcessHandle(), nullptr);

    EXPECT_TRUE(p2.valid());
    EXPECT_EQ(p2.GetProcessID(), originalPid);
    EXPECT_EQ(p2.GetProcessHandle(), originalHandle);

    p2.terminate();
}

TEST(ProcessTest, MoveAssignmentTransfersOwnership) {
    Process p1(L"cmd.exe /c timeout /t 1 /nobreak");
    Process p2(L"cmd.exe /c exit 0");

    DWORD pid1 = p1.GetProcessID();

    p2 = std::move(p1);

    EXPECT_FALSE(p1.valid());
    EXPECT_TRUE(p2.valid());
    EXPECT_EQ(p2.GetProcessID(), pid1);

    p2.terminate();
}

TEST(ProcessTest, WaitThrowsOnTimeout)
{
    Process p(L"cmd.exe /c ping -n 4 127.0.0.1 > nul");

    EXPECT_THROW(p.wait(100), std::runtime_error);

    p.terminate();
}

TEST(ProcessTest, TerminateWorks)
{
    Process p(L"cmd.exe /c timeout /t 10 /nobreak");
    
    EXPECT_TRUE(p.valid());

    bool result = p.terminate(1);
    EXPECT_TRUE(result);

    auto start = std::chrono::steady_clock::now();
    p.wait(1000); 
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    EXPECT_LT(elapsed.count(), 0.5);
}