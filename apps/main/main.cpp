#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

#define NOMINMAX
#include <windows.h>
#include "employee.h"
#include "process.h"
#include "fileUtils.h"

void printEmployees(const std::vector<employee>& employees)
{
    std::cout << "-------------------------------\n";
    for (const auto& emp : employees)
    {
        std::cout << emp << std::endl;
    }
    std::cout << "-------------------------------\n";
}

void printReport(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw runtime_error("Failed to open report file: " + filename);
    }

    std::cout << "\n=== Report " << filename << " ===\n\n";

    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }

    std::cout << "\n=== End of Report ===\n";
}

std::wstring string_to_wstring(const std::string& str, UINT code_page = CP_UTF8) {
    if (str.empty()) return L"";

    int wide_size = MultiByteToWideChar(code_page, 0, str.c_str(), -1, nullptr, 0);

    if (wide_size == 0) return L"";

    std::wstring wide_str(wide_size, 0);
    wide_size = MultiByteToWideChar(code_page, 0, str.c_str(), -1, &wide_str[0], wide_size);

    wide_str.pop_back();
    return wide_str;
}

int main()
{
    try 
    {
        std::string binfile;
        int count;

        std::cout << "Enter file name: ";
        binfile = getFilename(cin, ".bin");
        std::cout << "Enter count: ";
        while (!(std::cin >> count) || count < 0)
        {
            std::cout << "Invalid count. Enter a positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Starting Creator..." << endl;
        std::string commandLine = "Creator.exe " + binfile + " " + to_string(count);
        myLib::Process creator(string_to_wstring(commandLine), FALSE, CREATE_NEW_CONSOLE);
        creator.wait();

        std::cout << "\nData from binary file:\n";
        auto employees = readEmployeesFromFile(binfile);
        printEmployees(employees);

        string reportfile;
        double rate;
        std::cout << "\nEnter report file name: ";
        reportfile = getFilename(cin, ".txt");
        cout << "Enter rate: ";
        while (!(std::cin >> rate) || rate < 0)
        {
            std::cout << "Invalid rate. Enter a positive number: ";
            std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Starting Reporter..." << std::endl;        
        commandLine = "Reporter.exe " + binfile + " " + reportfile + " " + to_string(rate);
        myLib::Process reporter(string_to_wstring(commandLine), FALSE, CREATE_NEW_CONSOLE);
        reporter.wait();

        printReport(reportfile);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\nExit program." << std::endl;
    system("pause");
    return 0;
}